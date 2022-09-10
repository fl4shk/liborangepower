#ifndef liborangepower_math_fixed_pt_class_hpp
#define liborangepower_math_fixed_pt_class_hpp

#include "../misc/misc_includes.hpp"
#include "misc_funcs.hpp"
#include "misc_types.hpp"

namespace liborangepower
{

using bitwise::width_of_type;

namespace math
{
//--------
// A class implementing fixed-point arithmetic with `constexpr` functions.
// Of course, this can be used in runtime code.
template<std::integral _IntT, size_t _FRAC_WIDTH>
class CxFixedPt final
{
public:		// types
	using IntT = _IntT;

	class CtorArgs final
	{
	public:		// variables
		IntT data;
	};
public:		// constants
	static constexpr size_t
		INT_T_WIDTH = width_of_type<IntT>();
	static constexpr size_t
		FRAC_WIDTH = _FRAC_WIDTH,
		WHOLE_WIDTH = INT_T_WIDTH - FRAC_WIDTH;

	//template<size_t OTHER_FRAC_WIDTH>
	//static constexpr size_t SHIFT_AMOUNT
	//	= FRAC_WIDTH > OTHER_FRAC_WIDTH
	//	? FRAC_WIDTH - OTHER_FRAC_WIDTH
	//	: OTHER_FRAC_WIDTH - FRAC_WIDTH;

	static_assert(FRAC_WIDTH < INT_T_WIDTH,
		"`FRAC_WIDTH >= INT_T_WIDTH`");
public:		// types
	using MaxIntT 
		= PickT
		<
			std::unsigned_integral<IntT>,
			uintmax_t,
			intmax_t
		>;
	//using RecipCxFixedPt = CxFixedPt<MaxIntT, FRAC_WIDTH * 2>::CtorArgs;
	//using RecipCxFixedPt = CxFixedPt<MaxIntT, FRAC_WIDTH * 2>;
public:		// variables
	IntT data = 0;
public:		// functions
	//--------
	constexpr inline CxFixedPt()
	{
	}
	constexpr inline CxFixedPt(const CtorArgs& ctor_args)
		: data(ctor_args.data)
	{
	}
	//--------
	explicit constexpr inline CxFixedPt(std::integral auto to_conv)
		: data(to_conv << FRAC_WIDTH)
	{
	}

	template<std::integral OtherIntT, size_t OTHER_FRAC_WIDTH>
	explicit constexpr inline CxFixedPt
		(const CxFixedPt<OtherIntT, OTHER_FRAC_WIDTH>& to_conv)
	{
		constexpr size_t
			OTHER_INT_T_WIDTH = width_of_type<OtherIntT>();
			//OTHER_WHOLE_BITS = OTHER_INT_T_WIDTH - OTHER_FRAC_WIDTH;
		constexpr int
			MY_SHIFT_AMOUNT = OTHER_FRAC_WIDTH - FRAC_WIDTH;

		if constexpr (MY_SHIFT_AMOUNT < 0)
		{
			// Do the conversion with the larger type 
			if constexpr (OTHER_INT_T_WIDTH > INT_T_WIDTH)
			{
				data = to_conv.data << (-MY_SHIFT_AMOUNT);
			}
			else // if constexpr (OTHER_INT_T_WIDTH <= INT_T_WIDTH)
			{
				data = to_conv.data;
				data <<= -MY_SHIFT_AMOUNT;
			}
		}
		else if constexpr (MY_SHIFT_AMOUNT > 0)
		{
			data = to_conv.data >> MY_SHIFT_AMOUNT;
		}
		else
		{
			data = to_conv.data;
		}
	}
	//--------
	constexpr inline CxFixedPt(const CxFixedPt&) = default;
	constexpr inline CxFixedPt& operator = (const CxFixedPt&) = default;
	constexpr inline ~CxFixedPt() = default;
	//--------
	template<std::integral CastIntT>
	explicit constexpr inline operator CastIntT () const
	{
		return data >> FRAC_WIDTH;
	}
	//--------
	constexpr inline CxFixedPt operator + (const CxFixedPt& other) const
	{
		return CxFixedPt(data + other.data);
	}
	constexpr inline CxFixedPt& operator += (const CxFixedPt& other) const
	{
		*this = *this + other;
		return *this;
	}

	constexpr inline CxFixedPt operator - (const CxFixedPt& other) const
	{
		return CxFixedPt(data - other.data);
	}
	constexpr inline CxFixedPt& operator -= (const CxFixedPt& other) const
	{
		*this = *this - other;
		return *this;
	}

	constexpr inline CxFixedPt operator * (const CxFixedPt& other) const
	{
		return CxFixedPt((MaxIntT(data) * MaxIntT(other.data))
			>> FRAC_WIDTH);
	}
	constexpr inline CxFixedPt& operator *= (const CxFixedPt& other) const
	{
		*this = *this * other;
		return *this;
	}

	constexpr inline CxFixedPt operator / (const CxFixedPt& other) const
	{
		return CxFixedPt((MaxIntT(data) << FRAC_WIDTH)
			/ MaxIntT(other.data));
	}
	constexpr inline CxFixedPt& operator /= (const CxFixedPt& other) const
	{
		*this = *this / other;
		return *this;
	}
	//--------
	constexpr inline double recip_dbl() const
	{
		const long double
			DATA_DBL = data;
		return 1.0d 
			/ (DATA_DBL / (MaxIntT(1) << MaxIntT(FRAC_WIDTH)));
	}
	//--------
};
//--------
// 16
using CxFixedI8p8 = CxFixedPt<int16_t, 8>;
using CxFixedU8p8 = CxFixedPt<uint16_t, 8>;
using CxFixedI12p4 = CxFixedPt<int16_t, 4>;
using CxFixedU12p4 = CxFixedPt<uint16_t, 4>;

// 32
using CxFixedI16p16 = CxFixedPt<int32_t, 16>;
using CxFixedU16p16 = CxFixedPt<uint32_t, 16>;
using CxFixedI24p8 = CxFixedPt<int32_t, 8>;
using CxFixedU24p8 = CxFixedPt<uint32_t, 8>;

// 64
using CxFixedI32p32 = CxFixedPt<int64_t, 32>;
using CxFixedU32p32 = CxFixedPt<uint64_t, 32>;
using CxFixedI48p16 = CxFixedPt<int64_t, 16>;
using CxFixedU48p16 = CxFixedPt<uint64_t, 16>;
//--------
} // namespace math
} // namespace liborangepower

#endif		// liborangepower_math_fixed_pt_class_hpp
