#ifndef liborangepower_containers_std_container_id_funcs_hpp
#define liborangepower_containers_std_container_id_funcs_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/is_specialization_concepts.hpp"

#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

namespace liborangepower
{
namespace containers
{
//--------
GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTARGS(is_std_array, std::array);
template<typename Type>
constexpr inline bool is_std_array()
{
	return IS_SPECIALIZATION_MACRO(is_std_array);
	//return concepts::is_specialization<Type, std::array>();
	//return concepts::is_specialization_rtargs<Type, std::array>();
}
//--------
template<typename Type>
constexpr inline bool is_std_vector()
{
	return concepts::is_specialization<Type, std::vector>();
}

template<typename Type>
constexpr inline bool is_std_deque()
{
	return concepts::is_specialization<Type, std::deque>();
}
template<typename Type>
constexpr inline bool is_vec_like_std_container()
{
	return
	(
		is_std_vector<Type>()
		|| is_std_deque<Type>()
	);
}
//--------
template<typename Type>
constexpr inline bool is_std_set()
{
	return concepts::is_specialization<Type, std::set>();
}
template<typename Type>
constexpr inline bool is_std_unordered_set()
{
	return concepts::is_specialization<Type, std::unordered_set>();
}

template<typename Type>
constexpr inline bool is_set_like_std_container()
{
	return
	(
		is_std_set<Type>()
		|| is_std_unordered_set<Type>()
	);
}
//--------
template<typename Type>
constexpr inline bool is_std_map()
{
	return concepts::is_specialization<Type, std::map>();
}

template<typename Type>
constexpr inline bool is_std_unordered_map()
{
	//return(is_std_set);
	return concepts::is_specialization<Type, std::unordered_map>();
}

template<typename Type>
constexpr inline bool is_map_like_std_container()
{
	return
	(
		is_std_map<Type>()
		|| is_std_unordered_map<Type>()
	);
}
//--------
template<typename Type>
constexpr inline bool is_basic_std_container()
{
	return
	(
		is_vec_like_std_container<Type>()
		|| is_set_like_std_container<Type>()
		|| is_map_like_std_container<Type>()
	);
}
//--------
} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_std_container_id_funcs_hpp
