#ifndef liborangepower_concepts_std_container_concepts_hpp
#define liborangepower_concepts_std_container_concepts_hpp

#include "../misc/misc_includes.hpp"

namespace liborangepower
{
namespace concepts
{
//--------
template<typename T>
concept HasStdVecBasicIterFuncs = requires(T obj, typename T::size_type pos)
{
	{ obj.at(pos) } -> std::convertible_to<typename T::reference>;
	{ obj.at(pos) } -> std::convertible_to<typename T::const_reference>;
	{ obj.size() } -> std::convertible_to<typename T::size_type>;
};
//--------
//--------
} // namespace concepts
} // namespace liborangepower
#endif		// liborangepower_concepts_std_container_concepts_hpp
