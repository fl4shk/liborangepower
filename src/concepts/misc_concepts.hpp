#ifndef liborangepower_concepts_misc_concepts_hpp
#define liborangepower_concepts_misc_concepts_hpp

#include "../misc/misc_includes.hpp"

namespace liborangepower
{
namespace concepts
{

template<typename Type>
concept HasStaticKindStr = requires
{
	{ Type::KIND_STR } -> std::convertible_to<std::string>;
};

template<typename DerivedType, typename BaseType>
concept IsDerivedAndHasStaticKindStr 
	= std::derived_from<DerivedType, BaseType>
	&& HasStaticKindStr<DerivedType>;

template<typename Type>
concept IsConstexpr = requires()
{
	{ std::bool_constant<(Type{}, true)>() }
		-> std::same_as<std::true_type>;
};

} // namespace concepts
} // namespace liborangepower

#endif		// liborangepower_concepts_misc_concepts_hpp
