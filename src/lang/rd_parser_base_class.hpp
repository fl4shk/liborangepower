#ifndef liborangepower_rd_parser_base_class_hpp
#define liborangepower_rd_parser_base_class_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_output_classes.hpp"
#include "../misc/misc_input_classes.hpp"
#include "../strings/sconcat_etc.hpp"
#include "file_pos_class.hpp"

#include <variant>
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

	using ParseFunc = void (DerivedType::*)();

	//using ParseAction = std::variant<TokType, ParseFunc>;

	//using RecurseParseRet = std::map<TokType, ParseFunc>;

	// Used for things like expression parsing.
	using RgRulesRet = std::pair<std::map<TokType, ParseFunc>,
		std::set<TokType>>;
	//--------

protected:		// variables
	std::string _filename, _text;
	std::unique_ptr<LexerType> _lexer;
	//bool _just_get_valid_next_token_set, _just_test, _just_parse;

	std::stack<RgRulesRet*> _rg_rules_ret_stack;
	bool _just_rg_rules = false;
	//std::stack<DerivedType*> _self_stack;

	bool _debug = false;

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

	GEN_GETTER_BY_CON_REF(filename);
	GEN_GETTER_BY_VAL(just_rg_rules);

protected:		// functions
	inline auto _next_tok()
	{
		return _lexer->next_tok();
	}

	inline std::map<TokType, ParseFunc>& _top_rgr_ret_map()
	{
		return _rg_rules_ret_stack.top()->first;
	}

private:		// functions
	// Used for things like expression parsing where the check for what
	// token yields what parsing rule can take place across multiple
	// parsing rules.
	inline void _recrs_get_rules(DerivedType* self, ParseFunc parse_func,
		RgRulesRet* ret)
	{
		const bool old_just_rg_rules = self->_just_rg_rules;
		self->_just_rg_rules = true;

		_rg_rules_ret_stack.push(ret);
		(self->*parse_func)();
		_rg_rules_ret_stack.pop();

		for (const auto& p: ret->first)
		{
			ret->second.insert(p.first);
		}

		self->_just_rg_rules = old_just_rg_rules;
	}

protected:		// functions
	void _recrs_parse(DerivedType* self, ParseFunc parse_func)
	{
		RgRulesRet rg_rules_ret;
		_recrs_get_rules(self, parse_func, &rg_rules_ret);

		if (rg_rules_ret.first.count(_lexer->tok()) > 0)
		{
			// This is so we don't have to keep doing this in the parsing
			// functions themselves.
			_next_tok();
			(self->*rg_rules_ret.first.at(_lexer->tok()))();
		}
		else
		{
			_inner_expect_fail(rg_rules_ret.second);
		}
	}

private:		// functions
	void _inner_expect_fail(std::set<TokType>& tok_set)
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

		file_pos().err(msg);
	}

	template<typename... RemArgTypes>
	bool _inner_expect(std::set<TokType>& tok_set, TokType first_tok,
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
		std::set<TokType> tok_set;

		if (!_inner_expect(tok_set, first_tok, rem_args...))
		{
			_inner_expect_fail(tok_set);
		}
	}

private:		// functions
	template<typename... RemArgTypes>
	bool _inner_sel_parse(std::set<TokType>& tok_set, DerivedType* self,
		TokType first_tok, ParseFunc first_parse_func,
		RemArgTypes&&... rem_args)
	{
		tok_set.insert(first_tok);

		if (_lexer->tok() == first_tok)
		{
			(self->*first_parse_func)();
			return true;
		}
		else if constexpr (sizeof...(rem_args) > 0)
		{
			return _inner_sel_parse(tok_set, self, rem_args...);
		}
		else
		{
			return false;
		}
	}

protected:		// functions
	template<typename... RemArgTypes>
	void _sel_parse(DerivedType* self, TokType first_tok,
		ParseFunc first_parse_func, RemArgTypes&&... rem_args)
	{
		std::set<TokType> tok_set;

		if (!_inner_sel_parse(tok_set, first_tok, first_parse_func,
			rem_args...))
		{
			_inner_expect_fail(tok_set);
		}
	}
};

} // namespace lang

} // namespace liborangepower


#endif		// liborangepower_rd_parser_base_class_hpp
