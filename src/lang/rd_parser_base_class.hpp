#ifndef liborangepower_lang_rd_parser_base_class_hpp
#define liborangepower_lang_rd_parser_base_class_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_output_classes.hpp"
#include "../misc/misc_input_classes.hpp"
#include "../strings/sconcat_etc.hpp"
#include "file_pos_class.hpp"

#include <variant>
#include <optional>
#include <memory>
#include <fstream>
#include <string>
#include <map>
#include <set>

namespace liborangepower
{

using misc_output::printout;
using misc_output::printerr;
using misc_output::osprintout;
using strings::sconcat;

namespace lang
{

// A base class for parsing LL(1) grammars via recursive descent.
template<typename LexerType, typename DerivedType>
class RdParserBase
{
public:		// types
	//--------
	using TokType = LexerType::TokType;
	using LexerState = LexerType::State;

	using TokSet = std::set<TokType>;

	using ParseRet = std::optional<TokSet>;

	using ParseFunc = ParseRet (DerivedType::*)();
	//--------

	//--------
	friend class PrologueAndEpilogue;
	class PrologueAndEpilogue final
	{
	private:		// variables
		RdParserBase* _parser = nullptr;
		string _saved_parse_func_str;
		//TokSet _to_merge_tok_set;

	public:		// functions
		inline PrologueAndEpilogue(RdParserBase* s_parser,
			string&& s_parse_func_str)
			: _parser(s_parser)
		{
			_saved_parse_func_str = std::move(_parser->_parse_func_str);
			_parser->_parse_func_str = std::move(s_parse_func_str);
		}
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(PrologueAndEpilogue);
		inline ~PrologueAndEpilogue()
		{
			_parser->_parse_func_str = std::move(_saved_parse_func_str);
			//_parser->_wanted_tok_set_merge(_to_merge_tok_set);
		}

		GEN_GETTER_BY_CON_REF(saved_parse_func_str);
		//GEN_GETTER_AND_SETTER_BY_CON_REF(to_merge_tok_set);

		//inline void internal_err(const std::string& msg="") const
		//{
		//	_parser->_internal_err(_parser->_parse_func_str, msg);
		//}
	};
	//--------

protected:		// variables
	std::string _filename, _text;
	std::unique_ptr<LexerType> _lexer;

	string _parse_func_str;

	bool _just_get_valid_tokens = false;

	//bool _debug = false;

protected:		// variables
	//bool _found_wanted_tok;
	TokSet _wanted_tok_set;

public:		// functions
	inline RdParserBase(const std::string& s_filename)
		: _filename(s_filename)
	{
		if (auto&& f = std::ifstream(filename()); true)
		{
			_text = misc_input::get_istream_as_str(f);
		}
		
		_lexer.reset(new LexerType(_filename, &_text));
		_next_tok();

		//_lexer.reset(new LexerType(_filename, _text));
		//_next_tok();
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(RdParserBase);
	virtual inline ~RdParserBase() = default;

	inline FilePos lex_file_pos() const
	{
		return _lexer->file_pos();
	}
	inline auto lex_tok() const
	{
		return _lexer->tok();
	}
	inline const auto& lex_s() const
	{
		return _lexer->s();
	}
	inline const auto& lex_n() const
	{
		return _lexer->n();
	}

	inline auto prev_lex_tok() const
	{
		return _lexer->prev_state().tok();
	}
	inline const auto& prev_lex_s() const
	{
		return _lexer->prev_state().s();
	}
	inline const auto& prev_lex_n() const
	{
		return _lexer->prev_state().n();
	}

	GEN_GETTER_BY_CON_REF(filename);
	GEN_GETTER_BY_VAL(just_get_valid_tokens);

protected:		// functions
	inline ParseRet _call_parse_func(const ParseFunc& parse_func)
	{
		return (_self()->*parse_func)();
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline void _warn(const FilePos& some_file_pos,
		const FirstArgType& first_arg, RemArgTypes&&... rem_args) const
	{
		some_file_pos.warn(sconcat(first_arg, rem_args...));
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline void _lex_fp_warn(const FirstArgType& first_arg,
		RemArgTypes&&... rem_args) const
	{
		_warn(lex_file_pos(), first_arg, rem_args...);
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline void _err(const FilePos& some_file_pos, 
		const FirstArgType& first_arg, RemArgTypes&&... rem_args) const
	{
		some_file_pos.err(sconcat(first_arg, rem_args...));
	}
	template<typename FirstArgType, typename... RemArgTypes>
	inline void _lex_fp_err(const FirstArgType& first_arg,
		RemArgTypes&&... rem_args) const
	{
		_err(lex_file_pos(), first_arg, rem_args...);
	}

	inline DerivedType* _self()
	{
		return static_cast<DerivedType*>(this);
	}
	inline auto _next_tok()
	{
		return _lexer->next_tok();
	}

	template<typename... ArgTypes>
	inline void _pfs_internal_err(const ArgTypes&... args) const
	{
		_internal_err(_parse_func_str, sconcat(args...));
	}
	virtual inline void _internal_err(const std::string& func_str,
		const std::string& msg="") const
	{
		string full_msg = sconcat(func_str, "():  Internal error");
		if (msg.size() == 0)
		{
			full_msg += ".";
		}
		else // if (msg.size() > 0)
		{
			full_msg += sconcat(":  ", msg);
		}

		lex_file_pos().err(full_msg);
	}

	inline void _tok_set_merge(TokSet& tok_set,
		const TokSet& to_merge_from)
	{
		// Check for duplicate tokens, i.e. a non-LL(1) grammar, and
		// spit out an error if duplicate tokens were found.
		for (const auto& outer_item: tok_set)
		{
			for (const auto& inner_item: to_merge_from)
			{
				if (outer_item == inner_item)
				{
					_internal_err("_tok_set_merge", sconcat(":  ",
						"Duplicate token \"", _lexer->tok_to_string_map()
						.at(outer_item), "\"."));
				}
			}
		}

		TokSet temp_to_merge_from = to_merge_from;

		tok_set.merge(temp_to_merge_from);
	}

	inline void _wanted_tok_set_merge(const TokSet& to_merge_from)
	{
		_tok_set_merge(_wanted_tok_set, to_merge_from);
	}

	inline void _tok_set_merge(TokSet& tok_set,
		const ParseRet& to_merge_from)
	{
		_tok_set_merge(tok_set, *to_merge_from);
	}
	inline void _wanted_tok_set_merge(const ParseRet& to_merge_from)
	{
		_wanted_tok_set_merge(*to_merge_from);
	}

private:		// functions
	inline ParseRet _inner_check_parse(TokSet& tok_set,
		const ParseFunc& parse_func)
	{
		const bool old_just_get_valid_tokens = just_get_valid_tokens();
		_just_get_valid_tokens = true;
		const auto ret = _call_parse_func(parse_func);
		_just_get_valid_tokens = old_just_get_valid_tokens;

		_tok_set_merge(tok_set, ret);

		return ret;
	}
	template<typename... RemFuncTypes>
	inline std::optional<ParseFunc> _check_parse(TokSet& tok_set,
		const ParseFunc& first_func, RemFuncTypes&&... rem_funcs)
	{
		const auto parse_ret = _inner_check_parse(tok_set, first_func);

		if (parse_ret->count(lex_tok()) > 0)
		{
			//_found_wanted_tok = true;
			return first_func;
		}
		else if constexpr (sizeof...(rem_funcs) > 0)
		{
			return _check_parse(tok_set, rem_funcs...);
		}
		else
		{
			return std::nullopt;
		}
	}

protected:		// functions
	template<typename... RemFuncTypes>
	inline bool _check_parse(const ParseFunc& first_func,
		RemFuncTypes&&... rem_funcs)
	{
		return _check_parse(_wanted_tok_set, first_func, rem_funcs...);
	}

private:		// functions
	template<typename... RemArgTypes>
	inline void _inner_get_valid_tok_set(TokSet& ret,
		const ParseFunc& first_parse_func, RemArgTypes&&... rem_args)
	{
		_inner_check_parse(ret, first_parse_func);

		if constexpr (sizeof...(rem_args) > 0)
		{
			_inner_get_valid_tok_set(ret, rem_args...);
		}
	}

protected:		// functions
	template<typename... RemArgTypes>
	inline TokSet _get_valid_tok_set(const ParseFunc& first_parse_func,
		RemArgTypes&&... rem_args)
	{
		TokSet ret;
		_inner_get_valid_tok_set(ret, first_parse_func, rem_args...);
		return ret;
	}

//private:		// functions
//	inline bool _inner_attempt_parse(const ParseFunc& parse_func)
//	{
//		//_wanted_tok_set_merge(_get_valid_tok_set(parse_func));
//
//		if (_check_parse(parse_func))
//		{
//			_call_parse_func(parse_func);
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}

protected:		// functions
	//inline bool _attempt_parse_basic(const ParseFunc& parse_func)
	//{
	//	_wanted_tok_set.clear();
	//	return _inner_attempt_parse(parse_func);
	//}
	inline bool _attempt_parse(const ParseFunc& parse_func)
	{
		//_wanted_tok_set_merge(_get_valid_tok_set(parse_func));
		//return _inner_attempt_parse(parse_func);
		if (_check_parse(parse_func))
		{
			_call_parse_func(parse_func);
			return true;
		}
		else
		{
			return false;
		}
	}
	//inline bool _attempt_parse_opt(const ParseFunc& parse_func)
	//{
	//	const bool ret = _inner_attempt_parse(parse_func);
	//	if (!ret)
	//	{
	//		_wanted_tok_set_merge(_get_valid_tok_set(parse_func);
	//	}
	//	return ret;
	//}

	//inline void _fail_if_not_found_wanted_tok() const
	//{
	//	if (!_found_wanted_tok)
	//	{
	//		_expect(_wanted_tok_set);
	//	}
	//}

private:		// functions
	template<typename... RemArgTypes>
	inline std::optional<TokType> _cmp_tok(TokType to_cmp,
		TokType first_tok, RemArgTypes&&... rem_args) const
	{
		if (to_cmp == first_tok)
		{
			return first_tok;
		}
		else if constexpr (sizeof...(rem_args) > 0)
		{
			return _cmp_tok(to_cmp, rem_args...);
		}
		else
		{
			return std::nullopt;
		}
	}
	inline std::optional<TokType> _cmp_tok(TokType to_cmp,
		const TokSet& tok_set) const
	{
		for (const auto& tok: tok_set)
		{
			if (to_cmp == tok)
			{
				return tok;
			}
		}

		return std::nullopt;
	}

protected:		// functions
	template<typename... RemArgTypes>
	inline std::optional<TokType> _cmp_lex_tok(TokType first_tok,
		RemArgTypes&&... rem_args) const
	{
		return _cmp_tok(lex_tok, first_tok, rem_args...);
	}
	inline std::optional<TokType> _cmp_lex_tok(const TokSet& tok_set)
		const
	{
		return _cmp_tok(lex_tok(), tok_set);
	}

	template<typename... RemArgTypes>
	inline std::optional<TokType> _cmp_prev_lex_tok(TokType first_tok,
		RemArgTypes&&... rem_args) const
	{
		return _cmp_tok(prev_lex_tok, first_tok, rem_args...);
	}
	inline std::optional<TokType> _cmp_prev_lex_tok(const TokSet& tok_set)
		const
	{
		return _cmp_tok(prev_lex_tok(), tok_set);
	}

	void _inner_expect_fail(const TokSet& tok_set) const
	{
		std::string msg = sconcat("Expected one of the following tokens:",
			"  {");

		decltype(tok_set.size()) i = 0;

		for (const auto& p: tok_set)
		{
			msg += _lexer->tok_to_string_map().at(p);

			if ((i + 1) < tok_set.size())
			{
				msg += ", ";
			}

			++i;
		}

		msg += sconcat("}");

		lex_file_pos().err(msg);
	}

private:		// functions
	template<typename... RemArgTypes>
	bool _inner_expect(TokSet& tok_set, TokType first_tok,
		RemArgTypes&&... rem_args) const
	{
		tok_set.insert(first_tok);

		if (lex_tok() == first_tok)
		{
			return true;
		}
		else if constexpr (sizeof...(rem_args) > 0)
		{
			return _inner_expect(tok_set, rem_args...);
		}
		else
		{
			return false;
		}
	}

protected:		// functions
	template<typename... RemArgTypes>
	void _expect(TokType first_tok, RemArgTypes&&... rem_args)
	{
		TokSet tok_set;

		if (!_inner_expect(tok_set, first_tok, rem_args...))
		{
			_tok_set_merge(tok_set, _wanted_tok_set);
			_inner_expect_fail(tok_set);
		}

		_wanted_tok_set.clear();
	}
	void _expect_wanted_tok()
	{
		if (!_cmp_lex_tok(_wanted_tok_set))
		{
			_inner_expect_fail(_wanted_tok_set);
		}

		_wanted_tok_set.clear();
	}
	//inline void _expect_wanted_tok(const TokSet& extra_wanted_tok_set)
	//{
	//	_wanted_tok_set_merge(extra_wanted_tok_set);
	//	_expect_wanted_tok();
	//}

//private:		// functions
//	template<typename... RemArgTypes>
//	bool _inner_sel_parse(TokSet& tok_set, TokType first_tok,
//		ParseFunc first_parse_func, RemArgTypes&&... rem_args)
//	{
//		tok_set.insert(first_tok);
//
//		if (_lexer->tok() == first_tok)
//		{
//			_call_parse_func(parse_func);
//			return true;
//		}
//		else if constexpr (sizeof...(rem_args) > 0)
//		{
//			return _inner_sel_parse(tok_set, rem_args...);
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//protected:		// functions
//	template<typename... RemArgTypes>
//	void _sel_parse(TokType first_tok, ParseFunc first_parse_func,
//		RemArgTypes&&... rem_args)
//	{
//		TokSet tok_set;
//
//		if (!_inner_sel_parse(tok_set, first_tok, first_parse_func,
//			rem_args...))
//		{
//			_inner_expect_fail(tok_set);
//		}
//	}
};


} // namespace lang

} // namespace liborangepower


#endif		// liborangepower_lang_rd_parser_base_class_hpp
