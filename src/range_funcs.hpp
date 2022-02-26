#ifndef liborangepower_range_funcs_hpp
#define liborangepower_range_funcs_hpp

//#include "vec2_classes.hpp"
#include "misc/misc_includes.hpp"


namespace liborangepower
{

namespace range
{

// in_range and vec2_in_range are PRIMARILY intended for use with a range
// of 0 (inclusive) to size (exclusive)
template<typename FirstArgT, typename SecondArgT,
	typename ThirdArgT>
inline bool in_range(FirstArgT range_start_inclusive, 
	SecondArgT range_end_exclusive, ThirdArgT to_check)
{
	return (to_check >= range_start_inclusive 
		&& to_check < range_end_exclusive);
}

template<typename FirstArgT, typename SecondArgT,
	typename ThirdArgT>
inline bool in_range_inclusive(FirstArgT range_start_inclusive, 
	SecondArgT range_end_inclusive, ThirdArgT to_check)
{
	return (to_check >= range_start_inclusive
		&& to_check <= range_end_inclusive);
}

//template<typename T>
//inline bool vec2_in_range(containers::Vec2<T> range_start_inclusive, 
//	containers::Vec2<T> range_end_exclusive, 
//	containers::Vec2<T> to_check)
//{
//	return (to_check.x >= range_start_inclusive.x 
//		&& to_check.x < range_end_exclusive.x
//		&& to_check.y >= range_start_inclusive.y 
//		&& to_check.y < range_end_exclusive.y);
//}


template<typename T>
inline T clamp_to_range(T range_start_inclusive, 
	T range_end_exclusive, T to_clamp)
{
	if (to_clamp < range_start_inclusive)
	{
		//to_clamp = range_start_inclusive;
		return range_start_inclusive;
	}
	else if (to_clamp >= range_end_exclusive)
	{
		//to_clamp = range_end_exclusive - T(1);
		return range_end_exclusive - (T)(1);
		//T ret = range_end_exclusive;
		//ret -= (T)1;

	}
	else
	{
		return to_clamp;
	}
}

} // namespace range

} // namespace liborangepower



#endif		// liborangepower_range_funcs_hpp
