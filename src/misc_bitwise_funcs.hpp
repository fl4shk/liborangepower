#ifndef liborangepower_misc_bitwise_funcs_hpp
#define liborangepower_misc_bitwise_funcs_hpp

#include "misc_types.hpp"
#include "misc_defines.hpp"


namespace liborangepower
{

namespace bitwise
{

template<typename Type>
inline void clear_bits(Type& to_clear, size_t mask)
{
	to_clear &= ~mask;
}

template<typename Type>
inline void set_bits(Type& to_set, size_t mask)
{
	to_set |= mask;
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
	return get_bits(to_get_from, 
		bprange_to_shifted_mask(bit_pos_range_hi, bit_pos_range_lo),
		bit_pos_range_lo);
}


template<typename Type>
inline void clear_and_set_bits(Type& to_change, size_t clear_mask,
	size_t set_mask)
{
	to_change &= ~clear_mask;
	to_change |= set_mask;
}

template<typename Type>
inline void clear_and_set_bits_with_range(Type& to_change, size_t val,
	size_t bit_pos_range_hi, size_t bit_pos_range_lo)
{
	clear_and_set_bits(to_change, 
		bprange_to_shifted_mask(bit_pos_range_hi, bit_pos_range_lo), 
		((val & bprange_to_mask(bit_pos_range_hi, bit_pos_range_lo))
		<< bit_pos_range_lo));
}

}

}


#endif		// liborangepower_misc_bitwise_funcs_hpp
