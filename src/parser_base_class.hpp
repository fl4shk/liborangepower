#ifndef liborangepower_parser_base_class_hpp
#define liborangepower_parser_base_class_hpp

// src/parser_base_class.hpp

#include "misc_includes.hpp"
#include "lexer_base_class.hpp"

namespace liborangepower
{

namespace lang
{

template<typename LexerType>
class ParserBase
{
public:		// types
	using TokType = typename LexerType::TokType;
	using LexerState = typename LexerType::State;
	using TokToStringMap = std::map<TokType, std::string>;

	class LexStateSets final
	{
	public:		// variables
		std::set<const LexerState> found_set, dup_set;
		LexerState first_dup, end;

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
	};

protected:		// variables
	LexStateSets _lss;
	bool _just_test = false;
	size_t _curr_file_index = 0;
	std::vector<std::string> _filename_vec;
	std::vector<std::string*> _text_vec;
	std::vector<LexerType> _lexer_vec;

public:		// functions
	ParserBase(std::vector<std::string>&& s_filename_vec)
		: _filename_vec(std::move(s_filename_vec))
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ParserBase)
	virtual ~ParserBase()
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

	GEN_GETTER_BY_VAL(curr_file_index)
	GEN_GETTER_BY_VAL(just_test)
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

	const std::vector<const LexerState> _next_n_tokens(size_t n,
		bool affect_lexer)
	{
		std::vector<const LexerState> ret;

		LexerType temp_lexer(_lexer());

		auto& lexer = (!affect_lexer) ? _lexer() : temp_lexer;

		for (size_t i=0; i<n; ++i)
		{
			ret.push_back(lexer.state());
			lexer._next_tok();
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
			!just_test());

		for (const auto& tok_iter : tokens)
		{
			auto update_lss = [&]() -> void
			{
				if (_lss.found_set.contains(tok_iter))
				{
					_lss.dup_set.insert(tok_iter);
					if (_lss.dup_set.size() == 1)
					{
						_lss.first_dup = tok_iter;
					}
				}
				_lss.found_set.insert(tok_iter);
			};

			if (prefix_set.contains(tok_iter.tok))
			{
				update_lss();
			}
			else if (tok_iter.tok == end)
			{
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
	inline void _next_lss_tokens(const TokToStringMap& some_tok_ident_map)
	{
		if (lss().valid())
		{
			for (size_t i=0; i<lss().found_set.size(); ++i)
			{
				_lexer()._next_tok();
			}
		}
		else // if (!lss().valid())
		{
			_unexpected(some_tok_ident_map, &lss().first_dup);
		}
	}

	inline auto _next_tok(LexerType* lexer=nullptr)
	{
		if (lexer == nullptr)
		{
			return _lexer().next_tok(just_test());
		}
		else // if (lexer != nullptr)
		{
			return lexer->next_tok(just_test());
		}
	}

	template<typename FirstFuncType, typename... RemFuncTypes>
	bool _do_parse(FirstFuncType&& first_func, RemFuncTypes&&... rem_funcs)
	{
		_just_test = false;
		if (std::mem_fn(first_func)(*this))
		{
			_just_test = true;
			std::mem_fn(first_func)(*this);

			return true;
		}
		else if constexpr (sizeof...(rem_funcs) != 0)
		{
			return _do_parse(rem_funcs...);
		}

		return false;
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
		const LexerState* lex_state=nullptr) const
	{
		return sconcat("Expected token ", some_tok_ident_map.at(tok),
			".  Have token ", some_tok_ident_map.at(lex_state->tok),
			" and string ", lex_state->s);
	}
	void _expect(TokType tok, const TokToStringMap& some_tok_ident_map,
		const LexerState* lex_state=nullptr)
	{
		if (tok)
		{
			_err(_msg_for_expect(tok, some_tok_ident_map, lex_state));
		}
		_next_tok();
	}
	void _unexpected(const TokToStringMap& some_tok_ident_map,
		const LexerState* some_lex_state=nullptr)
	{
		const LexerState* lex_state = (some_lex_state == nullptr)
			? &_lexer().state() : some_lex_state;
		_err("Unexpected token ", some_tok_ident_map.at(lex_state->tok),
			".  Have string ", lex_state->s);
	}
	bool _to_next_in_list(TokType end, TokType separator,
		const TokToStringMap& some_tok_ident_map)
	{
		if (cmp_lex_tok(end))
		{
			_next_tok();
			return false;
		}
		else if (cmp_lex_tok(separator))
		{
			_next_tok();
			return true;
		}
		else
		{
			_unexpected(some_tok_ident_map);
		}
	}
};

} // namespace lang

} // namespace liborangepower


#endif		// liborangepower_parser_base_class_hpp
