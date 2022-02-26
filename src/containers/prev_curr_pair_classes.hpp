#ifndef liborangepower_containers_prev_curr_pair_classes_hpp
#define liborangepower_containers_prev_curr_pair_classes_hpp

#include "../misc/misc_types.hpp"
#include "../misc/misc_defines.hpp"
#include "../concepts/is_specialization_concepts.hpp"

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
template<typename T>
class PrevCurrPair final
{
public:		// types
	using ElemT = T;
private:		// variables
	T _prev, _curr;

public:		// functions
	inline PrevCurrPair() = default;
	inline PrevCurrPair(const T& s_prev, const T& s_curr)
		: _prev(s_prev), _curr(s_curr)
	{
	}
	inline PrevCurrPair(T&& s_prev, T&& s_curr)
		: _prev(std::move(s_prev)), _curr(std::move(s_curr))
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(PrevCurrPair);
	~PrevCurrPair() = default;

	inline void back_up()
	{
		_prev = _curr;
	}

	inline void back_up_and_update(const T& n_curr)
	{
		_prev = std::move(_curr);
		_curr = n_curr;
	}
	inline void back_up_and_update(T&& n_curr)
	{
		_prev = std::move(_curr);
		_curr = std::move(n_curr);
	}

	inline bool has_changed() const
	{
		return (_prev != _curr);
	}

	//inline bool operator < (const PrevCurrPair& to_cmp) const
	//{
	//	if (_curr < to_cmp._curr)
	//	{
	//		return true;
	//	}
	//	else if (_curr == to_cmp._curr)
	//	{
	//		return (_prev < to_cmp._prev);
	//	}
	//	else // if (_curr > to_cmp._curr)
	//	{
	//		return false;
	//	}
	//}
	//inline bool operator == (const PrevCurrPair& to_cmp) const
	//{
	//	return ((_prev == to_cmp._prev) && (_curr == to_cmp._curr));
	//}
	inline auto operator <=> (const PrevCurrPair& to_cmp) const
		= default;

	inline T& operator () ()
	{
		return _curr;
	}
	inline const T& operator () () const
	{
		return _curr;
	}

	GEN_GETTER_BY_CON_REF(prev)
	GEN_GETTER_BY_CON_REF(curr)
};
//template<typename T> 
//class CxPrevCurrPair final
//{
//public:		// types
//	using ElemT = T;
//private:		// variables
//	T _prev, _curr;
//public:		// functions
//	constexpr inline CxPrevCurrPair() = default;
//	constexpr inline CxPrevCurrPair(const T& s_prev, const T& s_curr)
//		: _prev(s_prev), _curr(s_curr)
//	{
//	}
//	constexpr inline CxPrevCurrPair(T&& s_prev, T&& s_curr)
//		: _prev(std::move(s_prev)), _curr(std::move(s_curr))
//	{
//	}
//	GEN_CX_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(CxPrevCurrPair);
//	constexpr ~CxPrevCurrPair() = default;
//
//	constexpr inline void back_up()
//	{
//		_prev = _curr;
//	}
//
//	constexpr inline void back_up_and_update(const T& n_curr)
//	{
//		_prev = std::move(_curr);
//		_curr = n_curr;
//	}
//	constexpr inline void back_up_and_update(T&& n_curr)
//	{
//		_prev = std::move(_curr);
//		_curr = std::move(n_curr);
//	}
//
//	constexpr inline bool has_changed() const
//	{
//		return (_prev != _curr);
//	}
//
//	constexpr inline auto operator <=> (const CxPrevCurrPair& to_cmp) const
//		= default;
//
//	constexpr inline T& operator () ()
//	{
//		return _curr;
//	}
//	constexpr inline const T& operator () () const
//	{
//		return _curr;
//	}
//
//	GEN_GETTER_BY_CON_REF(prev)
//	GEN_GETTER_BY_CON_REF(curr)
//};
//--------
template<typename T>
class MoveOnlyPrevCurrPair final
{
public:		// types
	using ElemT = T;
private:		// variables
	T _prev, _curr;
public:		// functions
	inline MoveOnlyPrevCurrPair() = default;
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(MoveOnlyPrevCurrPair);
	~MoveOnlyPrevCurrPair() = default;

	inline void back_up()
	{
		_prev = std::move(_curr);
		_curr = T();
	}

	inline void back_up_and_update(T&& n_curr)
	{
		_prev = std::move(_curr);
		_curr = std::move(n_curr);
	}

	inline bool has_changed() const
	{
		return (_prev != _curr);
	}

	inline auto operator <=> (const MoveOnlyPrevCurrPair& to_cmp) const
		= default;

	inline T& operator () ()
	{
		return _curr;
	}
	inline const T& operator () () const
	{
		return _curr;
	}

	GEN_GETTER_BY_CON_REF(prev);
	GEN_GETTER_BY_CON_REF(curr);
};

//template<typename T>
//class CxMoveOnlyPrevCurrPair final
//{
//public:		// types
//	using ElemT = T;
//private:		// variables
//	T _prev, _curr;
//public:		// functions
//	constexpr inline CxMoveOnlyPrevCurrPair() = default;
//	GEN_CX_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(CxMoveOnlyPrevCurrPair);
//	constexpr ~CxMoveOnlyPrevCurrPair() = default;
//
//	constexpr inline void back_up()
//	{
//		_prev = std::move(_curr);
//		_curr = T();
//	}
//
//	constexpr inline void back_up_and_update(T&& n_curr)
//	{
//		_prev = std::move(_curr);
//		_curr = std::move(n_curr);
//	}
//
//	constexpr inline bool has_changed() const
//	{
//		return (_prev != _curr);
//	}
//
//	constexpr inline auto operator <=>
//		(const CxMoveOnlyPrevCurrPair& to_cmp) const = default;
//
//	constexpr inline T& operator () ()
//	{
//		return _curr;
//	}
//	constexpr inline const T& operator () () const
//	{
//		return _curr;
//	}
//
//	GEN_GETTER_BY_CON_REF(prev);
//	GEN_GETTER_BY_CON_REF(curr);
//};
//--------
template<typename T>
constexpr inline bool is_prev_curr_pair()
{
	return concepts::is_specialization<T, PrevCurrPair>();
}

template<typename T>
constexpr inline bool is_move_only_prev_curr_pair()
{
	return concepts::is_specialization<T, MoveOnlyPrevCurrPair>();
}
//--------
} // namespace containers

} // namespace liborangepower


#endif		// liborangepower_containers_prev_curr_pair_classes_hpp
