#ifndef liborangepower_concepts_math_concepts_hpp
#define liborangepower_concepts_math_concepts_hpp

#include <cstdint>
#include <concepts>

namespace liborangepower
{
namespace concepts
{
//--------
template<typename T, typename OtherT=T>
concept HasArithAsBinops = requires(T c, OtherT other)
{
	{ c + other } -> std::convertible_to<T>;
	{ c - other } -> std::convertible_to<T>;
};

template<typename T, typename OtherT=T>
concept HasArithMasBinops
	= HasArithAsBinops<T, OtherT>
	&& requires(T c, OtherT other)
{
	{ c * other } -> std::convertible_to<T>;
};

template<typename T, typename OtherT=T>
concept HasArithMdasBinops 
	= HasArithAsBinops<T, OtherT>
	&& requires(T c, OtherT other)
{
	{ c * other } -> std::convertible_to<T>;
	{ c / other } -> std::convertible_to<T>;
};

// The basic four arithmetic operators
template<typename T, typename OtherT=T>
concept HasArithAllBinops
	= HasArithAsBinops<T, OtherT>
	&& HasArithMdasBinops<T, OtherT>
	&& requires(T c, OtherT other)
{
	{ c % other } -> std::convertible_to<T>;
};

template<typename T>
concept HasArithAUnop = requires(T c)
{
	{ +c } -> std::convertible_to<T>;
};
template<typename T>
concept HasArithSUnop = requires(T c)
{
	{ -c } -> std::convertible_to<T>;
};

template<typename T>
concept HasArithAsUnops
	= HasArithAUnop<T> && HasArithSUnop<T>;

template<typename T>
concept HasArithRecipMbrFunc = requires(T c)
{
	{ c.recip() } -> std::convertible_to<T>;
};
//--------
template<typename T, typename OtherT=T>
concept HasCmpEqNeBinops = requires(T c, OtherT other)
{
	{ c == other } -> std::convertible_to<T>;
	{ c != other } -> std::convertible_to<T>;
};

template<typename T, typename OtherT=T>
concept HasCmpLtBinop = requires(T c, OtherT other)
{
	{ c < other } -> std::convertible_to<T>;
};
template<typename T, typename OtherT=T>
concept HasCmpGtBinop = requires(T c, OtherT other)
{
	{ c > other } -> std::convertible_to<T>;
};
template<typename T, typename OtherT=T>
concept HasCmpLeBinop = requires(T c, OtherT other)
{
	{ c <= other } -> std::convertible_to<T>;
};
template<typename T, typename OtherT=T>
concept HasCmpGeBinop = requires(T c, OtherT other)
{
	{ c >= other } -> std::convertible_to<T>;
};

template<typename T, typename OtherT=T>
concept HasCmpInequBinops
	= HasCmpLtBinop<T, OtherT> && HasCmpGtBinop<T, OtherT>
	&& HasCmpLeBinop<T, OtherT> && HasCmpGeBinop<T, OtherT>;

template<typename T, typename OtherT=T>
concept HasCmpAllBinops
	= HasCmpEqNeBinops<T, OtherT> && HasCmpInequBinops<T, OtherT>;
//--------
template<typename T, typename OtherT=T>
concept HasBitwNonShiftBinops = requires(T c, OtherT other)
{
	{ c & other } -> std::convertible_to<T>;
	{ c | other } -> std::convertible_to<T>;
	{ c ^ other } -> std::convertible_to<T>;
};
template<typename T, typename OtherT=T>
concept HasBitwShiftBinops = requires(T c, OtherT other)
{
	{ c << other } -> std::convertible_to<T>;
	{ c >> other } -> std::convertible_to<T>;
};
template<typename T, typename OtherT=T>
concept HasBitwAllBinops
	= HasBitwNonShiftBinops<T, OtherT>
	&& HasBitwShiftBinops<T, OtherT>;

template<typename T>
concept HasBitwUnops = requires(T c)
{
	{ ~c } -> std::convertible_to<T>;
};
//--------
//template<typename T>
//concept HasAbsMbrFunc = requires(T c)
//{
//	{ c.abs() } -> std::convertible_to<T>;
//};
//--------
} // namespace concepts
} // namespace liborangepower

#endif		// liborangepower_concepts_math_concepts_hpp
