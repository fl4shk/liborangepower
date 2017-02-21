#ifndef liborangepower_range_funcs_hpp
#define liborangepower_range_funcs_hpp

#include "vec2_classes.hpp"


// in_range and vec2_in_range are PRIMARILY intended for use with a range
// of 0 (inclusive) to size (exclusive)
template< typename type >
inline bool in_range( type range_start_inclusive, type range_end_exclusive, 
	type to_check )
{
	return ( to_check >= range_start_inclusive 
		&& to_check < range_end_exclusive );
}

template< typename type >
inline bool in_range_inclusive( type range_start_inclusive, 
	type range_end_inclusive, type to_check )
{
	return ( to_check >= range_start_inclusive
		&& to_check <= range_end_inclusive );
}

template< typename type >
inline bool vec2_in_range( vec2<type> range_start_inclusive, 
	vec2<type> range_end_exclusive, vec2<type> to_check )
{
	return ( to_check.x >= range_start_inclusive.x 
		&& to_check.x < range_end_exclusive.x
		&& to_check.y >= range_start_inclusive.y 
		&& to_check.y < range_end_exclusive.y );
}


template< typename type >
inline type clamp_to_range( type range_start_inclusive, 
	type range_end_exclusive, type to_clamp )
{
	if ( to_clamp < range_start_inclusive )
	{
		//to_clamp = range_start_inclusive;
		return range_start_inclusive;
	}
	else if ( to_clamp >= range_end_exclusive )
	{
		//to_clamp = range_end_exclusive - type(1);
		return range_end_exclusive - (type)(1);
		//type ret = range_end_exclusive;
		//ret -= (type)1;
		
	}
	else
	{
		return to_clamp;
	}
}




#endif		// liborangepower_range_funcs_hppc
