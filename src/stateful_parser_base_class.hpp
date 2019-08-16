#ifndef liborangepower_stateful_parser_base_class_hpp
#define liborangepower_stateful_parser_base_class_hpp

#include "misc_includes.hpp"
#include "misc_output_classes.hpp"
#include "misc_input_classes.hpp"

namespace liborangepower
{

using misc_output::printout;
using misc_output::sconcat;

namespace lang
{

template<typename LexerType>
class StatefulParserBase
{
public:		// types
	using TokType = typename LexerType::TokType;
	using LexerState = typename LexerType::State;
	using TokToStringMap = std::map<TokType, std::string>;
	using ParseRet = bool;


	class LexStateSets final
	{
	public:		// variables
		std::set<LexerState> found_set, dup_set;
		LexerState first_dup;
		TokType end;

	public:		// functions
		LexStateSets()
		{
		}
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(LexStateSets)
		~LexStateSets()
		{
		}

		inline bool valid() const
		{
			return (dup_set.size() == 0);
		}

		inline bool find_found(TokType tok, LexerState& ret) const
		{
			for (const auto& iter : found_set)
			{
				if (iter.tok() == tok)
				{
					ret = iter;
					return true;
				}
			}
			return false;
		}
		inline LexerState find_found(TokType tok) const
		{
			LexerState ret;
			find_found(tok, ret);
			return ret;
		}
		inline LexerState find_found() const
		{
			return find_found(end);
		}
		inline bool find_dup(TokType tok, LexerState& ret) const
		{
			for (const auto& iter : dup_set)
			{
				if (iter.tok() == tok)
				{
					ret = iter;
					return true;
				}
			}
			return false;
		}
		inline LexerState find_dup(TokType tok) const
		{
			LexerState ret;
			find_dup(tok, ret);
			return ret;
		}
	};



	friend class WExpect;
	class WExpect
	{
	private:		// variables
		StatefulParserBase* _parser = nullptr;
		LexerType* _lexer = nullptr;
	public:		// functions
		WExpect(StatefulParserBase* s_parser, TokType tok,
			const TokToStringMap& some_tok_ident_map,
			LexerType* s_lexer=nullptr)
			: _parser(s_parser), _lexer(s_lexer)
		{
			_parser->_expect(tok, some_tok_ident_map, _lexer, false);
		}
		GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(WExpect);
		~WExpect()
		{
			_parser->_next_tok(_lexer);
		}
	};


	template<typename DerivedType>
	friend class UnitParse;

	template<typename DerivedType>
	class UnitParse final
	{
	public:		// types
		using ParseRet = bool;
		using ParseFunc = bool (DerivedType::*)();

	private:		// variables
		DerivedType* _self = nullptr;
		std::string _parse_func_str;
		ParseFunc _parse_func = nullptr;
		bool _optional = false;

	public:		// functions
		UnitParse(DerivedType* s_self, const std::string& s_parse_func_str,
			ParseFunc s_parse_func, bool s_optional=false)
			: _self(s_self), _parse_func_str(s_parse_func_str),
			_parse_func(s_parse_func), _optional(s_optional)
		{
		}
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(UnitParse);
		~UnitParse()
		{
		}

		inline void set_just_test(bool n_just_test) const
		{
			_self->_just_test = n_just_test;
		}

		inline bool operator () () const
		{
			return (_self->*_parse_func)();
		}

		GEN_GETTER_BY_CON_REF(parse_func_str)
		GEN_GETTER_BY_VAL(optional)
	};


	// Perform a parsing sequence using member function pointers
	template<typename DerivedType>
	friend class SeqParse;

	template<typename DerivedType>
	class SeqParse
	{
	public:		// types
		using TheUnitParse = UnitParse<DerivedType>;
		using ParseRet = typename TheUnitParse::ParseRet;
		using TheSeqParse = std::shared_ptr<SeqParse<DerivedType>>;
		using OneInst = std::variant<bool, TheUnitParse, TheSeqParse>;
		using Vec = std::vector<OneInst>;

		class FirstValidInvalidInst
		{
		public:		// variables
			ParseRet parse_ret;
			OneInst one_inst;
		};
	public:		// variables
		static inline bool debug = false;
		static inline const TokToStringMap* debug_tok_ident_map = nullptr;

	protected:		// variables
		DerivedType* _self = nullptr;
		Vec _vec;
		bool _optional = false;

	public:		// functions
		SeqParse() = default;
		SeqParse(DerivedType* s_self, Vec&& s_vec, bool s_optional=false)
			: _self(s_self), _vec(std::move(s_vec)), _optional(s_optional)
		{
		}
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(SeqParse);
		virtual ~SeqParse() = default;

		virtual bool check() const
		{
			const auto lex_state = _self->_lex_state();

			for (const auto& iter : vec())
			{
				if (!_check_one(iter))
				{
					_self->_lexer().set_state(lex_state);
					return false;
				}

				// This is necessary to reach the next parsing function in
				// the (linear) sequence.
				_exec_one(iter, true);
			}

			_self->_lexer().set_state(lex_state);
			return true;
		}
		// For OrParse
		inline OneInst fv_inst() const
		{
			OneInst ret;
			const auto lex_state = _self->_lex_state();

			for (const auto& iter : vec())
			{
				if (_check_one(iter))
				{
					ret = iter;
					_self->_lexer().set_state(lex_state);
					return ret;
				}
				//_exec_one(iter);
			}

			ret = false;
			_self->_lexer().set_state(lex_state);
			return ret;
		}
		// For OrParse
		inline std::string fv_parse_func_str() const
		{
			return std::get<TheUnitParse>(std::get<TheSeqParse>
				(fv_inst())->vec().front()).parse_func_str();
		}
		inline FirstValidInvalidInst first_invalid_inst() const
		{
			FirstValidInvalidInst ret;
			const auto lex_state = _self->_lex_state();

			for (const auto& iter : vec())
			{
				if (!_check_one(iter))
				{
					ret.parse_ret.reset(new LexerState(_self->_lexer()
						.state()));
					ret.one_inst = iter;
					_self->_lexer().set_state(lex_state);
					return ret;
				}
				_exec_one(iter, true);
			}

			ret.parse_ret.reset(new LexerState(_self->_lexer().state()));
			ret.one_inst = false;
			_self->_lexer().set_state(lex_state);
			return ret;
		}
		virtual void exec() const
		{
			const auto ret = _self->_lex_state();

			for (const auto& iter : vec())
			{
				_exec_one(iter);
			}

			//return ParseRet(new LexerState(ret));
		}

		GEN_GETTER_BY_CON_REF(vec)
		GEN_GETTER_BY_VAL(optional)

	protected:		// functions
		bool _check_one(const OneInst& iter) const
		{
			if (std::holds_alternative<TheUnitParse>(iter))
			{
				const auto& temp = std::get<TheUnitParse>(iter);
				temp.set_just_test(true);

				if (!temp.optional())
				{
					if (temp())
					{
						temp.set_just_test(false);
						return true;
					}
					else
					{
						temp.set_just_test(false);
						return false;
					}
				}
			}
			else
			{
				const auto& temp = std::get<TheSeqParse>(iter);

				if (!temp->optional())
				{
					return temp->check();
				}
			}
			return true;
		}
		void _exec_one(const OneInst& iter, bool actual_just_parse=false)
			const
		{
			_self->_push_num(_self->just_parse());
			_self->_just_parse = actual_just_parse;
			if (std::holds_alternative<TheUnitParse>(iter))
			{
				const auto& temp = std::get<TheUnitParse>(iter);

				if (debug)
				{
					printout("_exec_one():  ", temp.parse_func_str(),
						"\n");
				}

				const auto lex_state = _self->_dup_lex_state();
				if (temp.optional())
				{
					temp.set_just_test(true);

					if (temp())
					{
						temp.set_just_test(false);
						temp();

						if (debug)
						{
							printout("success:  \"",
								debug_tok_ident_map->at(lex_state->tok()),
								"\", \"", lex_state->s(), "\" ",
								lex_state->line_num(), ":",
								lex_state->pos_in_line(), "\n");
						}
					}
					temp.set_just_test(false);
				}
				else
				{
					temp.set_just_test(false);
					temp();

					if (debug)
					{
						printout("success:  \"",
							debug_tok_ident_map->at(lex_state->tok()),
							"\", \"", lex_state->s(), "\" ",
							lex_state->line_num(), ":",
							lex_state->pos_in_line(), "\n");
					}
				}
			}
			else
			{
				const auto& temp = std::get<TheSeqParse>(iter);

				if (temp->optional())
				{
					if (temp->check())
					{
						temp->exec();
					}
				}
				else
				{
					temp->exec();
				}
			}
			if (_self->_pop_num())
			{
				_self->_just_parse = true;
			}
			else
			{
				_self->_just_parse = false;
			}
		}
	};

	template<typename SomeSeqParseType>
	using MapSeqParse = std::map<std::string, SomeSeqParseType>;


	// Find the first valid parsing sequence and execute it.  Choose from a
	// list separated by pipes (|).
	template<typename DerivedType>
	class OrParse : public SeqParse<DerivedType>
	{
	public:		// typedefs
		using Base = SeqParse<DerivedType>;
		using TheUnitParse = typename Base::TheUnitParse;
		using TheSeqParse = typename Base::TheSeqParse;
		using ParseRet = typename Base::ParseRet;
		using Vec = typename Base::Vec;

	public:		// functions
		OrParse(DerivedType* s_self, Vec&& s_vec, bool s_optional=false)
			: Base(s_self, std::move(s_vec), s_optional)
		{
		}
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(OrParse);
		virtual ~OrParse()
		{
		}

		virtual bool check() const
		{
			// Any one found gets used
			for (const auto& iter : Base::vec())
			{
				if (Base::_check_one(iter))
				{
					return true;
				}
			}
			return false;
		}
		virtual void exec() const
		{
			//const auto ret = Base::_self->_lex_state();

			for (const auto& iter : Base::vec())
			{
				// First one found gets executed
				if (Base::_check_one(iter))
				{
					Base::_exec_one(iter);
					break;
				}
			}

			//return ParseRet(new LexerState(ret));
		}
	};

	template<typename DerivedType>
	class ListParse : public SeqParse<DerivedType>
	{
	public:		// typedefs
		using Base = SeqParse<DerivedType>;
		using TheUnitParse = typename Base::TheUnitParse;
		using TheSeqParse = typename Base::TheSeqParse;
		using ParseRet = typename Base::ParseRet;
		using Vec = typename Base::Vec;

	public:		// functions
		ListParse(DerivedType* s_self, Vec&& s_vec,
			bool s_optional=false)
			: Base(s_self, std::move(s_vec), s_optional)
		{
		}
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ListParse);
		virtual ~ListParse()
		{
		}

		virtual bool check() const
		{
			const auto lex_state = Base::_self->_lex_state();

			bool found;
			bool first_done = false;

			for (;;)
			{
				found = true;
				for (const auto& iter : Base::vec())
				{
					if (!Base::_check_one(iter))
					{
						//_self->_lexer().set_state(lex_state);
						//return first_done;
						found = false;
						break;
					}
					Base::_exec_one(iter, true);
				}

				if (!found)
				{
					break;
				}
				first_done = true;
			}

			Base::_self->_lexer().set_state(lex_state);
			return first_done;
		}
		virtual void exec() const
		{
			//const auto ret = Base::_self->_lex_state();

			size_t to_push = 0;

			do
			{
				Base::exec();
				++to_push;
			} while (check());

			if ((!Base::_self->actual_just_test())
				&& (!Base::_self->just_parse()))
			{
				Base::_self->_push_num(to_push);
			}

			//return ParseRet(new LexerState(ret));
		}
	};

	template<typename DerivedType>
	class MultiParse
	{
	public:		// types
		using TheUnitParse = UnitParse<DerivedType>;
		using ParseRet = typename TheUnitParse::ParseRet;
		using ParseFunc = typename TheUnitParse::ParseFunc;
		using TheSeqParse = SeqParse<DerivedType>;
		using TheOrParse = OrParse<DerivedType>;
		using TheListParse = ListParse<DerivedType>;
		using Vec = typename TheSeqParse::Vec;

	public:		// functions
		template<typename SomeMapSeqParseType, typename FirstArgType,
			typename...  RemArgTypes>
		static inline void _append_msp
			(SomeMapSeqParseType& map_seq_parse,
			const std::string& first_key, FirstArgType&& first_seq,
			RemArgTypes&&... rem_args)
		{
			map_seq_parse[first_key] = std::move(first_seq);

			if constexpr (sizeof...(rem_args) > 0)
			{
				_append_msp(map_seq_parse, rem_args...);
			}
		}

		static inline TheUnitParse _unit_parse(DerivedType* self,
			const std::string& s_parse_func_str, ParseFunc s_parse_func,
			bool s_optional)
		{
			return TheUnitParse(self, s_parse_func_str, s_parse_func,
				s_optional);
		}

		template<typename FirstArgType, typename... RemArgTypes>
		static inline void _inner_seq_parse(Vec& ret,
			const FirstArgType& first_arg, RemArgTypes&&... rem_args)
		{
			using NoRefFirstArgType
				= typename std::remove_reference<FirstArgType>::type;
			using TrueFirstArgType
				= typename std::remove_cv<NoRefFirstArgType>::type;
			static_assert((std::is_same<TrueFirstArgType, TheUnitParse>()
				|| std::is_same<TrueFirstArgType, TheSeqParse>()
				|| std::is_same<TrueFirstArgType, TheOrParse>()
				|| std::is_same<TrueFirstArgType, TheListParse>()),
				"Invalid _inner_seq_parse() first arg");

			typename TheSeqParse::OneInst to_push;

			if constexpr (std::is_same<TrueFirstArgType, TheUnitParse>())
			{
				to_push = first_arg;
			}
			else if constexpr (std::is_same<TrueFirstArgType,
				TheSeqParse>())
			{
				using TempTheSeqParse = typename SeqParse<DerivedType>
					::TheSeqParse;
				to_push = TempTheSeqParse(new SeqParse<DerivedType>
					(first_arg));
			}
			else if constexpr (std::is_same<TrueFirstArgType,
				TheOrParse>())
			{
				using TempTheSeqParse = typename SeqParse<DerivedType>
					::TheSeqParse;
				to_push = TempTheSeqParse(new OrParse<DerivedType>
					(first_arg));
			}
			else if constexpr (std::is_same<TrueFirstArgType,
				TheListParse>())
			{
				using TempTheSeqParse = typename SeqParse<DerivedType>
					::TheSeqParse;
				to_push = TempTheSeqParse(new ListParse<DerivedType>
					(first_arg));
			}
			ret.push_back(to_push);

			if constexpr (sizeof...(rem_args) > 0)
			{
				_inner_seq_parse(ret, rem_args...);
			}
		}

		template<typename FirstArgType, typename... RemArgTypes>
		static inline TheSeqParse _opt_seq_parse(DerivedType* s_self,
			const FirstArgType& first_arg, RemArgTypes&&... rem_args)
		{
			typename TheSeqParse::Vec s_vec;
			_inner_seq_parse(s_vec, first_arg, rem_args...);

			return TheSeqParse(s_self, std::move(s_vec), true);
		}
		template<typename FirstArgType, typename... RemArgTypes>
		static inline TheSeqParse _req_seq_parse(DerivedType* s_self,
			const FirstArgType& first_arg, RemArgTypes&&... rem_args)
		{
			typename TheSeqParse::Vec s_vec;
			_inner_seq_parse(s_vec, first_arg, rem_args...);

			return TheSeqParse(s_self, std::move(s_vec), false);
		}
		template<typename FirstArgType, typename... RemArgTypes>
		static inline TheOrParse _opt_or_parse(DerivedType* s_self,
			const FirstArgType& first_arg, RemArgTypes&&... rem_args)
		{
			typename TheOrParse::Vec s_vec;
			_inner_seq_parse(s_vec, first_arg, rem_args...);

			return TheOrParse(s_self, std::move(s_vec), true);
		}
		template<typename FirstArgType, typename... RemArgTypes>
		static inline TheOrParse _req_or_parse(DerivedType* s_self,
			const FirstArgType& first_arg, RemArgTypes&&... rem_args)
		{
			typename TheOrParse::Vec s_vec;
			_inner_seq_parse(s_vec, first_arg, rem_args...);

			return TheOrParse(s_self, std::move(s_vec), false);
		}
		template<typename FirstArgType, typename... RemArgTypes>
		static inline TheListParse _opt_list_parse(DerivedType* s_self,
			const FirstArgType& first_arg, RemArgTypes&&... rem_args)
		{
			typename TheListParse::Vec s_vec;
			_inner_seq_parse(s_vec, first_arg, rem_args...);

			return TheListParse(s_self, std::move(s_vec), true);
		}
		template<typename FirstArgType, typename... RemArgTypes>
		static inline TheListParse _req_list_parse(DerivedType* s_self,
			const FirstArgType& first_arg, RemArgTypes&&... rem_args)
		{
			typename TheListParse::Vec s_vec;
			_inner_seq_parse(s_vec, first_arg, rem_args...);

			return TheListParse(s_self, std::move(s_vec), false);
		}
	};


protected:		// variables
	LexStateSets _lss;
	bool _just_test = false, _just_parse = false;
	size_t _curr_file_index = 0;
	std::vector<std::string> _filename_vec;
	std::vector<std::unique_ptr<std::string>> _text_vec;
	std::vector<LexerType> _lexer_vec;

public:		// functions
	StatefulParserBase(std::vector<std::string>&& s_filename_vec)
		: _filename_vec(std::move(s_filename_vec))
	{
		for (const auto& filename : _filename_vec)
		{
			if (auto&& f = std::ifstream(filename); true)
			{
				_text_vec.push_back(std::unique_ptr<std::string>(new
					std::string(liborangepower::misc_input
						::get_istream_as_str(f))));
			}
			_lexer_vec.push_back(LexerType(filename,
				_text_vec.back().get()));
			_next_tok(&_lexer_vec.back());
		}
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StatefulParserBase)
	virtual ~StatefulParserBase()
	{
	}

	//inline auto lex_tok() const
	//{
	//	return _lexer().tok();
	//}
	//inline const auto& lex_s() const
	//{
	//	return _lexer().s();
	//}
	//inline auto lex_src_code_chunk() const
	//{
	//	return _lexer().src_code_chunk();
	//}
	//inline bool cmp_lex_tok(TokType tok) const
	//{
	//	return (lex_tok() == tok);
	//}


	//// Order does not matter
	//inline bool cmp_prefix_tok_list(const std::set<TokType>& prefix_set,
	//	TokType end, bool& found_dup) const
	//{
	//	found_dup = false;

	//	std::set<TokType> found_prefix_set;
	//	Lexer temp_lexer(_lexer());
	//	auto* lexer = &temp_lexer;

	//	for (const auto& iter : prefix_set)
	//	{
	//		if (found_prefix_set.find)
	//		_next_tok(lexer);
	//	}
	//}

	inline bool cmp_lex_tok(TokType to_cmp) const
	{
		return (_lexer().tok() == to_cmp);
	}

	inline bool actual_just_test() const
	{
		if (just_parse())
		{
			return false;
		}
		else
		{
			return _just_test;
		}
	}
	inline bool just_parse() const
	{
		return _just_parse;
	}

	GEN_GETTER_BY_VAL(curr_file_index)
	GEN_GETTER_BY_CON_REF(lss)

protected:		// functions
	const LexerType& _lexer() const
	{
		return _lexer_vec.at(curr_file_index());
	}
	LexerType& _lexer()
	{
		return _lexer_vec.at(curr_file_index());
	}
	const LexerState& _lex_state() const
	{
		return _lexer().state();
	}

	const std::vector<LexerState> _next_n_tokens(size_t n,
		bool affect_lexer)
	{
		std::vector<LexerState> ret;

		LexerType temp_lexer(_lexer());

		auto& lexer = affect_lexer ? _lexer() : temp_lexer;

		for (size_t i=0; i<n; ++i)
		{
			ret.push_back(lexer.state());
			_next_tok(&lexer);
		}

		return ret;
	}

	// Duplicates are banned.
	bool _check_prefixed_tok_seq(const std::set<TokType>& prefix_set,
		TokType end)
	{
		_lss.found_set.clear();
		_lss.dup_set.clear();
		_lss.end = end;

		const auto tokens = _next_n_tokens((prefix_set.size() + 1),
			!actual_just_test());
		//printout("_check_prefixed_tok_seq():  Test 0:  ", tokens.size(),
		//	"\n");

		for (const auto& tok_iter : tokens)
		{
			//printout(tok_iter.s(), " ",
			//	static_cast<size_t>(tok_iter.tok()), "\n");
			auto update_lss = [&]() -> void
			{
				if (_lss.found_set.count(tok_iter) != 0)
				{
					_lss.dup_set.insert(tok_iter);
					if (_lss.dup_set.size() == 1)
					{
						_lss.first_dup = tok_iter;
					}
				}
				_lss.found_set.insert(tok_iter);
			};

			if (prefix_set.count(tok_iter.tok()) != 0)
			{
				update_lss();
			}
			else if (tok_iter.tok() == end)
			{
				//printout("_check_prefixed_tok_seq():  Test\n");
				update_lss();
				return true;
			}
			else
			{
				break;
			}
		}

		return false;
	}
	bool _check_prefixed_tok_seq(TokType end)
	{
		return _check_prefixed_tok_seq(std::set<TokType>(), end);
	}
	inline void _next_lss_tokens(const TokToStringMap& some_tok_ident_map)
	{
		if (lss().valid())
		{
			for (size_t i=0; i<lss().found_set.size(); ++i)
			{
				_lexer().next_tok();
			}
		}
		else // if (!lss().valid())
		{
			_unexpected(some_tok_ident_map, lss().first_dup);
		}
	}

	inline auto _next_tok(LexerType* lexer=nullptr)
	{
		if (lexer == nullptr)
		{
			return _lexer().next_tok();
		}
		else // if (lexer != nullptr)
		{
			return lexer->next_tok();
		}
	}


	template<typename DerivedType, typename FirstFuncType,
		typename... RemFuncTypes>
	static auto _check_parse(DerivedType* self, FirstFuncType&& first_func,
		RemFuncTypes&&... rem_funcs)
	{
		self->_just_test = true;
		if ((self->*first_func)())
		{
			return first_func;
		}
		else if constexpr (sizeof...(rem_funcs))
		{
			return _check_parse(self, rem_funcs...);
		}
		return static_cast<FirstFuncType>(nullptr);
	}
	template<typename DerivedType, typename FuncType>
	static auto _check_parse(DerivedType* self,
		const std::vector<FuncType>& func_vec)
	{
		for (const auto& iter : func_vec)
		{
			self->_just_test = true;
			if ((self->*iter)())
			{
				return iter;
			}
		}
		return static_cast<FuncType>(nullptr);
	}

	template<typename DerivedType, typename FirstFuncType,
		typename... RemFuncTypes>
	static bool _opt_parse(DerivedType* self, FirstFuncType&& first_func,
		RemFuncTypes&&... rem_funcs)
	{
		self->_just_test = true;
		if ((self->*first_func)())
		{
			self->_just_test = false;
			(self->*first_func)();

			return true;
		}
		else if constexpr (sizeof...(rem_funcs))
		{
			return _opt_parse(self, rem_funcs...);
		}
		return false;
	}
	template<typename DerivedType, typename FuncType>
	static bool _opt_parse(DerivedType* self,
		const std::vector<FuncType>& func_vec)
	{
		for (const auto& iter : func_vec)
		{
			self->_just_test = true;
			if ((self->*iter)())
			{
				self->_just_test = false;
				(self->*iter)();

				return true;
			}
		}
		return false;
	}
	template<typename DerivedType, typename FirstFuncType,
		typename... RemFuncTypes>
	static bool _opt_parse_loop(DerivedType* self,
		FirstFuncType&& first_func, RemFuncTypes&&... rem_funcs)
	{
		bool found = false;
		while (_opt_parse(self, first_func, rem_funcs...))
		{
			found = true;
		}
		return found;
	}
	template<typename DerivedType, typename FuncType>
	static bool _opt_parse_loop(DerivedType* self,
		const std::vector<FuncType>& func_vec)
	{
		bool found = false;
		while (_opt_parse(self, func_vec))
		{
			found = true;
		}
		return found;
	}

	template<typename DerivedType, typename FirstFuncType,
		typename... RemFuncTypes>
	static void _req_parse(DerivedType* self,
		FirstFuncType&& first_func, RemFuncTypes&&... rem_funcs)
	{
		if (!_opt_parse(self, first_func, rem_funcs...))
		{
			self->_unexpected();
		}
	}
	template<typename DerivedType, typename FuncType>
	static void _req_parse(DerivedType* self,
		const std::vector<FuncType>& func_vec)
	{
		if (!_opt_parse(self, func_vec))
		{
			self->_unexpected();
		}
	}

	template<typename DerivedType, typename FirstFuncType,
		typename... RemFuncTypes>
	static void _req_parse_loop(DerivedType* self,
		FirstFuncType&& first_func, RemFuncTypes&&... rem_funcs)
	{
		bool found = false;
		while (_opt_parse(self, first_func, rem_funcs...))
		{
			found = true;
		}
		if (!found)
		{
			self->_unexpected();
		}
	}
	template<typename DerivedType, typename FuncType>
	static void _req_parse_loop(DerivedType* self,
		const std::vector<FuncType>& func_vec)
	{
		bool found = false;
		while (_opt_parse(self, func_vec))
		{
			found = true;
		}
		if (!found)
		{
			self->_unexpected();
		}
	}


	//inline void _syntax_error(const std::string& msg) const
	//{
	//	lex_src_code_chunk().syntax_error(msg);
	//}
	template<typename... ArgTypes>
	inline void _err(const LexerState* lex_state, ArgTypes&&... args)
	{
		_lexer().src_code_chunk(lex_state).err(sconcat(args...));
	}
	template<typename... ArgTypes>
	inline void _err(ArgTypes&&... args) const
	{
		_lexer().src_code_chunk().err(sconcat(args...));
	}
	template<typename... ArgTypes>
	inline void _warn(const LexerState* lex_state, ArgTypes&&... args)
	{
		_lexer().src_code_chunk(lex_state).warn(sconcat(args...));
	}
	template<typename... ArgTypes>
	inline void _warn(ArgTypes&&... args) const
	{
		_lexer().src_code_chunk().warn(sconcat(args...));
	}

	std::string _msg_for_expect(TokType tok,
		const TokToStringMap& some_tok_ident_map,
		const LexerState& lex_state) const
	{
		return sconcat("Expected token \"", some_tok_ident_map.at(tok),
			"\".  Have token \"", some_tok_ident_map.at(lex_state.tok()),
			"\" and string \"", lex_state.s(), "\"");
	}
	void _expect(TokType tok, const TokToStringMap& some_tok_ident_map,
		const LexerState& lex_state, bool perf_next_tok=true)
	{
		if (lex_state.tok() != tok)
		{
			_err(_msg_for_expect(tok, some_tok_ident_map, lex_state));
		}

		if (perf_next_tok)
		{
			_next_tok();
		}
	}
	void _expect(TokType tok, const TokToStringMap& some_tok_ident_map,
		LexerType* lexer=nullptr, bool perf_next_tok=true)
	{
		if (lexer != nullptr)
		{
			_expect(tok, some_tok_ident_map, lexer->state(),
				perf_next_tok);
		}
		else // if (lexer == nullptr)
		{
			_expect(tok, some_tok_ident_map, _lexer().state(),
				perf_next_tok);
		}
	}
	inline auto _wexpect(TokType tok,
		const TokToStringMap& some_tok_ident_map,
		LexerType* lexer=nullptr)
	{
		return WExpect(this, tok, some_tok_ident_map, lexer);
	}
	void _unexpected(const TokToStringMap& some_tok_ident_map,
		const LexerState& lex_state)
	{
		_err("Unexpected token \"", some_tok_ident_map.at(lex_state.tok()),
			"\".  Have string \"", lex_state.s(), "\"");
	}
	void _unexpected(const TokToStringMap& some_tok_ident_map,
		LexerType* lexer=nullptr)
	{
		if (lexer == nullptr)
		{
			_unexpected(some_tok_ident_map, _lexer().state());
		}
		else // if (lexer != nullptr)
		{
			_unexpected(some_tok_ident_map, lexer->state());
		}
	}
	bool _to_next_in_list(TokType end, TokType separator,
		const TokToStringMap& some_tok_ident_map,
		LexerType* lexer=nullptr)
	{
		if (cmp_lex_tok(end))
		{
			_next_tok(lexer);
			return false;
		}
		else if (cmp_lex_tok(separator))
		{
			_next_tok(lexer);
			return true;
		}
		else
		{
			_unexpected(some_tok_ident_map, lexer);
			return false;
		}
	}

	inline std::unique_ptr<LexerState> _dup_lex_state() const
	{
		return std::unique_ptr<LexerState>(new LexerState(_lex_state()));
	}
};

} // namespace lang

} // namespace liborangepower

#endif		// liborangepower_stateful_parser_base_class_hpp
