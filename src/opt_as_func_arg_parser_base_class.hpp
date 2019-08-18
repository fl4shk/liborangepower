#ifndef liborangepower_opt_as_func_arg_parser_base_class_hpp
#define liborangepower_opt_as_func_arg_parser_base_class_hpp

#include <vector>
#include <set>

namespace liborangepower
{

namespace lang
{

template<typename LexerType>
class OptAsFuncArgParserBase
{
public:		// types
	enum class Opt
	{
		JustParse,
		Exec,
	};

	using TwoStates = typename LexerType::TwoStates;
	using TokType = typename LexerType::TokType;

	class ParseRet final
	{
	private:		// variables
		bool _valid = true;
		std::vector<TwoStates> _lex_two_states_vec;
		std::set<TokType> _tok_set;
	public:		// functions
		inline ParseRet() = default;
		inline ParseRet(const ParseRet& to_copy) = default;
		inline ParseRet(ParseRet&& to_move) = default;
		inline ~ParseRet() = default;
		inline ParseRet& operator = (const ParseRet& to_copy) = default;
		inline ParseRet& operator = (ParseRet&& to_move) = default;

		inline void append_lex_two_states(const TwoStates& to_append)
		{
			_lex_two_states_vec.push_back(to_append);
		}
		inline void append_tok(TokType tok)
		{
			_tok_set.insert(tok);
		}
		inline void append_tok_set(const std::set<TokType>& to_append_set)
		{
			for (const auto& iter : to_append_set)
			{
				_tok_set.insert(iter);
			}
		}
		inline void append_parse_ret(const ParseRet& to_append)
		{
			if (!to_append.valid())
			{
				_valid = false;
			}
			for (const auto& iter : to_append.lex_two_states_vec())
			{
				_lex_two_states_vec.push_back(iter);
			}
			for (const auto& iter : to_append.tok_set())
			{
				_tok_set.insert(iter);
			}
		}

		GEN_GETTER_AND_SETTER_BY_VAL(valid)
		GEN_GETTER_BY_CON_REF(lex_two_states_vec)
		GEN_GETTER_BY_CON_REF(tok_set)
	};

	//template<typename DerivedType>
	//friend class SeqParse;

	//template<typename DerivedType>
	//class SeqParse
	//{
	//public:		// types
	//	using ParseFunc = ParseRet (DerivedType::*)(Opt opt);
	//	using SomeSeqParse = std::shared_ptr<SeqParse<DerivedType>>;
	//	using OneInst = std::variant<bool, ParseFunc, SomeSeqParse>;
	//	using Vec = std::vector<OneInst>;

	//protected:		// variables
	//	DerivedType* _self = nullptr;
	//	std::string _ident;
	//	Vec _vec;
	//	bool _optional = false;
	//public:		// functions
	//	SeqParse(DerivedType* s_self, Vec&& s_vec, bool s_optional=false)
	//		: _self(s_self), _ident(""), _vec(s_vec), _optional(s_optional)
	//	{
	//	}
	//	SeqParse(DerivedType* s_self, const std::string& s_ident,
	//		Vec&& s_vec, bool s_optional=false)
	//		: _self(s_self), _ident(s_ident), _vec(s_vec),
	//		_optional(s_optional)
	//	{
	//	}
	//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(SeqParse);
	//	virtual ~SeqParse() = default;

	//	virtual ParseRet operator () (Opt opt) const
	//	{
	//		switch (opt)
	//		{
	//		case Opt::JustParse:
	//			
	//		case Opt::Exec:
	//			for (const
	//		default:
	//			return ParseRet();
	//		}
	//	}
	//};

protected:		// variables
	LexerType _lexer;

public:		// functions
	inline OptAsFuncArgParserBase(const std::string& s_filename,
		std::string* s_text)
		: _lexer(s_filename, s_text)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(OptAsFuncArgParserBase);
	virtual inline ~OptAsFuncArgParserBase() = default;
};

} // namespace lang

} // namespace liborangepower

#endif		// liborangepower_opt_as_func_arg_parser_base_class_hpp
