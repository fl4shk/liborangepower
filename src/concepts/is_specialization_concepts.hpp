#ifndef liborangepower_misc_is_specialization_concepts_hpp
#define liborangepower_misc_is_specialization_concepts_hpp

#include <concepts>

namespace liborangepower
{
namespace concepts
{

#define GEN_IS_SPECIALIZATION_CHECK_FUNCS(func_name, ContainerEtcType) \
	template<typename FirstType, typename... RemTypes> \
	extern uint8_t _ ## func_name ## _check (const FirstType&); \
	\
	template<typename FirstType, typename... RemTypes> \
	extern uint32_t _ ## func_name ## _check \
		(const ContainerEtcType<FirstType, RemTypes...>&) \

#define GEN_IS_SPECIALIZATION_FUNC_CONTENTS(func_name) \
	return (sizeof(_ ## func_name ## _check<FirstType, RemTypes...> \
		(std::declval<FirstType>())) \
		== sizeof(uint32_t))

//template<typename, template<typename...> typename>
//constexpr inline bool is_specialization = false;
//template<template<typename...> typename Type, typename... Args>
//constexpr inline bool is_specialization<Type<Args...>, Type> = true;

//template<typename Type, template<typename...> typename NonSpecType>
//constexpr inline bool is_specialization = false;

//template<typename Type>
//extern uint32_t _is_move_only_prev_curr_pair_func
//	(const MoveOnlyPrevCurrPair<Type>&);
//template<typename Type>
//extern uint8_t _is_move_only_prev_curr_pair_func(const Type&);
//
//template<typename Type>
//constexpr inline bool is_move_only_prev_curr_pair()
//{
//	return (sizeof(_is_move_only_prev_curr_pair_func(std::declval<Type>()))
//		== sizeof(uint32_t));
//}
//template<typename FirstArgType,
//	template<typename...> typename ContainerEtcType,
//	typename... RemArgTypes>
//extern uint32_t is_specialization
//	(const ContainerEtcType<FirstArgType, RemArgTypes...>&);
//template<typename Type,
//	template<typename...> typename ContainerEtcType,
//	typename... RemArgTypes>
//extern uint8_t is_specialization(const Type&);
//
//template<typename Type, template<typename...> typename ContainerEtcType,
//	typename... RemArgTypes>
//constexpr inline bool is_specialization 
//	= (sizeof(is_specialization<Type, ContainerEtcType, RemArgTypes...>
//		(std::declval<Type>()))
//		== sizeof(uint32_t));

template<typename FirstArgType,
	template<typename...> typename ContainerEtcType,
	typename... RemArgTypes>
extern uint8_t is_specialization(const FirstArgType&);

template<typename FirstArgType,
	template<typename...> typename ContainerEtcType,
	typename... RemArgTypes>
extern uint32_t is_specialization
	(const ContainerEtcType<FirstArgType, RemArgTypes...>&);

template<typename FirstArgType,
	template<typename...> typename ContainerEtcType,
	typename... RemArgTypes>
constexpr inline bool is_specialization()
{
	return (sizeof(is_specialization
		<FirstArgType, ContainerEtcType, RemArgTypes...>
		(std::declval<FirstArgType>()))
		== sizeof(uint32_t));
}

//template<typename FirstArgType,
//	template<typename> typename ContainerEtcType>
//extern uint8_t is_specialization(const FirstArgType&);
//
//template<typename FirstArgType,
//	template<typename> typename ContainerEtcType>
//extern uint32_t is_specialization
//	(const ContainerEtcType<FirstArgType>&);
//
//template<typename FirstArgType,
//	template<typename> typename ContainerEtcType>
//constexpr inline bool is_specialization()
//{
//	return (sizeof(is_specialization<FirstArgType, ContainerEtcType>
//		(std::declval<FirstArgType>()))
//		== sizeof(uint32_t));
//}

template<typename Type, template<typename...> typename NonSpecType>
concept IsSpecialization = is_specialization<Type, NonSpecType>();

} // namespace concepts
} // namespace liborangepower

#endif		// liborangepower_misc_is_specialization_concepts_hpp
