#ifndef liborangepower_concepts_std_container_concepts_hpp
#define liborangepower_concepts_std_container_concepts_hpp

#include "../misc/misc_includes.hpp"

namespace liborangepower
{
namespace concepts
{
//--------
template<typename T>
concept HasStdVecBasicIterFuncs
	= requires()
{
	{ std::declval<typename T::reference>() };
	{ std::declval<typename T::const_reference>() };
	{ std::declval<typename T::size_type>() };
}
	&& requires(T c, typename T::size_type pos)
{
	{ c.at(pos) } -> std::convertible_to<typename T::reference>;
	{ c.at(pos) } -> std::convertible_to<typename T::const_reference>;
	{ c.size() } -> std::convertible_to<typename T::size_type>;
};

template<typename T>
concept HasStdVecPushBackFuncs
	= requires()
{
	{ std::declval<typename T::const_reference>() };
	{ std::declval<typename T::value_type&&>() };
}
	&& requires(T c, typename T::const_reference val_cr,
		typename T::value_type&& val_rr)
{
	{ c.push_back(val_cr) };
	{ c.push_back(std::move(val_rr)) };
};
//--------
//--------
} // namespace concepts
} // namespace liborangepower
#endif		// liborangepower_concepts_std_container_concepts_hpp
