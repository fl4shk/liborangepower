#ifndef liborangepower_containers_std_container_id_funcs_hpp
#define liborangepower_containers_std_container_id_funcs_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/is_specialization_concepts.hpp"

#include <memory>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

namespace liborangepower
{
namespace containers
{
using concepts::is_specialization;
//--------
template<typename FirstType, typename... RemTypes>
extern uint8_t _is_std_unique_ptr_check(const FirstType&);

template<typename FirstType, typename... RemTypes>
extern uint16_t _is_std_unique_ptr_check
	(const std::unique_ptr<FirstType, RemTypes...>&);

template<typename FirstType, typename... RemTypes>
extern uint32_t _is_std_unique_ptr_check
	(const std::unique_ptr<FirstType[], RemTypes...>&);


template<typename ToCheckType>
constexpr inline bool is_non_arr_std_unique_ptr()
{
	return (sizeof(_is_std_unique_ptr_check(std::declval<ToCheckType>()))
		== sizeof(uint16_t));
}
template<typename ToCheckType>
constexpr inline bool is_arr_std_unique_ptr()
{
	return (sizeof(_is_std_unique_ptr_check(std::declval<ToCheckType>()))
		== sizeof(uint32_t));
}
template<typename ToCheckType>
constexpr inline bool is_any_std_unique_ptr()
{
	return (is_non_arr_std_unique_ptr<ToCheckType>()
		|| is_arr_std_unique_ptr<ToCheckType>());
}
//--------
////GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTARGS(is_std_array, std::array);
//template<typename Type>
//constexpr inline bool is_std_array()
//{
//	//return IS_SPECIALIZATION_MACRO(is_std_array);
//	//return concepts::is_specialization<Type, std::array>();
//	return is_specialization<Type, std::array>();
//}
//--------
template<typename Type>
constexpr inline bool is_std_vector()
{
	return is_specialization<Type, std::vector>();
}

template<typename Type>
constexpr inline bool is_std_deque()
{
	return is_specialization<Type, std::deque>();
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
//template<typename Type>
//constexpr inline bool is_arr_like_std_container()
//{
//	return
//	(
//		is_std_array<Type>()
//		|| is_vec_like_std_container<Type>()
//	);
//}
//--------
template<typename Type>
constexpr inline bool is_std_set()
{
	return is_specialization<Type, std::set>();
}
template<typename Type>
constexpr inline bool is_std_unordered_set()
{
	return is_specialization<Type, std::unordered_set>();
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
	return is_specialization<Type, std::map>();
}

template<typename Type>
constexpr inline bool is_std_unordered_map()
{
	//return(is_std_set);
	return is_specialization<Type, std::unordered_map>();
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
constexpr inline bool is_pseudo_vec_like_std_container()
{
	return
	(
		//is_arr_like_std_container<Type>()
		is_vec_like_std_container<Type>()
		|| is_set_like_std_container<Type>()
	);
}
template<typename Type>
constexpr inline bool is_basic_indexable_std_container()
{
	return
	(
		is_pseudo_vec_like_std_container<Type>()
		|| is_map_like_std_container<Type>()
	);
}
//--------
} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_std_container_id_funcs_hpp
