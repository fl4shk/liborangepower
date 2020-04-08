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
template<typename FirstArgType, typename SecondArgType,
	typename ThirdArgType>
inline bool in_range(FirstArgType range_start_inclusive, 
	SecondArgType range_end_exclusive, ThirdArgType to_check)
{
	return (to_check >= range_start_inclusive 
		&& to_check < range_end_exclusive);
}

template<typename FirstArgType, typename SecondArgType,
	typename ThirdArgType>
inline bool in_range_inclusive(FirstArgType range_start_inclusive, 
	SecondArgType range_end_inclusive, ThirdArgType to_check)
{
	return (to_check >= range_start_inclusive
		&& to_check <= range_end_inclusive);
}

//template<typename Type>
//inline bool vec2_in_range(containers::Vec2<Type> range_start_inclusive, 
//	containers::Vec2<Type> range_end_exclusive, 
//	containers::Vec2<Type> to_check)
//{
//	return (to_check.x >= range_start_inclusive.x 
//		&& to_check.x < range_end_exclusive.x
//		&& to_check.y >= range_start_inclusive.y 
//		&& to_check.y < range_end_exclusive.y);
//}


template<typename Type>
inline Type clamp_to_range(Type range_start_inclusive, 
	Type range_end_exclusive, Type to_clamp)
{
	if (to_clamp < range_start_inclusive)
	{
		//to_clamp = range_start_inclusive;
		return range_start_inclusive;
	}
	else if (to_clamp >= range_end_exclusive)
	{
		//to_clamp = range_end_exclusive - Type(1);
		return range_end_exclusive - (Type)(1);
		//Type ret = range_end_exclusive;
		//ret -= (Type)1;

	}
	else
	{
		return to_clamp;
	}
}

} // namespace range

} // namespace liborangepower



#endif		// liborangepower_range_funcs_hpp
