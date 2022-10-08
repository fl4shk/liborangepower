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

namespace liborangepower {
namespace containers {
//--------
using concepts::is_specialization;
//--------
template<typename ToCheckT>
constexpr inline bool is_std_optional() {
	return is_specialization<ToCheckT, std::optional>();
}
//--------
template<typename FirstT, typename... RemTs>
extern uint8_t _is_std_unique_ptr_check(const FirstT&);

template<typename FirstT, typename... RemTs>
extern uint16_t _is_std_unique_ptr_check(
	const std::unique_ptr<FirstT, RemTs...>&
);

template<typename FirstT, typename... RemTs>
extern uint32_t _is_std_unique_ptr_check(
	const std::unique_ptr<FirstT[], RemTs...>&
);


template<typename ToCheckT>
constexpr inline bool is_std_unique_ptr_to_non_arr() {
	return (sizeof(_is_std_unique_ptr_check(std::declval<ToCheckT>()))
		== sizeof(uint16_t));
}
template<typename ToCheckT>
constexpr inline bool is_std_unique_ptr_to_arr() {
	return (sizeof(_is_std_unique_ptr_check(std::declval<ToCheckT>()))
		== sizeof(uint32_t));
}
template<typename ToCheckT>
constexpr inline bool is_any_std_unique_ptr() {
	return (is_std_unique_ptr_to_non_arr<ToCheckT>()
		|| is_std_unique_ptr_to_arr<ToCheckT>());
}
//--------
template<typename FirstT, typename... RemTs>
extern uint8_t _is_std_shared_ptr_check(const FirstT&);

template<typename FirstT, typename... RemTs>
extern uint16_t _is_std_shared_ptr_check(
	const std::shared_ptr<FirstT, RemTs...>&
);

template<typename FirstT, typename... RemTs>
extern uint32_t _is_std_shared_ptr_check(
	const std::shared_ptr<FirstT[], RemTs...>&
);


template<typename ToCheckT>
constexpr inline bool is_std_shared_ptr_to_non_arr() {
	return (sizeof(_is_std_shared_ptr_check(std::declval<ToCheckT>()))
		== sizeof(uint16_t));
}
template<typename ToCheckT>
constexpr inline bool is_std_shared_ptr_to_arr() {
	return (sizeof(_is_std_shared_ptr_check(std::declval<ToCheckT>()))
		== sizeof(uint32_t));
}
template<typename ToCheckT>
constexpr inline bool is_any_std_shared_ptr() {
	return (is_std_shared_ptr_to_non_arr<ToCheckT>()
		|| is_std_shared_ptr_to_arr<ToCheckT>());
}

template<typename FirstT, typename... RemTs>
extern uint8_t _is_std_weak_ptr_check(const FirstT&);

template<typename FirstT, typename... RemTs>
extern uint16_t _is_std_weak_ptr_check(
	const std::weak_ptr<FirstT, RemTs...>&
);

template<typename FirstT, typename... RemTs>
extern uint32_t _is_std_weak_ptr_check(
	const std::weak_ptr<FirstT[], RemTs...>&
);


template<typename ToCheckT>
constexpr inline bool is_std_weak_ptr_to_non_arr() {
	return (sizeof(_is_std_weak_ptr_check(std::declval<ToCheckT>()))
		== sizeof(uint16_t));
}
template<typename ToCheckT>
constexpr inline bool is_std_weak_ptr_to_arr() {
	return (sizeof(_is_std_weak_ptr_check(std::declval<ToCheckT>()))
		== sizeof(uint32_t));
}
template<typename ToCheckT>
constexpr inline bool is_any_std_weak_ptr() {
	return (is_std_weak_ptr_to_non_arr<ToCheckT>()
		|| is_std_weak_ptr_to_arr<ToCheckT>());
}
//--------
//GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTARGS(is_std_array, std::array);
template<typename T>
constexpr inline bool is_std_array() {
	//return IS_SPECIALIZATION_MACRO(is_std_array);
	//return concepts::is_specialization<T, std::array>();
	return is_specialization<T, std::array>();
}
//--------
template<typename T>
constexpr inline bool is_std_vector() {
	return is_specialization<T, std::vector>();
}

template<typename T>
constexpr inline bool is_std_deque() {
	return is_specialization<T, std::deque>();
}
template<typename T>
constexpr inline bool is_vec_like_std_container() {
	return (
		is_std_vector<T>()
		|| is_std_deque<T>()
	);
}
template<typename T>
constexpr inline bool is_arr_like_std_container() {
	return (
		is_std_array<T>()
		|| is_vec_like_std_container<T>()
	);
}
//--------
template<typename T>
constexpr inline bool is_std_set() {
	return is_specialization<T, std::set>();
}
template<typename T>
constexpr inline bool is_std_unordered_set() {
	return is_specialization<T, std::unordered_set>();
}

template<typename T>
constexpr inline bool is_set_like_std_container() {
	return (
		is_std_set<T>()
		|| is_std_unordered_set<T>()
	);
}
//--------
template<typename T>
constexpr inline bool is_std_map() {
	return is_specialization<T, std::map>();
}

template<typename T>
constexpr inline bool is_std_unordered_map() {
	//return(is_std_set);
	return is_specialization<T, std::unordered_map>();
}

template<typename T>
constexpr inline bool is_map_like_std_container() {
	return (
		is_std_map<T>()
		|| is_std_unordered_map<T>()
	);
}

template<typename T>
concept MapLikeStdContnr = is_map_like_std_container<T>();
//--------
template<typename T>
constexpr inline bool is_pseudo_vec_like_std_container() {
	return (
		//is_arr_like_std_container<T>()
		is_vec_like_std_container<T>()
		|| is_set_like_std_container<T>()
	);
}
template<typename T>
constexpr inline bool is_pseudo_arr_like_std_container() {
	return (
		is_arr_like_std_container<T>()
		|| is_pseudo_vec_like_std_container<T>()
	);
}
template<typename T>
constexpr inline bool is_basic_indexable_std_container() {
	return (
		is_pseudo_vec_like_std_container<T>()
		|| is_map_like_std_container<T>()
	);
}
//--------
} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_std_container_id_funcs_hpp
