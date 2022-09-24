#ifndef liborangepower_misc_is_specialization_concepts_hpp
#define liborangepower_misc_is_specialization_concepts_hpp

#include "../metaprog_defines.hpp"

#include <concepts>
#include <cstdint>

namespace liborangepower
{
namespace concepts
{
//--------
#define _INTERNAL_GEN_IS_SPECIALIZATION_CHECK_FUNCS(func_name, \
	ContnrEtcT, rem_cond) \
	template<typename T> \
	extern uint8_t _ ## func_name ## _check (const T&); \
	\
	template<typename T, \
		IF(rem_cond)(typename... RemTs, auto... RemTargs)> \
	extern uint32_t _ ## func_name ## _check \
		(const ContnrEtcT<T, \
		IF(rem_cond)(RemTs, RemTargs)...>&) \

#define GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTYPES(func_name, \
	ContnrEtcT) \
	_INTERNAL_GEN_IS_SPECIALIZATION_CHECK_FUNCS(func_name, \
		ContnrEtcT, 1)
#define GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTARGS(func_name, \
	ContnrEtcT) \
	_INTERNAL_GEN_IS_SPECIALIZATION_CHECK_FUNCS(func_name, \
		ContnrEtcT, 0)

#define IS_SPECIALIZATION_MACRO(func_name) \
	(sizeof(_ ## func_name ## _check(std::declval<T>())) \
		== sizeof(uint32_t))
//--------
template<template<typename...> typename ContnrEtcT,
	typename FirstArgT>
extern uint8_t _is_specialization_check(const FirstArgT&);

template<template<typename...> typename ContnrEtcT,
	typename FirstArgT, typename... RemArgTs>
extern uint32_t _is_specialization_check
	(const ContnrEtcT<FirstArgT, RemArgTs...>&);

template<typename ToCheckT,
	template<typename...> typename ContnrEtcT>
constexpr inline bool is_specialization()
{
	return (sizeof(_is_specialization_check<ContnrEtcT>
		(std::declval<ToCheckT>()))
		== sizeof(uint32_t));
}

template<typename T, template<typename...> typename ContnrEtcT>
concept IsSpecialization = is_specialization<T, ContnrEtcT>();
//--------
template<template<typename, auto, auto...> typename ContnrEtcT,
	typename T>
extern uint8_t _is_specialization_check(const T&);

template<template<typename, auto, auto...> typename ContnrEtcT,
	typename T, auto FirstAutoArg, auto... RemAutoArgs>
extern uint32_t _is_specialization_check
	(const ContnrEtcT<T, FirstAutoArg, RemAutoArgs...>&);

template<typename ToCheckT,
	template<typename, auto, auto...> typename ContnrEtcT>
constexpr inline bool is_specialization()
{
	return (sizeof(_is_specialization_check<ContnrEtcT>
		(std::declval<ToCheckT>()))
		== sizeof(uint32_t));
}

template<typename T,
	template<typename, auto, auto...> typename ContnrEtcT>
concept IsSpecializationRtArgs
	= is_specialization<T, ContnrEtcT>();
//--------
} // namespace concepts
} // namespace liborangepower

#endif		// liborangepower_misc_is_specialization_concepts_hpp
