#ifndef liborangepower_containers_std_container_id_funcs_hpp
#define liborangepower_containers_std_container_id_funcs_hpp

#include <cstdint>
#include <deque>
#include <map>
#include <set>
#include "../concepts/is_specialization_concepts.hpp"

namespace liborangepower
{
namespace containers
{

//template<typename FirstType, typename... RemTypes>
//constexpr inline bool is_std_vector()
//{
//	return misc_util::is_specialization
//		<FirstType, std::vector, RemTypes...>();
//}
//template<typename FirstType, typename... RemTypes>
//constexpr inline bool is_std_deque()
//{
//	return misc_util::is_specialization
//		<FirstType, std::deque, RemTypes...>();
//}
//template<typename FirstType, typename... RemTypes>
//constexpr inline bool is_std_set()
//{
//	return misc_util::is_specialization
//		<FirstType, std::set, RemTypes...>();
//}
GEN_IS_SPECIALIZATION_CHECK_FUNCS(is_std_vector, std::vector);
template<typename Type>
constexpr inline bool is_std_vector()
{
	GEN_IS_SPECIALIZATION_FUNC_CONTENTS(is_std_vector);
}

GEN_IS_SPECIALIZATION_CHECK_FUNCS(is_std_deque, std::deque);
template<typename Type>
constexpr inline bool is_std_deque()
{
	GEN_IS_SPECIALIZATION_FUNC_CONTENTS(is_std_deque);
}

GEN_IS_SPECIALIZATION_CHECK_FUNCS(is_std_set, std::set);
template<typename Type>
constexpr inline bool is_std_set()
{
	GEN_IS_SPECIALIZATION_FUNC_CONTENTS(is_std_set);
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

template<typename Type>
constexpr inline bool is_basic_std_container()
{
	return
	(
		is_vec_like_std_container<Type>()
		|| is_std_set<Type>()
	);
}

} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_std_container_id_funcs_hpp
