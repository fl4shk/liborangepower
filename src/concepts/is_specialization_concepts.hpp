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
	CntnrEtcT, rem_cond) \
	template<typename T> \
	extern uint8_t _ ## func_name ## _check (const T&); \
	\
	template<typename T, \
		IF(rem_cond)(typename... RemTs, auto... RemTargs)> \
	extern uint32_t _ ## func_name ## _check \
		(const CntnrEtcT<T, \
		IF(rem_cond)(RemTs, RemTargs)...>&) \

#define GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTYPES(func_name, \
	CntnrEtcT) \
	_INTERNAL_GEN_IS_SPECIALIZATION_CHECK_FUNCS(func_name, \
		CntnrEtcT, 1)
#define GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTARGS(func_name, \
	CntnrEtcT) \
	_INTERNAL_GEN_IS_SPECIALIZATION_CHECK_FUNCS(func_name, \
		CntnrEtcT, 0)

#define IS_SPECIALIZATION_MACRO(func_name) \
	(sizeof(_ ## func_name ## _check(std::declval<T>())) \
		== sizeof(uint32_t))
//--------
template<template<typename...> typename CntnrEtcT,
	typename FirstArgT>
extern uint8_t _is_specialization_check(const FirstArgT&);

template<template<typename...> typename CntnrEtcT,
	typename FirstArgT, typename... RemArgTs>
extern uint32_t _is_specialization_check
	(const CntnrEtcT<FirstArgT, RemArgTs...>&);

template<typename ToCheckT,
	template<typename...> typename CntnrEtcT>
constexpr inline bool is_specialization()
{
	return (sizeof(_is_specialization_check<CntnrEtcT>
		(std::declval<ToCheckT>()))
		== sizeof(uint32_t));
}
//--------
template<template<typename, auto, auto...> typename CntnrEtcT,
	typename T>
extern uint8_t _is_specialization_check(const T&);

template<template<typename, auto, auto...> typename CntnrEtcT,
	typename T, auto FirstAutoArg, auto... RemAutoArgs>
extern uint32_t _is_specialization_check
	(const CntnrEtcT<T, FirstAutoArg, RemAutoArgs...>&);

template<typename ToCheckT,
	template<typename, auto, auto...> typename CntnrEtcT>
constexpr inline bool is_specialization()
{
	return (sizeof(_is_specialization_check<CntnrEtcT>
		(std::declval<ToCheckT>()))
		== sizeof(uint32_t));
}
//--------
template<typename T, template<typename...> typename CntnrEtcT>
concept IsSpecialization = is_specialization<T, CntnrEtcT>();

template<typename T,
	template<typename, auto, auto...> typename CntnrEtcT>
concept IsSpecializationRtArgs
	= is_specialization<T, CntnrEtcT>();
//--------
} // namespace concepts
} // namespace liborangepower

#endif		// liborangepower_misc_is_specialization_concepts_hpp
