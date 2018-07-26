#ifndef liborangepower_prev_curr_pair_class_hpp
#define liborangepower_prev_curr_pair_class_hpp

#include "misc_types.hpp"
#include "misc_defines.hpp"

#include <utility>


namespace liborangepower
{

namespace containers
{

template<typename type>
class Vec2;


// This is a small class for the purposes of holding the states of
// "previous" and "current" pairs.  It is primarily intended for use with
// SMALL types, such as vec2's, built-in types, and so on and so forth.
template<typename type>
class PrevCurrPair
{
public:		// variables
	type prev, curr;

public:		// functions

	inline void back_up()
	{
		prev = curr;
	}

	inline void back_up_and_update(const type& n_curr)
	{
		prev = std::move(curr);
		curr = n_curr;
	}
	inline void back_up_and_update(type&& n_curr)
	{
		prev = std::move(curr);
		curr = std::move(n_curr);
	}

	inline bool has_changed() const
	{
		return (prev != curr);
	}

	inline operator Vec2<type>() const
	{
		return Vec2<type>(prev, curr);
	}


};


} // namespace containers

} // namespace liborangepower


#endif		// liborangepower_prev_curr_pair_class_hpp
