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
template<typename Type>
class PrevCurrPair final
{
private:		// variables
	Type _prev, _curr;

public:		// functions
	inline PrevCurrPair() = default;
	inline PrevCurrPair(const Type& s_prev, const Type& s_curr)
		: _prev(s_prev), _curr(s_curr)
	{
	}
	inline PrevCurrPair(Type&& s_prev, Type&& s_curr)
		: _prev(std::move(s_prev)), _curr(std::move(s_curr))
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(PrevCurrPair);
	~PrevCurrPair() = default;

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
//template<typename Type> 
//class CxPrevCurrPair final
//{
//private:		// variables
//	Type _prev, _curr;
//public:		// functions
//	constexpr inline CxPrevCurrPair() = default;
//	constexpr inline CxPrevCurrPair(const Type& s_prev, const Type& s_curr)
//		: _prev(s_prev), _curr(s_curr)
//	{
//	}
//	constexpr inline CxPrevCurrPair(Type&& s_prev, Type&& s_curr)
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
//	constexpr inline void back_up_and_update(const Type& n_curr)
//	{
//		_prev = std::move(_curr);
//		_curr = n_curr;
//	}
//	constexpr inline void back_up_and_update(Type&& n_curr)
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
//	constexpr inline Type& operator () ()
//	{
//		return _curr;
//	}
//	constexpr inline const Type& operator () () const
//	{
//		return _curr;
//	}
//
//	GEN_GETTER_BY_CON_REF(prev)
//	GEN_GETTER_BY_CON_REF(curr)
//};
//--------
template<typename Type>
class MoveOnlyPrevCurrPair final
{
private:		// variables
	Type _prev, _curr;
	
public:		// functions
	inline MoveOnlyPrevCurrPair() = default;
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(MoveOnlyPrevCurrPair);
	~MoveOnlyPrevCurrPair() = default;

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

	inline auto operator <=> (const MoveOnlyPrevCurrPair& to_cmp) const
		= default;

	inline Type& operator () ()
	{
		return _curr;
	}
	inline const Type& operator () () const
	{
		return _curr;
	}

	GEN_GETTER_BY_CON_REF(prev);
	GEN_GETTER_BY_CON_REF(curr);
};

//template<typename Type>
//class CxMoveOnlyPrevCurrPair final
//{
//private:		// variables
//	Type _prev, _curr;
//	
//public:		// functions
//	constexpr inline CxMoveOnlyPrevCurrPair() = default;
//	GEN_CX_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(CxMoveOnlyPrevCurrPair);
//	constexpr ~CxMoveOnlyPrevCurrPair() = default;
//
//	constexpr inline void back_up()
//	{
//		_prev = std::move(_curr);
//		_curr = Type();
//	}
//
//	constexpr inline void back_up_and_update(Type&& n_curr)
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
//	constexpr inline Type& operator () ()
//	{
//		return _curr;
//	}
//	constexpr inline const Type& operator () () const
//	{
//		return _curr;
//	}
//
//	GEN_GETTER_BY_CON_REF(prev);
//	GEN_GETTER_BY_CON_REF(curr);
//};
//--------
//template<typename Type>
//constexpr inline bool is_prev_curr_pair()
//{
//	return misc_util::is_specialization<Type, PrevCurrPair>();
//}
//template<typename Type>
//constexpr inline bool is_cx_prev_curr_pair()
//{
//	return misc_util::is_specialization<Type, CxPrevCurrPair>();
//}
//
//template<typename Type>
//constexpr inline bool is_move_only_prev_curr_pair()
//{
//	return misc_util::is_specialization<Type, MoveOnlyPrevCurrPair>();
//}
//template<typename Type>
//constexpr inline bool is_cx_move_only_prev_curr_pair()
//{
//	return misc_util::is_specialization<Type, CxMoveOnlyPrevCurrPair>();
//}
GEN_IS_SPECIALIZATION_CHECK_FUNCS(is_prev_curr_pair, PrevCurrPair);
template<typename Type>
constexpr inline bool is_prev_curr_pair()
{
	GEN_IS_SPECIALIZATION_FUNC_CONTENTS(is_prev_curr_pair);
}

GEN_IS_SPECIALIZATION_CHECK_FUNCS(is_move_only_prev_curr_pair,
	MoveOnlyPrevCurrPair);
template<typename Type>
constexpr inline bool is_move_only_prev_curr_pair()
{
	GEN_IS_SPECIALIZATION_FUNC_CONTENTS(is_move_only_prev_curr_pair);
}
//--------
} // namespace containers

} // namespace liborangepower


#endif		// liborangepower_containers_prev_curr_pair_classes_hpp
