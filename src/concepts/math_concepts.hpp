#ifndef liborangepower_concepts_math_concepts_hpp
#define liborangepower_concepts_math_concepts_hpp

#include <cstdint>
#include <concepts>

namespace liborangepower {
namespace concepts {
//--------
template<typename T, typename OtherT=T, typename ConvT=T>
concept HasArithAsBinops = requires(T c, OtherT other) {
	{ c + other } -> std::convertible_to<ConvT>;
	{ c - other } -> std::convertible_to<ConvT>;
};

template<typename T, typename OtherT=T, typename ConvT=T>
concept HasArithMasBinops
= HasArithAsBinops<T, OtherT, ConvT>
&& requires(T c, OtherT other) {
	{ c * other } -> std::convertible_to<ConvT>;
};

template<typename T, typename OtherT=T, typename ConvT=T>
concept HasArithMdasBinops 
= HasArithAsBinops<T, OtherT, ConvT>
&& requires(T c, OtherT other) {
	{ c * other } -> std::convertible_to<ConvT>;
	{ c / other } -> std::convertible_to<ConvT>;
};

// The basic four arithmetic operators
template<typename T, typename OtherT=T, typename ConvT=T>
concept HasArithAllBinops
= HasArithAsBinops<T, OtherT, ConvT>
&& HasArithMdasBinops<T, OtherT, ConvT>
&& requires(T c, OtherT other) {
	{ c % other } -> std::convertible_to<ConvT>;
};

template<typename T, typename ConvT=T>
concept HasArithAUnop = requires(T c) {
	{ +c } -> std::convertible_to<ConvT>;
};
template<typename T, typename ConvT=T>
concept HasArithSUnop = requires(T c) {
	{ -c } -> std::convertible_to<ConvT>;
};

template<typename T, typename ConvT=T>
concept HasArithAsUnops
	= HasArithAUnop<T, ConvT> && HasArithSUnop<T, ConvT>;
//--------
template<typename T, typename OtherT=T>
concept HasCmpEqNeBinops = requires(T c, OtherT other) {
	{ c == other } -> std::convertible_to<bool>;
	{ c != other } -> std::convertible_to<bool>;
};

template<typename T, typename OtherT=T>
concept HasCmpLtBinop = requires(T c, OtherT other) {
	{ c < other } -> std::convertible_to<bool>;
};
template<typename T, typename OtherT=T>
concept HasCmpGtBinop = requires(T c, OtherT other) {
	{ c > other } -> std::convertible_to<bool>;
};
template<typename T, typename OtherT=T>
concept HasCmpLeBinop = requires(T c, OtherT other) {
	{ c <= other } -> std::convertible_to<bool>;
};
template<typename T, typename OtherT=T>
concept HasCmpGeBinop = requires(T c, OtherT other) {
	{ c >= other } -> std::convertible_to<bool>;
};

template<typename T, typename OtherT=T>
concept HasCmpInequBinops
	= HasCmpLtBinop<T, OtherT> && HasCmpGtBinop<T, OtherT>
	&& HasCmpLeBinop<T, OtherT> && HasCmpGeBinop<T, OtherT>;

template<typename T, typename OtherT=T>
concept HasCmpAllBinops
	= HasCmpEqNeBinops<T, OtherT> && HasCmpInequBinops<T, OtherT>;
//--------
template<typename T, typename OtherT=T, typename ConvT=T>
concept HasBitwNonShiftBinops = requires(T c, OtherT other) {
	{ c & other } -> std::convertible_to<ConvT>;
	{ c | other } -> std::convertible_to<ConvT>;
	{ c ^ other } -> std::convertible_to<ConvT>;
};
template<typename T, typename OtherT=T, typename ConvT=T>
concept HasBitwShiftBinops = requires(T c, OtherT other) {
	{ c << other } -> std::convertible_to<ConvT>;
	{ c >> other } -> std::convertible_to<ConvT>;
};
template<typename T, typename OtherT=T, typename ConvT=T>
concept HasBitwAllBinops
	= HasBitwNonShiftBinops<T, OtherT, ConvT>
	&& HasBitwShiftBinops<T, OtherT, ConvT>;

template<typename T, typename ConvT=T>
concept HasBitwUnops = requires(T c) {
	{ ~c } -> std::convertible_to<ConvT>;
};
//--------
template<typename T, typename ConvT=T>
concept HasArithSignMbrFunc = requires(T c) {
	{ c.sign() } -> std::convertible_to<ConvT>;
};
template<typename T, typename ConvT=T>
concept HasArithAbsMbrFunc = requires(T c) {
	{ c.abs() } -> std::convertible_to<ConvT>;
};
//--------
template<typename T, typename ConvT=T>
concept HasArithRecipMbrFunc = requires(T c) {
	{ c.recip() } -> std::convertible_to<ConvT>;
};
template<typename T, typename ConvT=T>
concept HasArithLongDblRecipOp = requires(T c) {
	{ 1.0l / c } -> std::convertible_to<ConvT>;
};
template<typename T, typename ConvT=T>
concept HasArithAnyRecipOp 
	= HasArithRecipMbrFunc<T, ConvT>
	|| HasArithLongDblRecipOp<T, ConvT>;
//--------
template<typename T, typename ConvT=T>
concept HasArithDiv2MbrFunc = requires(T c) {
	{ c.div_2() } -> std::convertible_to<ConvT>;
};
template<typename T, typename ConvT=T>
concept HasArithIntDiv2Op = requires(T c) {
	{ c / 2 } -> std::convertible_to<ConvT>;
};
template<typename T, typename ConvT=T>
concept HasArithAnyDiv2Op
	= HasArithDiv2MbrFunc<T, ConvT>
	|| HasArithIntDiv2Op<T, ConvT>;
//--------
template<typename T, typename ConvT=T>
concept HasArithSqrtMbrFunc = requires(T c) {
	{ c.sqrt() } -> std::convertible_to<ConvT>;
};
template<typename T, typename ConvT=T>
concept HasArithStdSqrtFunc = requires(T c) {
	{ std::sqrt(c) } -> std::convertible_to<ConvT>;
};
template<typename T, typename ConvT=T>
concept HasArithAnySqrtFunc
	= HasArithSqrtMbrFunc<T, ConvT>
	|| HasArithStdSqrtFunc<T, ConvT>;
//--------
} // namespace concepts
} // namespace liborangepower

#endif		// liborangepower_concepts_math_concepts_hpp
