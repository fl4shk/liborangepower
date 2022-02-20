#ifndef liborangepower_misc_is_specialization_concepts_hpp
#define liborangepower_misc_is_specialization_concepts_hpp

#include "../metaprog_defines.hpp"

#include <concepts>
#include <cstdint>

namespace liborangepower
{
namespace concepts
{

#define _INTERNAL_GEN_IS_SPECIALIZATION_CHECK_FUNCS(func_name, \
	ContainerEtcType, rem_cond) \
	template<typename Type> \
	extern uint8_t _ ## func_name ## _check (const Type&); \
	\
	template<typename Type, \
		IF(rem_cond)(typename... RemTypes, auto... RemTargs)> \
	extern uint32_t _ ## func_name ## _check \
		(const ContainerEtcType<Type, \
		IF(rem_cond)(RemTypes, RemTargs)...>&) \

#define GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTYPES(func_name, \
	ContainerEtcType) \
	_INTERNAL_GEN_IS_SPECIALIZATION_CHECK_FUNCS(func_name, \
		ContainerEtcType, 1)
#define GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTARGS(func_name, \
	ContainerEtcType) \
	_INTERNAL_GEN_IS_SPECIALIZATION_CHECK_FUNCS(func_name, \
		ContainerEtcType, 0)

#define IS_SPECIALIZATION_MACRO(func_name) \
	(sizeof(_ ## func_name ## _check(std::declval<Type>())) \
		== sizeof(uint32_t))
//--------
template<template<typename...> typename ContainerEtcType,
	typename FirstArgType, typename... RemArgTypes>
extern uint8_t _is_specialization_check(const FirstArgType&);

template<template<typename...> typename ContainerEtcType,
	typename FirstArgType, typename... RemArgTypes>
extern uint32_t _is_specialization_check
	(const ContainerEtcType<FirstArgType, RemArgTypes...>&);

template<typename ToCheckType,
	template<typename...> typename ContainerEtcType>
constexpr inline bool is_specialization()
{
	return (sizeof(_is_specialization_check<ContainerEtcType>
		(std::declval<ToCheckType>()))
		== sizeof(uint32_t));
}
//--------
//template<template<typename, auto...> typename ContainerEtcType,
//	typename ArgType, auto... RemArgs>
//extern uint8_t _is_specialization_check(const ArgType&, bool);
//
//template<template<typename...> typename ContainerEtcType,
//	typename ArgType, auto... RemArgs>
//extern uint32_t _is_specialization_check
//	(const ContainerEtcType<ArgType, RemArgs...>&, bool);
//
//template<typename ToCheckType,
//	template<typename, auto...> typename ContainerEtcType>
//constexpr inline bool is_specialization()
//{
//	return (sizeof(_is_specialization_check<ContainerEtcType>
//		(std::declval<ToCheckType>(), true))
//		== sizeof(uint32_t));
//}
//--------
template<typename Type, template<typename...> typename ContainerEtcType>
concept IsSpecialization = is_specialization<Type, ContainerEtcType>();
//--------
} // namespace concepts
} // namespace liborangepower

#endif		// liborangepower_misc_is_specialization_concepts_hpp
