#ifndef liborangepower_misc_is_specialization_concepts_hpp
#define liborangepower_misc_is_specialization_concepts_hpp

#include <concepts>

namespace liborangepower
{
namespace misc_util
{

template<typename, template<typename...> typename>
constexpr inline bool is_specialization = false;
template<template<typename...> typename Type, typename... Args>
constexpr inline bool is_specialization<Type<Args...>, Type> = true;

template<typename Type, template<typename...> typename NonSpecType>
concept IsSpecialization = is_specialization<Type, NonSpecType>;

} // namespace misc_util
} // namespace liborangepower

#endif		// liborangepower_misc_is_specialization_concepts_hpp
