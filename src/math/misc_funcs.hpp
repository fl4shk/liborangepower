#ifndef liborangepower_math_misc_funcs_hpp
#define liborangepower_math_misc_funcs_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/math_concepts.hpp"

namespace liborangepower
{
namespace math
{
//--------
template<typename FirstArgT, typename SecondArgT>
constexpr inline FirstArgT max_va(const FirstArgT& arg_0,
	const SecondArgT& arg_1)
{
	if (arg_0 >= arg_1)
	{
		return arg_0;
	}
	else
	{
		return arg_1;
	}
}

template<typename FirstArgT, typename SecondArgT, typename... RemTs>
constexpr inline FirstArgT max_va(const FirstArgT& arg_0, 
	const SecondArgT& arg_1, RemTs... remaining_args )
{
	return max_va(max_va(arg_0, arg_1), remaining_args...);
}


template<typename FirstArgT, typename SecondArgT>
constexpr inline FirstArgT min_va(const FirstArgT& arg_0, 
	const SecondArgT& arg_1)
{
	if (arg_0 <= arg_1)
	{
		return arg_0;
	}
	else
	{
		return arg_1;
	}
}

template<typename FirstArgT, typename SecondArgT, 
	typename... RemTs>
constexpr inline FirstArgT min_va(const FirstArgT& arg_0, 
	const SecondArgT& arg_1, RemTs... remaining_args )
{
	return min_va(min_va(arg_0, arg_1), remaining_args...);
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

template<concepts::HasCmpLtBinop T>
constexpr inline T cstm_sign(const T& val)
{
	return (val < T(0)) ? T(-1) : T(1);
}

template<typename T>
constexpr inline T cstm_abs(const T& val)
	requires
		concepts::HasCmpLtBinop<T>
		&& concepts::HasArithSUnop<T>
{
	return (val < T(0)) ? -val : val;
}

template<typename T>
constexpr inline T clamp(const T& val, const T& min, const T& max)
	requires
		concepts::HasCmpLtBinop<T> && concepts::HasCmpGtBinop<T>
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

//template<typename T>
//constexpr inline auto recip(const T& val)
//{
//	if constexpr (concepts::HasArithRecipMbrFunc<T>)
//	{
//		return val.recip();
//	}
//	else
//	{
//		return (1.0 / val);
//	}
//}
template<typename T>
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
//--------
//template<typename T>
//constexpr inline T max_va
//--------
} // namespace math
} // namespace liborangepower

#endif		// liborangepower_math_misc_funcs_hpp
