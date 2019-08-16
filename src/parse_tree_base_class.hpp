#ifndef liborangepower_parse_tree_base_class_hpp
#define liborangepower_parse_tree_base_class_hpp

#include "gmp_stuff.hpp"


#include <string>
#include <map>
#include <memory>

namespace liborangepower
{

namespace lang
{

template<typename SrcCodeChunkType, typename TokType>
class ParseTreeBase
{
public:		// types
	using Child = std::unique_ptr<ParseTreeBase>;
	using DataElem = variant<bool, std::string, bignum::BigNum, TokType>;

private:		// variables
	SrcCodeChunkType _src_code_chunk;
	std::string _ident;
	std::map<std::string, DataElem> _data;
	std::map<std::string, Child> _children;

public:		// functions
	inline ParseTreeBase(const SrcCodeChunkType& s_src_code_chunk)
		: _src_code_chunk(s_src_code_chunk)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ParseTreeBase);
	virtual inline ~ParseTreeBase() = default;

	GEN_GETTER_BY_CON_REF(src_code_chunk)
	GEN_GETTER_AND_SETTER_BY_CON_REF(ident)
	GEN_GETTERS_BY_CON_REF_AND_REF(data)
	GEN_GETTERS_BY_CON_REF_AND_REF(children)
};

} // namespace lang

} // namespace liborangepower

#endif		// liborangepower_parse_tree_base_class_hpp
