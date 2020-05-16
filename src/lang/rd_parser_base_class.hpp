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

// A base class for parsing LL(1) grammars via recursive descent.
template<typename LexerType, typename DerivedType>
class RdParserBase
{
public:		// types
	//--------
	using TokType = LexerType::TokType;
	using LexerState = LexerType::State;

	using MembParseFunc = void (DerivedType::*)();

	// Mainly intended for use with lambdas
	using NonMembParseFunc = void (*)(DerivedType*);
	using ParseFunc = std::variant<MembParseFunc, NonMembParseFunc>;

	//using ParseAction = std::variant<TokType, ParseFunc>;

	//using RecurseParseRet = std::map<TokType, ParseFunc>;

	// Used for things like expression parsing.
	using TokSet = std::set<TokType>;
	using RgRulesRet = std::pair<std::map<TokType, 
		std::optional<ParseFunc>>, TokSet>;
	using RgrParseRet = std::pair<RgRulesRet, bool>;
	//--------

protected:		// variables
	std::string _filename, _text;
	std::unique_ptr<LexerType> _lexer;
	//bool _just_get_valid_next_token_set, _just_test, _just_parse;

	//std::stack<RgRulesRet*> _rg_rules_ret_stack;
	RgRulesRet* _rg_rules_ret = nullptr;
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
	GEN_GETTER_BY_VAL(just_rg_rules);

protected:		// functions
	inline void _call_parse_func(DerivedType* self,
		const ParseFunc& parse_func)
	{
		if (std::holds_alternative<MembParseFunc>(parse_func))
		{
			auto memb_parse_func = std::get<MembParseFunc>(parse_func);
			(self->*memb_parse_func)();
		}
		else // if (std::holds_alternative<NonMembParseFunc>(parse_func))
		{
			auto non_memb_parse_func = std::get<NonMembParseFunc>
				(parse_func);
			(*non_memb_parse_func)(self);
		}
	}
	inline auto _next_tok()
	{
		return _lexer->next_tok();
	}

	inline std::map<TokType, ParseFunc>& _rgr_ret_map()
	{
		return _rg_rules_ret->first;
	}

	// Ensure that there is only one layer deep of parsing funcs
	inline void _rg_rules_flatten(ParseFunc repl_parse_func,
		RgRulesRet* ret)
	{
		for (auto& p: ret->first)
		{
			p.second = repl_parse_func;
		}
	}

	// Used for things like expression parsing where the check for what
	// token yields what parsing rule can take place across multiple
	// parsing rules.
	inline void _recrs_get_rules(DerivedType* self,
		const ParseFunc& parse_func, RgRulesRet& ret)
	{
		// We shouldn't need nesting
		self->_just_rg_rules = true;

		const auto old_rg_rules_ret = self->_rg_rules_ret;
		self->_rg_rules_ret = &ret;

		_call_parse_func(self, parse_func);

		self->_rg_rules_ret = old_rg_rules_ret;

		for (const auto& p: ret->first)
		{
			ret->second.insert(p.first);
		}

		// We shouldn't need nesting
		self->_just_rg_rules = false;
	}

	inline RgrParseRet _rg_rules_parse(DerivedType* self,
		const ParseFunc& parse_func)
	{
		RgrParseRet ret;
		_recrs_get_rules(self, parse_func, ret.first);

		return _rg_rules_parse(self, ret);
	}
	inline RgrParseRet _rg_rules_parse(DerivedType* self,
		const ParseFunc& parse_func, const TokSet& extra_fail_tok_set)
	{
		RgrParseRet ret;
		_recrs_get_rules(self, parse_func, ret.first);

		return _rg_rules_parse(ret, self, extra_fail_tok_set);
	}

	inline void _post_rg_rules_parse(const RgrParseRet& rgr_parse_ret)
		const
	{
		if ((!rgr_parse_ret.second)
			&& (rgr_parse_ret.first.second.count(lex_tok()) == 0))
		{
			_inner_expect_fail(rgr_parse_ret.first.second);
		}
	}

private:		// functions
	inline RgrParseRet _rg_rules_parse(RgrParseRet& ret, DerivedType* self)
	{
		if (ret.first.first.count(lex_tok()) > 0)
		{
			_call_parse_func(self, ret.first.first.at(lex_tok()));
			ret.second = true;
		}
		else
		{
			ret.second = false;
		}

		return ret;
	}
	inline RgrParseRet _rg_rules_parse(RgrParseRet& ret, DerivedType* self,
		const TokSet& extra_fail_tok_set)
	{
		ret.first.second.merge(extra_fail_tok_set);

		return _rg_rules_parse(ret, self);
	}


private:		// functions
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

private:		// functions
	template<typename... RemArgTypes>
	bool _inner_sel_parse(TokSet& tok_set, DerivedType* self,
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
		TokSet tok_set;

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
