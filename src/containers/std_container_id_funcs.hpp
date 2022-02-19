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

template<typename Type>
constexpr inline bool is_std_vector()
{
	return misc_util::is_specialization<Type, std::vector>();
}
template<typename Type>
constexpr inline bool is_std_deque()
{
	 return misc_util::is_specialization<Type, std::deque>();
}
template<typename Type>
constexpr inline bool is_std_set()
{
	return misc_util::is_specialization<Type, std::set>();
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
		is_vec_like_std_container<Type>
		|| is_std_set<Type>
	);
}

} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_std_container_id_funcs_hpp
