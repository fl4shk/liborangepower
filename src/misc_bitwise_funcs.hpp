#ifndef liborangepower_misc_bitwise_funcs_hpp
#define liborangepower_misc_bitwise_funcs_hpp

#include "misc_types.hpp"
#include "misc_defines.hpp"


namespace liborangepower
{

namespace bitwise
{

template<typename Type>
inline constexpr size_t width_of_type()
{
	return (sizeof(Type) * 8);
}

template<typename Type>
inline constexpr size_t width_of_type(const Type& to_check)
{
	return width_of_type<Type>();
}

template<typename Type>
inline constexpr bool bprange_is_all(size_t bit_pos_range_hi,
	size_t bit_pos_range_lo)
{
	return ((bit_pos_range_hi 
		== width_to_msb_pos(width_of_type<Type>()))
		&& (bit_pos_range_lo == 0));
}

template<typename Type>
inline constexpr bool bprange_is_all(const Type& to_check, 
	size_t bit_pos_range_hi, size_t bit_pos_range_lo)
{
	return bprange_is_all<Type>(bit_pos_range_hi, bit_pos_range_lo);
}


template<typename Type>
inline void clear_bits(Type& to_clear, size_t mask)
{
	to_clear &= ~mask;
}

template<typename Type>
inline void clear_bits_with_range(Type& to_clear, size_t bit_pos_range_hi,
	size_t bit_pos_range_lo)
{
	clear_bits(to_clear, (bprange_to_mask(bit_pos_range_hi,
		bit_pos_range_lo) << bit_pos_range_lo));
}

template<typename Type>
inline void set_bits(Type& to_set, size_t mask)
{
	to_set |= mask;
}

template<typename Type>
inline void set_bits_with_range(Type& to_set, size_t val,
	size_t bit_pos_range_hi, size_t bit_pos_range_lo)
{
	set_bits(to_set, ((val & bprange_to_mask(bit_pos_range_hi,
		bit_pos_range_lo)) << bit_pos_range_lo));
}

template<typename Type>
inline constexpr Type get_bits(Type to_get_from, size_t mask, 
	size_t shift=0)
{
	return ((to_get_from & mask) >> shift);
}

template<typename Type>
inline constexpr Type get_bits_with_range(Type to_get_from, 
	size_t bit_pos_range_hi, size_t bit_pos_range_lo)
{
	if (bprange_is_all<Type>(bit_pos_range_hi, bit_pos_range_lo))
	{
		return to_get_from;
	}
	else
	{
		return get_bits(to_get_from, 
			bprange_to_shifted_mask(bit_pos_range_hi, bit_pos_range_lo),
			bit_pos_range_lo);
	}
}


template<typename Type>
inline void clear_and_set_bits(Type& to_change, size_t clear_mask,
	size_t set_mask)
{
	to_change &= ~clear_mask;
	to_change |= set_mask;
}

template<typename Type>
inline void clear_and_set_bits(Type& to_change, size_t val,
	size_t bit_pos_range_hi, size_t bit_pos_range_lo)
{
	if (bprange_is_all<Type>(bit_pos_range_hi, bit_pos_range_lo))
	{
		to_change = val;
	}
	else
	{
		clear_and_set_bits(to_change, 
			bprange_to_shifted_mask(bit_pos_range_hi, bit_pos_range_lo), 
			((val & bprange_to_mask(bit_pos_range_hi, bit_pos_range_lo))
			<< bit_pos_range_lo));
	}
}
template<typename Type>
inline void clear_and_set_bits_with_range(Type& to_change, size_t val,
	size_t bit_pos_range_hi, size_t bit_pos_range_lo)
{
	clear_and_set_bits(to_change, val, bit_pos_range_hi, bit_pos_range_lo);
}


using liborangepower::integer_types::u8;
using liborangepower::integer_types::s8;

using liborangepower::integer_types::u16;
using liborangepower::integer_types::s16;

using liborangepower::integer_types::u32;
using liborangepower::integer_types::s32;

using liborangepower::integer_types::u64;
using liborangepower::integer_types::s64;


template<typename Type>
size_t count_leading_zeros(Type x)
{
	size_t ret = 0;

	//u64 temp32 = 0, temp16 = 0, temp8 = 0, temp4 = 0, temp2 = 0;
	u64 s = x;

	if (s == 0)
	{
		ret = sizeof(Type) * 8;
	}

	else
	{
		switch (sizeof(Type))
		{
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

			//default:
			//	for (s64 i=((1 << sizeof(Type)) - 1); i>=0; --i)
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


} // namespace bitwise

} // namespace liborangepower


#endif		// liborangepower_misc_bitwise_funcs_hpp
