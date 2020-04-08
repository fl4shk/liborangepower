#ifndef liborangepower_lang_lexer_base_class_hpp
#define liborangepower_lang_lexer_base_class_hpp

#include "../misc/misc_includes.hpp"
#include "../gmp_stuff/gmp_stuff.hpp"

namespace liborangepower
{

namespace lang
{

template<typename _TokType, typename _NumType=bignum::BigNum>
class LexerBase
{
public:		// types
	using TokType = _TokType;
	using NumType = _NumType;

	class State
	{
	friend class LexerBase<TokType, NumType>;

	private:		// variables
		TokType _tok;
		std::string _s;
		int _c;
		NumType _n;
		size_t _x = 0, _line_num = 1, _pos_in_line = 0;

	public:		// functions
		State()
		{
		}
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(State)
		~State()
		{
		}

		// This is just for sorting purposes (mainly for `std::set`)
		inline bool operator < (const State& other) const
		{
			return (_x < other._x);
			//std::map<std::string, bool> cmp_lt_results, cmp_eq_results;
			//cmp_lt_results["_tok"] = (_tok < other._tok);
			//cmp_eq_results["_tok"] = (_tok == other._tok);

			//cmp_lt_results["_s"] = (_s < other._s);
			//cmp_eq_results["_s"] = (_s == other._s);

			//cmp_lt_results["_c"] = (_c < other._c);
			//cmp_eq_results["_c"] = (_c == other._c);

			//cmp_lt_results["_n"] = (_n < other._n);
			//cmp_eq_results["_n"] = (_n == other._n);

			//cmp_lt_results["_x"] = (_x < other._x);
			//cmp_eq_results["_x"] = (_x == other._x);

			//cmp_lt_results["_line_num"] = (_line_num < other._line_num);
			//cmp_eq_results["_line_num"] = (_line_num == other._line_num);

			//cmp_lt_results["_pos_in_line"]
			//	= (_pos_in_line < other._pos_in_line);
			//cmp_eq_results["_pos_in_line"]
			//	= (_pos_in_line == other._pos_in_line);

			//for (const auto& iter: cmp_lt_results)
			//{
			//	if (iter.second)
			//	{
			//		return true;
			//	}
			//	else if (cmp_eq_results[iter.first])
			//	{
			//		continue;
			//	}
			//	break;
			//}
			//return false;

			//return (_tok < other._tok);
		}
		inline bool operator == (const State& other) const
		{
			return (_x == other._x);
			//return ((_tok == other._tok) && (_s == other._s)
			//	&& (_c == other._c)
			//	&& (_n == other._n) && (_x == other._x)
			//	&& (_line_num == other._line_num)
			//	&& (_pos_in_line == other._pos_in_line));
			//return (tok == other.tok);
		}
		inline bool operator != (const State& other) const
		{
			return (!((*this) == other));
		}

		GEN_GETTER_AND_SETTER_BY_VAL(tok)
		GEN_GETTER_AND_SETTER_BY_CON_REF(s)
		GEN_GETTER_AND_SETTER_BY_VAL(c)
		GEN_GETTER_AND_SETTER_BY_CON_REF(n)
		GEN_GETTER_AND_SETTER_BY_VAL(x)
		GEN_GETTER_AND_SETTER_BY_VAL(line_num)
		GEN_GETTER_AND_SETTER_BY_VAL(pos_in_line)
	};

	using TwoStates = std::pair<State, State>;

protected:		// variables
	std::string _filename;
	std::string* _text = nullptr;
	TwoStates _two_states;

public:		// functions
	inline LexerBase(const std::string& s_filename, std::string* s_text)
		: _filename(s_filename), _text(s_text)
	{
		//_next_tok(done_tok, comment_tok);
		_next_char();
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(LexerBase)
	virtual ~LexerBase() = default;


	template<typename Type>
	inline Type src_code_chunk(const TwoStates* other_two_states=nullptr)
		const
	{
		if (other_two_states != nullptr)
		{
			return Type(filename(), other_two_states->second._s,
				other_two_states->first._line_num,
				other_two_states->first._pos_in_line);
		}
		else
		{
			return Type(filename(), state()._s,
				prev_state()._line_num, prev_state()._pos_in_line);
		}
	}

	inline auto tok() const
	{
		return state()._tok;
	}
	inline const auto& s() const
	{
		return state()._s;
	}
	inline auto c() const
	{
		return state()._c;
	}
	inline const auto& n() const
	{
		return state()._n;
	}
	inline auto x() const
	{
		return state()._x;
	}
	inline auto line_num() const
	{
		return state()._line_num;
	}
	inline auto prev_line_num() const
	{
		return prev_state()._line_num;
	}
	inline auto pos_in_line() const
	{
		return state()._pos_in_line;
	}
	inline auto prev_pos_in_line() const
	{
		return prev_state()._pos_in_line;
	}

	inline const auto& prev_state() const
	{
		return two_states().first;
	}
	inline auto& prev_state()
	{
		return _two_states.first;
	}
	inline void set_prev_state(const State& n_prev_state)
	{
		_two_states.first = n_prev_state;
	}

	inline const auto& state() const
	{
		return two_states().second;
	}
	inline auto& state()
	{
		return _two_states.second;
	}
	inline void set_state(const State& n_state)
	{
		_two_states.second = n_state;
	}

	GEN_GETTER_BY_CON_REF(filename)
	GEN_GETTER_BY_VAL(text)
	GEN_GETTER_AND_SETTER_BY_CON_REF(two_states)

protected:		// functions
	void _next_tok(TokType comment_tok)
	{
		do
		{
			_eat_whitespace();
			_two_states.first = _two_states.second;
			_inner_next_tok();
		} while (tok() == comment_tok);

		//if (c() == EOF)
		//{
		//	_set_tok(done_tok, false);
		//}
	}
	void _next_char()
	{
		if (x() < text()->size())
		{
			state()._c = text()->at(state()._x++);

			++state()._pos_in_line;

			if (c() == '\n')
			{
				++state()._line_num;
				state()._pos_in_line = 1;
			}
		}
		else
		{
			state()._c = EOF;
		}
	}
	void _eat_whitespace()
	{
		while (isspace(c()) && (c() != EOF))
		{
			_next_char();
		}
	}
	void _set_tok(TokType n_tok, bool perf_next_char)
	{
		state()._tok = n_tok;

		if (perf_next_char)
		{
			_next_char();
		}
	}

	virtual void _inner_next_tok() = 0;

	inline bool _set_kw_tok
		(const std::map<TokType, std::string>& some_tok_ident_map)
	{
		for (const auto& iter: some_tok_ident_map)
		{
			if (s() == iter.second)
			{
				_set_tok(iter.first, false);
				return true;
			}
		}
		return false;
	}
};

} // namespace lang

} // namespace liborangepower


#endif		// liborangepower_lang_lexer_base_class_hpp
