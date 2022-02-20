#ifndef liborangepower_containers_std_container_id_funcs_hpp
#define liborangepower_containers_std_container_id_funcs_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/is_specialization_concepts.hpp"

#include <deque>
#include <map>
#include <set>

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
GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTARGS(is_std_array, std::array);
template<typename Type>
constexpr inline bool is_std_array()
{
	GEN_IS_SPECIALIZATION_FUNC_CONTENTS(is_std_array);
}

GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTYPES(is_std_vector, std::vector);
template<typename Type>
constexpr inline bool is_std_vector()
{
	GEN_IS_SPECIALIZATION_FUNC_CONTENTS(is_std_vector);
}

GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTYPES(is_std_deque, std::deque);
template<typename Type>
constexpr inline bool is_std_deque()
{
	GEN_IS_SPECIALIZATION_FUNC_CONTENTS(is_std_deque);
}

GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTYPES(is_std_set, std::set);
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
