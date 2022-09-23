#ifndef liborangepower_math_misc_funcs_hpp
#define liborangepower_math_misc_funcs_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/math_concepts.hpp"

namespace liborangepower
{
namespace math
{
//--------
template<typename T>
constexpr inline const T& max_va(const T& arg_0, const T& arg_1)
	requires concepts::HasCmpLtBinop<T>
{
	return (arg_0 < arg_1) ? arg_1 : arg_0;
}

template<typename T>
constexpr inline const T& max_va(const T& arg_0, const T& arg_1,
	const std::same_as<T> auto&... rem_args)
	requires concepts::HasCmpLtBinop<T>
{
	return max_va<T>(max_va<T>(arg_0, arg_1), rem_args...);
}

template<typename T>
constexpr inline const T& min_va(const T& arg_0, const T& arg_1)
	requires concepts::HasCmpLtBinop<T>
{
	return (arg_0 < arg_1) ? arg_0 : arg_1;
}

template<typename T>
constexpr inline const T& min_va(const T& arg_0, const T& arg_1,
	const std::same_as<T> auto&... rem_args)
	requires concepts::HasCmpLtBinop<T>
{
	return min_va<T>(min_va<T>(arg_0, arg_1), rem_args...);
}
//--------
//template<typename T>
//constexpr inline T calc_sign(const T& s)
//{
//	if (s < T(0))
//	{
//		return T(-1);
//	}
//	else if (s == T(0))
//	{
//		return T(0);
//	}
//	else // if (s > T(0))
//	{
//		return T(1);
//	}
//};

template<typename T>
constexpr inline T clamp(const T& val, const T& min, const T& max)
	requires
	(concepts::HasCmpLtBinop<T> && concepts::HasCmpGtBinop<T>)
{
	//if (val < min)
	//{
	//	return min;
	//}
	//else if (min <= val && val <= max)
	//{
	//	return val;
	//}
	//else // if (val > max)
	//{
	//	return max;
	//}
	if (val < min)
	{
		return min;
	}
	else if (val > max)
	{
		return max;
	}
	else
	{
		return val;
	}
}

template<typename T>
constexpr inline auto cstm_sign(const T& val)
	requires 
	(std::integral<T> || std::floating_point<T>
	|| concepts::HasArithSignMbrFunc<T>
	|| concepts::HasCmpLtBinop<T>)
{
	if constexpr (std::integral<T> || std::floating_point<T>)
	{
		return std::signbit(val) ? T(-1) : T(1);
	}
	else if constexpr (concepts::HasArithSignMbrFunc<T>)
	{
		return val.sign();
	}
	else
	{
		return (val < T(0)) ? T(-1) : T(1);
	}
}

template<typename T>
constexpr inline auto cstm_abs(const T& val)
	requires
	(std::integral<T> || std::floating_point<T>
	|| concepts::HasArithAbsMbrFunc<T>
	|| (concepts::HasCmpLtBinop<T> && concepts::HasArithSUnop<T>))
{
	if constexpr (std::integral<T> || std::floating_point<T>)
	{
		return std::abs(val);
	}
	else if constexpr (concepts::HasArithAbsMbrFunc<T>)
	{
		return val.abs();
	}
	else
	{
		return (val < T(0)) ? -val : val;
	}
}

template<concepts::HasArithAnyRecipOp T>
constexpr inline auto recip(const T& val)
	requires (!std::integral<T>)
{
	if constexpr (concepts::HasArithRecipMbrFunc<T>)
	{
		return val.recip();
	}
	else
	{
		return
			1.0l / val;
			//= 1.0l / val;
			//= 1.0d / val;
			//= T(1) / val;
				// I'm pretty sure I don't want to use the above version,
				// as if there's no `T::recip()` member function, I'd most
				// likely want to use floating point arithmetic
		//return ret;
	}
}
template<concepts::HasArithAnyDiv2Op T>
constexpr inline auto div_2(const T& val)
{
	if constexpr (concepts::HasArithDiv2MbrFunc<T>)
	{
		return val.div_2();
	}
	else
	{
		return val / 2;
	}
}
template<concepts::HasArithAnySqrtFunc T>
constexpr inline auto cstm_sqrt(const T& val)
{
	if constexpr (concepts::HasArithSqrtMbrFunc<T>)
	{
		return val.sqrt();
	}
	else
	{
		return std::sqrt(val);
	}
}
//--------
//template<typename T>
//constexpr inline T max_va
//--------
} // namespace math
} // namespace liborangepower

#endif		// liborangepower_math_misc_funcs_hpp
