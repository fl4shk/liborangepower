#ifndef liborangepower_rd_parser_base_class_hpp
#define liborangepower_rd_parser_base_class_hpp

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

template<typename ParserType>
class ParseFuncStrDeferredRestorer;

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
		string _old_parse_func_str;
		bool _old_found_wanted_tok;
		TokSet _old_wanted_tok_set;

	public:		// functions
		inline PrologueAndEpilogue(RdParserBase* s_parser,
			string&& s_parse_func_str)
			: _parser(s_parser)
		{
			_old_parse_func_str = std::move(_parser->_parse_func_str);
			_parser->_parse_func_str = std::move(s_parse_func_str);

			_old_found_wanted_tok = _parser->_found_wanted_tok;
			_parser->_found_wanted_tok = false;

			_old_wanted_tok_set = std::move(_parser->_wanted_tok_set);
		}
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(PrologueAndEpilogue);
		inline ~PrologueAndEpilogue()
		{
			_parser->_parse_func_str = std::move(_old_parse_func_str);
			_parser->_found_wanted_tok = _old_found_wanted_tok;
			_parser->_wanted_tok_set = std::move(_old_wanted_tok_set);
		}
	};
	//--------

private:		// variables
	std::string _filename, _text;
	std::unique_ptr<LexerType> _lexer;

	string _parse_func_str;

	bool _just_get_valid_tokens = false;

	//bool _debug = false;

protected:		// variables
	bool _found_wanted_tok;
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
	inline DerivedType* _self()
	{
		return static_cast<DerivedType*>(this);
	}
	inline auto _next_tok()
	{
		return _lexer->next_tok();
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

	inline void _tok_set_merge(const ParseRet& to_merge_from)
	{
		// Check for duplicate tokens, i.e. a non-LL(1) grammar
		for (const auto& outer_item: _wanted_tok_set)
		{
			for (const auto& inner_item: *to_merge_from)
			{
				if (outer_item == inner_item)
				{
					_internal_err("_tok_set_merge", sconcat(":  ",
						"Duplicate token \"", _lexer->tok_to_string_map()
						.at(outer_item), "\"."));
				}
			}
		}

		TokSet temp_to_merge_from = *to_merge_from;

		_wanted_tok_set.merge(temp_to_merge_from);
	}

	inline bool _check_parse(const ParseFunc& parse_func)
	{
		_just_get_valid_tokens = true;
		const auto parse_ret = (_self()->*parse_func)();
		_just_get_valid_tokens = false;

		_tok_set_merge(parse_ret);

		return (parse_ret->count(lex_tok()) > 0);
	}

	inline bool _if_parse(const ParseFunc& parse_func)
	{
		if (_check_parse(parse_func))
		{
			_found_wanted_tok = true;
			(_self()->*parse_func)();
			return true;
		}
		else
		{
			return false;
		}
	}

	inline void _fail_if_not_found_wanted_tok() const
	{
		if (!_found_wanted_tok)
		{
			_inner_expect_fail(_wanted_tok_set);
		}
	}


	template<typename... RemArgTypes>
	inline std::optional<TokType> _cmp_lex_tok(TokType first_tok,
		RemArgTypes&&... rem_args) const
	{
		if (lex_tok() == first_tok)
		{
			return first_tok;
		}
		else if constexpr (sizeof...(rem_args) > 0)
		{
			return _cmp_lex_tok(rem_args...);
		}
		else
		{
			return std::nullopt;
		}
	}

	template<typename... RemArgTypes>
	inline std::optional<TokType> _cmp_prev_lex_tok(TokType first_tok,
		RemArgTypes&&... rem_args) const
	{
		if (prev_lex_tok() == first_tok)
		{
			return first_tok;
		}
		else if constexpr (sizeof...(rem_args) > 0)
		{
			return _cmp_lex_tok(rem_args...);
		}
		else
		{
			return std::nullopt;
		}
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

		if (_lexer->tok() == first_tok)
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
	void _expect(TokType first_tok, RemArgTypes&&... rem_args) const
	{
		TokSet tok_set;

		if (!_inner_expect(tok_set, first_tok, rem_args...))
		{
			_inner_expect_fail(tok_set);
		}
	}

//private:		// functions
//	template<typename... RemArgTypes>
//	bool _inner_sel_parse(TokSet& tok_set, TokType first_tok,
//		ParseFunc first_parse_func, RemArgTypes&&... rem_args)
//	{
//		tok_set.insert(first_tok);
//
//		if (_lexer->tok() == first_tok)
//		{
//			(_self()->*first_parse_func)();
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


#endif		// liborangepower_rd_parser_base_class_hpp
