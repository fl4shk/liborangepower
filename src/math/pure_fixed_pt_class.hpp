#ifndef liborangepower_math_pure_fixed_pt_class_hpp
#define liborangepower_math_pure_fixed_pt_class_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_defines.hpp"
#include "../misc/misc_types.hpp"
#include "../misc/misc_bitwise_funcs.hpp"
#include "misc_funcs.hpp"
#include "misc_types.hpp"

namespace liborangepower {

using bitwise::width_of_type;
using integer_types::u8;
using integer_types::i8;
using integer_types::u16;
using integer_types::i16;
using integer_types::u32;
using integer_types::i32;
using integer_types::u64;
using integer_types::i64;

namespace math {
//--------
// A class implementing fixed-point arithmetic with `constexpr` functions.
// Of course, this can be used in runtime code.
template<std::integral IntTarg, size_t FRAC_WIDTH_TARG>
class PureFixedPt {
public:		// types
	using IntT = IntTarg;

	class CtorArgs final {
	public:		// variables
		IntT data;
	};
public:		// constants
	static constexpr size_t
		INT_T_WIDTH = width_of_type<IntT>();
	static constexpr size_t
		FRAC_WIDTH = FRAC_WIDTH_TARG,
		WHOLE_WIDTH = INT_T_WIDTH - FRAC_WIDTH;

	//template<size_t OTHER_FRAC_WIDTH>
	//static constexpr size_t SHIFT_AMOUNT
	//	= FRAC_WIDTH > OTHER_FRAC_WIDTH
	//	? FRAC_WIDTH - OTHER_FRAC_WIDTH
	//	: OTHER_FRAC_WIDTH - FRAC_WIDTH;

	static_assert(FRAC_WIDTH >= 1,
		"`FRAC_WIDTH` < 1");
	static_assert(FRAC_WIDTH < INT_T_WIDTH,
		"`FRAC_WIDTH >= INT_T_WIDTH`");
public:		// types
	using MaxIntT = std::conditional_t<
		std::unsigned_integral<IntT>, uintmax_t, intmax_t
	>;
	//using RecipPureFixedPt = PureFixedPt<MaxIntT, FRAC_WIDTH * 2>::CtorArgs;
	//using RecipPureFixedPt = PureFixedPt<MaxIntT, FRAC_WIDTH * 2>;
public:		// variables
	IntT data = 0;
public:		// functions
	//--------
	constexpr inline PureFixedPt() {
	}
	constexpr inline PureFixedPt(const CtorArgs& ctor_args)
		: data(ctor_args.data) {
	}
	//--------
	explicit constexpr inline PureFixedPt(std::integral auto to_conv)
		: data(to_conv << FRAC_WIDTH) {
	}
	///*explicit*/ constexpr inline PureFixedPt(
	//	std::floating_point auto to_conv
	//)
	//	: data((long double)(to_conv) * (MaxIntT(1) << FRAC_WIDTH)) {
	//}

	template<std::integral OtherIntT, size_t OTHER_FRAC_WIDTH>
	explicit constexpr inline PureFixedPt(
		const PureFixedPt<OtherIntT, OTHER_FRAC_WIDTH>& to_conv
	) {
		constexpr size_t
			OTHER_INT_T_WIDTH = width_of_type<OtherIntT>();
			//OTHER_WHOLE_BITS = OTHER_INT_T_WIDTH - OTHER_FRAC_WIDTH;
		constexpr int
			MY_SHIFT_AMOUNT = OTHER_FRAC_WIDTH - FRAC_WIDTH;

		if constexpr (MY_SHIFT_AMOUNT < 0) {
			// Do the conversion with the larger type 
			if constexpr (OTHER_INT_T_WIDTH > INT_T_WIDTH) {
				data = to_conv.data << (-MY_SHIFT_AMOUNT);
			} else { // if constexpr (OTHER_INT_T_WIDTH <= INT_T_WIDTH)
				data = to_conv.data;
				data <<= -MY_SHIFT_AMOUNT;
			}
		} else if constexpr (MY_SHIFT_AMOUNT > 0) {
			data = to_conv.data >> MY_SHIFT_AMOUNT;
		} else {
			data = to_conv.data;
		}
	}
	//--------
	constexpr inline PureFixedPt(const PureFixedPt&) = default;
	constexpr inline PureFixedPt& operator = (
	    const PureFixedPt&
	) = default;

	//constexpr inline PureFixedPt& operator = (float to_assign) {
	//	*this = PureFixedPt(to_assign);
	//	return *this;
	//}
	//constexpr inline PureFixedPt& operator = (double to_assign) {
	//	*this = PureFixedPt(to_assign);
	//	return *this;
	//}
	//constexpr inline PureFixedPt& operator = (long double to_assign) {
	//	*this = PureFixedPt(to_assign);
	//	return *this;
	//}

	constexpr inline ~PureFixedPt() = default;
	//--------
	constexpr inline auto operator <=> (
	    const PureFixedPt&
	) const = default;
	//--------
	template<std::integral CastIntT>
	explicit constexpr inline operator CastIntT () const {
		return MaxIntT(data) >> FRAC_WIDTH;
		//return bitwise::get_bits_with_range(data, FRAC_WIDTH - 1, 0);
	}
	//template<std::floating_point CastFloatT>
	//explicit constexpr inline operator float () const {
	//	return float(
	//		(double)(data)
	//		/ (double)(MaxIntT(1) << FRAC_WIDTH)
	//	);
	//}
	//explicit constexpr inline operator double () const {
	//	return (double)(
	//		//whole_part<MaxIntT>()
	//		data
	//	)
	//		/ (double)(MaxIntT(1) << FRAC_WIDTH);
	//}
	//explicit constexpr inline operator long double () const {
	//	return (long double)(
	//		//whole_part<MaxIntT>()
	//		data
	//	)
	//		/ (long double)(MaxIntT(1) << FRAC_WIDTH);
	//}
	//--------
	template<std::integral CastIntT=IntT>
	constexpr inline CastIntT whole_part() const {
		return CastIntT(*this);
	}
	constexpr inline IntT frac_part() const {
		//return data & ((MaxIntT(1) << FRAC_WIDTH) - MaxIntT(1));
		return bitwise::get_bits_with_range(
			data,
			FRAC_WIDTH - MaxIntT(1),
			0
		);
	}
	//--------
	constexpr inline PureFixedPt operator + (
	    const PureFixedPt& other
	) const {
		//return PureFixedPt({.data=data + other.data});
		PureFixedPt ret;
		ret.data = data + other.data;
		return ret;
	}
	constexpr inline PureFixedPt& operator += (
		const PureFixedPt& other
	) {
		*this = *this + other;
		return *this;
	}
	//constexpr inline PureFixedPt operator + (double other) const {
	//	return PureFixedPt(double(*this) + other);
	//}
	//constexpr inline PureFixedPt& operator += (double other) const {
	//	*this = *this + other;
	//	return other;
	//}
	constexpr inline PureFixedPt operator + () const {
		//return PureFixedPt({.data=-data});
		PureFixedPt ret;
		ret.data = +data;
		return ret;
	}

	constexpr inline PureFixedPt operator - (
	    const PureFixedPt& other
	) const {
		//return PureFixedPt({.data=data - other.data});
		PureFixedPt ret;
		ret.data = data - other.data;
		return ret;
	}
	constexpr inline PureFixedPt& operator -= (
		const PureFixedPt& other
	) {
		*this = *this - other;
		return *this;
	}
	//constexpr inline PureFixedPt operator - (double other) const {
	//	return PureFixedPt(double(*this) - other);
	//}
	//constexpr inline PureFixedPt& operator -= (double other) const {
	//	*this = *this - other;
	//	return other;
	//}
	constexpr inline PureFixedPt operator - () const {
		//return PureFixedPt({.data=-data});
		PureFixedPt ret;
		ret.data = -data;
		return ret;
	}

	constexpr inline PureFixedPt operator * (
	    const PureFixedPt& other
	) const {
		//return PureFixedPt(CtorArgs{.data=(
		//	(MaxIntT(data) * MaxIntT(other.data)) >> FRAC_WIDTH
		//)});
		PureFixedPt ret;
		ret.data = (MaxIntT(data) * MaxIntT(other.data)) >> FRAC_WIDTH;
		return ret;
	}
	constexpr inline PureFixedPt& operator *= (
		const PureFixedPt& other
	) {
		*this = *this * other;
		return *this;
	}
	//constexpr inline PureFixedPt operator * (double other) const {
	//	return PureFixedPt(double(*this) * other);
	//}
	//constexpr inline PureFixedPt& operator *= (double other) const {
	//	*this = *this * other;
	//	return other;
	//}

	constexpr inline PureFixedPt operator / (
	    const PureFixedPt& other
	) const {
		//return PureFixedPt({.data=(
		//	(MaxIntT(data) << FRAC_WIDTH) / MaxIntT(other.data)
		//)});
		PureFixedPt ret;
		ret.data = (MaxIntT(data) << FRAC_WIDTH) / MaxIntT(other.data);
		return ret;
	}
	constexpr inline PureFixedPt& operator /= (
		const PureFixedPt& other
	) {
		*this = *this / other;
		return *this;
	}
	//constexpr inline PureFixedPt operator / (double other) const {
	//	return PureFixedPt(double(*this) / other);
	//}
	//constexpr inline PureFixedPt& operator /= (double other) const {
	//	*this = *this / other;
	//	return other;
	//}
	//--------
	//constexpr inline long double recip_ldbl() const {
	//	const long double
	//		DATA_DBL = data;
	//	return 1.0l
	//		/ (DATA_DBL / (MaxIntT(1) << FRAC_WIDTH));
	//}
	//constexpr inline long double sqrt_ldbl() const {
	//	return std::sqrt((long double)(*this));
	//}
	//constexpr inline PureFixedPt sqrt() const {
	//	return PureFixedPt(std::sqrt(double(*this)));
	//}
	//constexpr inline PureFixedPt div_2() const {
	//	//return PureFixedPt({.data=(data >> IntT(1))});
	//	PureFixedPt ret;
	//	ret.data = data >> IntT(1);
	//	return ret;
	//}
	//constexpr inline PureFixedPt sqrt() const {
	//}
	//--------
};
//--------
// 16
using PureFixedI8p8 = PureFixedPt<i16, 8>;
using PureFixedU8p8 = PureFixedPt<u16, 8>;
using PureFixedI12p4 = PureFixedPt<i16, 4>;
using PureFixedU12p4 = PureFixedPt<u16, 4>;

// 32
using PureFixedI16p16 = PureFixedPt<i32, 16>;
using PureFixedU16p16 = PureFixedPt<u32, 16>;
using PureFixedI24p8 = PureFixedPt<i32, 8>;
using PureFixedU24p8 = PureFixedPt<u32, 8>;
using PureFixedI20p12 = PureFixedPt<i32, 12>;
using PureFixedU20p12 = PureFixedPt<u32, 12>;

// 64
using PureFixedI32p32 = PureFixedPt<i64, 32>;
using PureFixedU32p32 = PureFixedPt<u64, 32>;
using PureFixedI48p16 = PureFixedPt<i64, 16>;
using PureFixedU48p16 = PureFixedPt<u64, 16>;
//--------
} // namespace math
} // namespace liborangepower

#endif      // liborangepower_math_pure_fixed_pt_class_hpp
