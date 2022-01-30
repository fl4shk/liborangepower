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

} // namespace concepts
} // namespace liborangepower

#endif		// liborangepower_concepts_misc_concepts_hpp
