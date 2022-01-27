#ifndef liborangepower_containers_prev_curr_pair_classes_hpp
#define liborangepower_containers_prev_curr_pair_classes_hpp

#include "../misc/misc_types.hpp"
#include "../misc/misc_defines.hpp"

#include <utility>
#include <cstdint>

#include "../gen_class_innards_defines.hpp"


namespace liborangepower
{

namespace containers
{
//--------
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

	inline bool operator < (const PrevCurrPair& to_cmp) const
	{
		if (_curr < to_cmp._curr)
		{
			return true;
		}
		else if (_curr == to_cmp._curr)
		{
			return (_prev < to_cmp._prev);
		}
		else // if (_curr > to_cmp._curr)
		{
			return false;
		}
	}
	inline bool operator == (const PrevCurrPair& to_cmp) const
	{
		return ((_prev == to_cmp._prev) && (_curr == to_cmp._curr));
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
extern uint32_t _is_prev_curr_pair_func(const PrevCurrPair<Type>&);
template<typename Type>
extern uint8_t _is_prev_curr_pair_func(const Type&);

template<typename Type>
constexpr inline bool is_prev_curr_pair()
{
	return (sizeof(_is_prev_curr_pair_func(std::declval<Type>()))
		== sizeof(uint32_t));
}
//--------
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

template<typename Type>
extern uint32_t _is_move_only_prev_curr_pair_func
	(const MoveOnlyPrevCurrPair<Type>&);
template<typename Type>
extern uint8_t _is_move_only_prev_curr_pair_func(const Type&);

template<typename Type>
constexpr inline bool is_move_only_prev_curr_pair()
{
	return (sizeof(_is_move_only_prev_curr_pair_func(std::declval<Type>()))
		== sizeof(uint32_t));
}
//--------
} // namespace containers

} // namespace liborangepower


#endif		// liborangepower_containers_prev_curr_pair_classes_hpp
