#ifndef liborangepower_concepts_misc_concepts_hpp
#define liborangepower_concepts_misc_concepts_hpp

#include "../misc/misc_includes.hpp"

namespace liborangepower
{
namespace concepts
{

template<typename T>
concept HasStaticKindStr = requires
{
	{ T::KIND_STR } -> std::convertible_to<std::string>;
};

template<typename DerivedT, typename BaseT>
concept IsDerivedAndHasStaticKindStr 
	= std::derived_from<DerivedT, BaseT>
	&& HasStaticKindStr<DerivedT>;

template<typename T>
concept IsConstexpr = requires()
{
	{ std::bool_constant<(T{}, true)>() }
		-> std::same_as<std::true_type>;
};

} // namespace concepts
} // namespace liborangepower

#endif		// liborangepower_concepts_misc_concepts_hpp
