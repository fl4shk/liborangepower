#ifndef liborangepower_misc_misc_bitwise_funcs_hpp
#define liborangepower_misc_misc_bitwise_funcs_hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "misc_defines.hpp"

#include <limits.h>


namespace liborangepower {
namespace bitwise {

template<typename T>
constexpr inline size_t width_of_type() {
	static_assert(
		CHAR_BIT == 8, "This software requires CHAR_BIT == 8"
	);
	return (sizeof(T) * 8);
}

// This uses the ability of the compiler to deduce what "T" is from the
// type of "to_check".
template<typename T>
constexpr inline size_t width_of_type(const T& to_check) {
	return width_of_type<T>();
}

template<typename T>
constexpr inline bool bprange_is_all(
	size_t bit_pos_range_hi, size_t bit_pos_range_lo
) {
	return (
		(bit_pos_range_hi == WIDTH2MP(width_of_type<T>()))
		&& (bit_pos_range_lo == 0)
	);
}

// This also uses the ability of the compiler to deduce what "T" is from
// the type of "to_check".
template<typename T>
constexpr inline bool bprange_is_all(
	const T& to_check, size_t bit_pos_range_hi, size_t bit_pos_range_lo
) {
	return bprange_is_all<T>(bit_pos_range_hi, bit_pos_range_lo);
}


template<typename T>
constexpr inline void clear_bits(T& to_clear, const auto& mask)
{
	to_clear &= ~mask;
}

template<typename T>
constexpr inline void clear_bits_with_range(
	T& to_clear, size_t bit_pos_range_hi, size_t bit_pos_range_lo
) {
	clear_bits(to_clear, (BPRANGE2MASK(bit_pos_range_hi,
		bit_pos_range_lo) << bit_pos_range_lo));
}
template<typename T>
constexpr inline void clear_bits_r(
	T& to_clear, size_t bit_pos_range_hi, size_t bit_pos_range_lo
) {
	clear_bits_with_range(to_clear, bit_pos_range_hi, bit_pos_range_lo);
}

template<typename T>
constexpr inline void set_bits(T& to_set, const auto& mask) {
	to_set |= mask;
}

template<typename T>
constexpr inline void set_bits_with_range(
	T& to_set, const auto& val,
	size_t bit_pos_range_hi, size_t bit_pos_range_lo
) {
	set_bits(to_set, ((val & BPRANGE2MASK(bit_pos_range_hi,
		bit_pos_range_lo)) << bit_pos_range_lo));
}
template<typename T>
constexpr inline void set_bits_r(
	T& to_set, const auto& val,
	size_t bit_pos_range_hi, size_t bit_pos_range_lo
) {
	set_bits_with_range(to_set, val, bit_pos_range_hi, bit_pos_range_lo);
}

template<typename T>
constexpr inline T get_bits(
	const T& to_get_from, const auto& mask, size_t shift=0
)
{
	return ((to_get_from & mask) >> shift);
}

template<typename T>
constexpr inline T get_bits_with_range(
	const T& to_get_from, size_t bit_pos_range_hi, size_t bit_pos_range_lo
) {
	// "BPRANGE2SHIFTED_MASK" didn't work for this case.
	if (bprange_is_all<T>(bit_pos_range_hi, bit_pos_range_lo)) {
		return to_get_from;
	} else {
		return get_bits(to_get_from, 
			BPRANGE2SHIFTED_MASK(bit_pos_range_hi, bit_pos_range_lo),
			bit_pos_range_lo);
	}
}
template<typename T>
constexpr inline T get_bits_r(
	const T& to_get_from, size_t bit_pos_range_hi, size_t bit_pos_range_lo
) {
	return get_bits_with_range(to_get_from, bit_pos_range_hi, bit_pos_range_lo);
}


template<typename T>
constexpr inline void clear_and_set_bits(
	T& to_change, const auto& clear_mask, const auto& set_mask
) {
	// I don't remember the reason why this doesn't just call
	// "clear_bits()" followed by "get_bits()", but I do recall it causing
	// *some* kind of problem.  Oh well.  It doesn't really do any harm to
	// keep things this way, I guess?
	to_change &= ~clear_mask;
	to_change |= set_mask;
}

template<typename T>
constexpr inline void clear_and_set_bits(
	T& to_change, const auto& val,
	size_t bit_pos_range_hi, size_t bit_pos_range_lo
) {
	// "BPRANGE2SHIFTED_MASK" didn't work for this case.
	if (bprange_is_all<T>(bit_pos_range_hi, bit_pos_range_lo)) {
		to_change = val;
	} else {
		clear_and_set_bits(to_change, 
			BPRANGE2SHIFTED_MASK(bit_pos_range_hi, bit_pos_range_lo), 
			((val & BPRANGE2MASK(bit_pos_range_hi, bit_pos_range_lo))
			<< bit_pos_range_lo));
	}
}
template<typename T>
constexpr inline void clear_and_set_bits_with_range(
	T& to_change,
	const auto& val, size_t bit_pos_range_hi, size_t bit_pos_range_lo
) {
	clear_and_set_bits(to_change, val, bit_pos_range_hi, bit_pos_range_lo);
}
template<typename T>
constexpr inline void clear_and_set_bits_r(
	T& to_change,
	const auto& val, size_t bit_pos_hi, size_t bit_pos_lo
) {
	clear_and_set_bits_with_range(to_change, val, bit_pos_hi, bit_pos_lo);
}


using liborangepower::integer_types::u8;
using liborangepower::integer_types::i8;

using liborangepower::integer_types::u16;
using liborangepower::integer_types::i16;

using liborangepower::integer_types::u32;
using liborangepower::integer_types::i32;

using liborangepower::integer_types::u64;
using liborangepower::integer_types::i64;


// Can this be made "constexpr"?
template<std::integral T>
constexpr size_t count_leading_zeros(const T& x) {
	//static_assert(std::is_integral<T>());
	static_assert(CHAR_BIT == 8,
		"This software requires CHAR_BIT == 8");

	size_t ret = 0;

	//u64 temp32 = 0, temp16 = 0, temp8 = 0, temp4 = 0, temp2 = 0;
	u64 s = x;

	if (s == 0) {
		ret = sizeof(T) * 8;
	} else {
		static_assert(sizeof(T) <= 8);
		switch (sizeof(T)) {
			case 8:
				s = get_bits_with_range(s, 63, 32)
					? get_bits_with_range(s, 63, 32)
					: ((static_cast<u64>(1) << static_cast<u64>(32)) 
					| get_bits_with_range(s, 31, 0));
				set_bits_with_range(ret, get_bits_with_range(s, 32, 32), 5,
					5);

			case 4:
				s = get_bits_with_range(s, 31, 16)
					? get_bits_with_range(s, 31, 16)
					: ((1 << 16) | get_bits_with_range(s, 15, 0));
				set_bits_with_range(ret, get_bits_with_range(s, 16, 16), 4, 
					4);

			case 2:
				s = get_bits_with_range(s, 15, 8)
					? get_bits_with_range(s, 15, 8)
					: ((1 << 8) | get_bits_with_range(s, 7, 0));
				set_bits_with_range(ret, get_bits_with_range(s, 8, 8), 3,
					3);

			case 1:
				s = get_bits_with_range(s, 7, 4)
					? get_bits_with_range(s, 7, 4)
					: ((1 << 4) | get_bits_with_range(s, 3, 0));
				set_bits_with_range(ret, get_bits_with_range(s, 4, 4), 2,
					2);

				s = get_bits_with_range(s, 3, 2)
					? get_bits_with_range(s, 3, 2)
					: ((1 << 2) | get_bits_with_range(s, 1, 0));
				set_bits_with_range(ret, get_bits_with_range(s, 2, 2), 1,
					1);

				set_bits_with_range(ret, !get_bits_with_range(s, 1, 1), 0,
					0);
				break;

			//// 128-bit, eh?  I don't know what else it'd be....
			//default:
			//	for (i64 i=((1 << sizeof(T)) - 1); i>=0; --i)
			//	{
			//		if (!get_bits_with_range(s, i, i))
			//		{
			//			++ret;
			//		}
			//		else
			//		{
			//			break;
			//		}
			//	}
			//	break;
		}
	}

	return ret;
}
template<std::integral T>
constexpr size_t basic_ilog2(T x)
{
	//static_assert(std::is_integral<T>());
	static_assert(CHAR_BIT == 8);

	return (sizeof(T) * 8 - 1 - count_leading_zeros(x));
}
//// sample code, mainly used as a reference for how make a low-area barrel
//// shifter in HDL/FPGA code
//template<std::integral T>
//constexpr T barrel_shift(const T& x, size_t amount, bool is_rshift) {
//
//	static_assert(CHAR_BIT == 8);
//
//	auto get_modded_i = [](size_t i) -> size_t {
//		return (1 << (i - 1));
//	};
//
//	static constexpr size_t MY_WIDTH = sizeof(T) * 8ull;
//	static constexpr size_t MY_MSB_POS = MY_WIDTH - 1ull;
//
//	static constexpr size_t TEMP_ARR_SIZE = (
//		sizeof(T) == 8
//		? 6ull
//		: (
//			sizeof(T) == 4
//			? 5ull
//			: (
//				sizeof(T) == 2
//				? 4ull
//				: (
//					3ull
//					//sizeof(T) == 1
//					//? 3
//					//: 
//				)
//			)
//		)
//	);
//	auto set_temp_lsl = [&](size_t i) -> void {
//		
//	};
//
//	//if constexpr (std::is_signed<T>) {
//	//} else {
//	//}
//
//	//switch (sizeof(T)) {
//	//	case 8: 
//	//	case 4: 
//	//	case 2: 
//	//	case 1: 
//	//	//default:
//	//}
//}

//template<std::integral T>
//constexpr size_t basic_count_leading_zeros(T x)
//{
//	//static_assert(std::is_integral<T>());
//	static_assert(CHAR_BIT == 8);
//
//	size_t ret = 0;
//
//	//u64 temp32 = 0, temp16 = 0, temp8 = 0, temp4 = 0, temp2 = 0;
//	u64 s = x;
//
//	if (s == 0)
//	{
//		ret = sizeof(T) * 8;
//	}
//	else
//	{
//		for (i64 i=((1 << sizeof(T)) - 1); i>=0; --i)
//		{
//			if (!get_bits_with_range(s, i, i))
//			{
//				++ret;
//			}
//			else
//			{
//				break;
//			}
//		}
//	}
//	return ret;
//}
//

} // namespace bitwise
} // namespace liborangepower


#endif		// liborangepower_misc_misc_bitwise_funcs_hpp
