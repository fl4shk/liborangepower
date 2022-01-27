#ifndef liborangepower_containers_std_container_id_funcs_hpp
#define liborangepower_containers_std_container_id_funcs_hpp

#include <cstdint>
#include <deque>
#include <map>
#include <set>

namespace liborangepower
{
namespace containers
{

template<typename Type>
extern uint32_t _is_std_vector_func(const std::vector<Type>&);
template<typename Type>
extern uint8_t _is_std_vector_func(const Type&);

template<typename Type>
constexpr inline bool is_std_vector()
{
	return (sizeof(_is_std_vector_func(std::declval<Type>()))
		== sizeof(uint32_t));
}

template<typename Type>
extern uint32_t _is_std_deque_func(const std::deque<Type>&);
template<typename Type>
extern uint8_t _is_std_deque_func(const Type&);

template<typename Type>
constexpr inline bool is_std_deque()
{
	return (sizeof(_is_std_deque_func(std::declval<Type>()))
		== sizeof(uint32_t));
}

template<typename Type>
extern uint32_t _is_std_set_func(const std::set<Type>&);
template<typename Type>
extern uint8_t _is_std_set_func(const Type&);

template<typename Type>
constexpr inline bool is_std_set()
{
	return (sizeof(_is_std_set_func(std::declval<Type>()))
		== sizeof(uint32_t));
}

template<typename Type>
constexpr inline bool is_basic_std_container()
{
	return (containers::is_std_vector<Type>()
		|| containers::is_std_deque<Type>()
		|| containers::is_std_set<Type>());
}

} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_std_container_id_funcs_hpp
