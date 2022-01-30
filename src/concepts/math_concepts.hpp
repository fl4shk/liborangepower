#ifndef liborangepower_concepts_math_concepts_hpp
#define liborangepower_concepts_math_concepts_hpp

#include <cstdint>
#include <concepts>

namespace liborangepower
{
namespace concepts
{

template<typename Type, typename OtherType>
concept HasNonBitwiseBinops = requires(Type c, OtherType other)
{
	{ c + other } -> std::convertible_to<Type>;
	{ c - other } -> std::convertible_to<Type>;
	{ c * other } -> std::convertible_to<Type>;
	{ c / other } -> std::convertible_to<Type>;
};
template<typename Type>
concept HasNonBitwiseUnops = requires(Type c)
{
	{ +c } -> std::convertible_to<Type>;
	{ -c } -> std::convertible_to<Type>;
};

template<typename Type, typename OtherType>
concept HasBitwiseBinops = requires(Type c, OtherType other)
{
	{ c & other } -> std::convertible_to<Type>;
	{ c | other } -> std::convertible_to<Type>;
	{ c ^ other } -> std::convertible_to<Type>;
	{ c << other } -> std::convertible_to<Type>;
	{ c >> other } -> std::convertible_to<Type>;
};
template<typename Type>
concept HasBitwiseUnops = requires(Type c)
{
	{ ~c } -> std::convertible_to<Type>;
};

} // namespace concepts
} // namespace liborangepower

#endif		// liborangepower_concepts_math_concepts_hpp
