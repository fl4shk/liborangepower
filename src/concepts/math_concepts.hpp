#ifndef liborangepower_concepts_math_concepts_hpp
#define liborangepower_concepts_math_concepts_hpp

#include <cstdint>
#include <concepts>

namespace liborangepower
{
namespace concepts
{

template<typename T, typename OtherT>
concept HasNonBitwiseBinops = requires(T c, OtherT other)
{
	{ c + other } -> std::convertible_to<T>;
	{ c - other } -> std::convertible_to<T>;
	{ c * other } -> std::convertible_to<T>;
	{ c / other } -> std::convertible_to<T>;
};
template<typename T>
concept HasNonBitwiseUnops = requires(T c)
{
	{ +c } -> std::convertible_to<T>;
	{ -c } -> std::convertible_to<T>;
};

template<typename T, typename OtherT>
concept HasBitwiseBinops = requires(T c, OtherT other)
{
	{ c & other } -> std::convertible_to<T>;
	{ c | other } -> std::convertible_to<T>;
	{ c ^ other } -> std::convertible_to<T>;
	{ c << other } -> std::convertible_to<T>;
	{ c >> other } -> std::convertible_to<T>;
};
template<typename T>
concept HasBitwiseUnops = requires(T c)
{
	{ ~c } -> std::convertible_to<T>;
};

} // namespace concepts
} // namespace liborangepower

#endif		// liborangepower_concepts_math_concepts_hpp
