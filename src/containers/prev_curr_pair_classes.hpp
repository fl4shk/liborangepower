#ifndef liborangepower_containers_prev_curr_pair_classes_hpp
#define liborangepower_containers_prev_curr_pair_classes_hpp

#include "../misc/misc_types.hpp"
#include "../misc/misc_defines.hpp"

#include <utility>

#include "../gen_class_innards_defines.hpp"


namespace liborangepower
{

namespace containers
{

// This is a small class for the purposes of holding the states of
// "previous" and "current" pairs.  It is primarily intended for use with
// SMALL types, such as vec2's, built-in types, and so on and so forth.
template<typename Type>
class PrevCurrPair
{
protected:		// variables
	Type _prev, _curr;

public:		// functions
	inline PrevCurrPair() = default;

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(PrevCurrPair);
	virtual ~PrevCurrPair() = default;


	inline void back_up()
	{
		_prev = _curr;
	}

	inline void back_up_and_update(const Type& n_curr)
	{
		_prev = std::move(_curr);
		_curr = n_curr;
	}
	inline void back_up_and_update(Type&& n_curr)
	{
		_prev = std::move(_curr);
		_curr = std::move(n_curr);
	}

	inline bool has_changed() const
	{
		return (_prev != _curr);
	}

	inline Type& operator () ()
	{
		return _curr;
	}
	inline const Type& operator () () const
	{
		return _curr;
	}

	GEN_GETTER_BY_CON_REF(prev)
	GEN_GETTER_BY_CON_REF(curr)
};


template<typename Type>
class MoveOnlyPrevCurrPair
{
protected:		// variables
	Type _prev, _curr;
	
public:		// functions
	inline MoveOnlyPrevCurrPair() = default;
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(MoveOnlyPrevCurrPair);
	virtual ~MoveOnlyPrevCurrPair() = default;

	inline void back_up()
	{
		_prev = std::move(_curr);
		_curr = Type();
	}

	inline void back_up_and_update(Type&& n_curr)
	{
		_prev = std::move(_curr);
		_curr = std::move(n_curr);
	}

	inline bool has_changed() const
	{
		return (_prev != _curr);
	}

	inline Type& operator () ()
	{
		return _curr;
	}
	inline const Type& operator () () const
	{
		return _curr;
	}

	GEN_GETTER_BY_CON_REF(prev)
	GEN_GETTER_BY_CON_REF(curr)
};


} // namespace containers

} // namespace liborangepower


#endif		// liborangepower_containers_prev_curr_pair_classes_hpp
