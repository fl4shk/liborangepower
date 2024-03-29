#ifndef liborangepower_gen_class_innards_defines_hpp
#define liborangepower_gen_class_innards_defines_hpp
//--------
#include "misc/misc_defines.hpp"
#include "metaprog_defines.hpp"
//--------
/*
#define GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(T, copy_dd, move_dd) \
	inline T(const T& to_copy) = copy_dd; \
	inline T(T&& to_move) = move_dd; \
	inline T& operator = (const T& to_copy) = copy_dd; \
	inline T& operator = (T&& to_move) = move_dd;
*/

#define GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(T, cx_cond, \
	copy_dd_cond, move_dd_cond) \
	CX_WHEN(cx_cond) \
		inline T(const T& to_copy) \
		= IF(copy_dd_cond)(default, delete); \
	CX_WHEN(cx_cond) \
		inline T(T&& to_move) \
		= IF(move_dd_cond)(default, delete); \
	CX_WHEN(cx_cond) \
		inline T& operator = (const T& to_copy) \
		= IF(copy_dd_cond)(default, delete); \
	CX_WHEN(cx_cond) \
		inline T& operator = (T&& to_move) \
		= IF(move_dd_cond)(default, delete);

/*
#define GEN_COPY_CONSTRUCTOR_AND_ASSIGN(T) \
	inline T(const T& to_copy) = default; \
	inline T& operator = (const T& to_copy) = default;
*/

#define GEN_COPY_ONLY_CONSTRUCTORS_AND_ASSIGN(T) \
	GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(T, 0, 1, 0)

#define GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(T) \
	GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(T, 0, 0, 1)

#define GEN_NO_CM_CONSTRUCTORS_AND_ASSIGN(T) \
	GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(T, 0, 0, 0)

#define GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(T) \
	GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(T, 0, 1, 1)

#define GEN_CX_COPY_ONLY_CONSTRUCTORS_AND_ASSIGN(T) \
	GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(T, 1, 1, 0)

#define GEN_CX_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(T) \
	GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(T, 1, 0, 1)

#define GEN_CX_NO_CM_CONSTRUCTORS_AND_ASSIGN(T) \
	GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(T, 1, 0, 0)

#define GEN_CX_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(T) \
	GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(T, 1, 1, 1)

/*
#define GEN_COPY_CONSTRUCTOR(T, dd) \
	constexpr inline T(const T& to_copy) = dd;
#define GEN_MOVE_CONSTRUCTOR(T, dd) \
	constexpr inline T(T&& to_move) = dd;

#define GEN_COPY_ASSIGN_OP(T, dd) \
	constexpr inline T& operator = (const T& to_copy) = dd;
#define GEN_MOVE_ASSIGN_OP(T, dd) \
	constexpr inline T& operator = (T&& to_move) = dd;
*/
//--------
//--------
// Getters
//--------
#ifndef GEN_GENERIC_GETTER_BY_VAL
// By value
#define GEN_GENERIC_GETTER_BY_VAL(cx_cond, prefix, suffix) \
CX_WHEN(cx_cond) inline decltype(prefix ## suffix) suffix () const \
{ \
	return prefix ## suffix; \
}
#endif

#ifndef GEN_GENERIC_GETTER_AS_PTR
// As a pointer
#define GEN_GENERIC_GETTER_AS_PTR(cx_cond, prefix, suffix) \
CX_WHEN(cx_cond) inline decltype(prefix ## suffix)* suffix () \
{ \
	return & prefix ## suffix; \
}
#endif

#ifndef GEN_GETTER_BY_VAL
// By value
#define GEN_GETTER_BY_VAL(suffix) \
GEN_GENERIC_GETTER_BY_VAL(0, _, suffix)
#endif

#ifndef GEN_CX_GETTER_BY_VAL
// By value
#define GEN_CX_GETTER_BY_VAL(suffix) \
GEN_GENERIC_GETTER_BY_VAL(1, _, suffix)
#endif


#ifndef GEN_GETTER_AS_PTR
// As a pointer
#define GEN_GETTER_AS_PTR(suffix) \
GEN_GENERIC_GETTER_AS_PTR(0, _, suffix)
#endif

#ifndef GEN_CX_GETTER_AS_PTR
// As a pointer
#define GEN_CX_GETTER_AS_PTR(suffix) \
GEN_GENERIC_GETTER_AS_PTR(1, _, suffix)
#endif
//--------
#ifndef GEN_GENERIC_GETTER_BY_CON_REF
// By constant reference
#define GEN_GENERIC_GETTER_BY_CON_REF(cx_cond, prefix, suffix) \
CX_WHEN(cx_cond) inline const decltype(prefix ## suffix) & suffix () const \
{ \
	return prefix ## suffix; \
}
#endif

#ifndef GEN_GETTER_BY_CON_REF
// By constant reference
#define GEN_GETTER_BY_CON_REF(suffix) \
GEN_GENERIC_GETTER_BY_CON_REF(0, _, suffix)
#endif

#ifndef GEN_CX_GETTER_BY_CON_REF
// By constant reference
#define GEN_CX_GETTER_BY_CON_REF(suffix) \
GEN_GENERIC_GETTER_BY_CON_REF(1, _, suffix)
#endif



#ifndef GEN_GENERIC_GETTER_BY_REF
// By reference
#define GEN_GENERIC_GETTER_BY_REF(cx_cond, prefix, suffix) \
CX_WHEN(cx_cond) inline decltype(prefix ## suffix)& suffix () \
{ \
	return prefix ## suffix; \
}
#endif

#ifndef GEN_GETTER_BY_REF
// By reference
#define GEN_GETTER_BY_REF(suffix) \
GEN_GENERIC_GETTER_BY_REF(0, _, suffix)
#endif

#ifndef GEN_CX_GETTER_BY_REF
// By reference
#define GEN_CX_GETTER_BY_REF(suffix) \
GEN_GENERIC_GETTER_BY_REF(1, _, suffix)
#endif

#ifndef GEN_GETTERS_BY_CON_REF_AND_REF
#define GEN_GETTERS_BY_CON_REF_AND_REF(suffix) \
GEN_GETTER_BY_CON_REF(suffix) \
GEN_GETTER_BY_REF(suffix)
#endif



#ifndef GEN_STATIC_GENERIC_GETTER_BY_VAL
// By value
#define GEN_STATIC_GENERIC_GETTER_BY_VAL(cx_cond, prefix, suffix) \
static CX_WHEN(cx_cond) inline decltype(prefix ## suffix) suffix () const \
{ \
	return prefix ## suffix; \
}
#endif

#ifndef GEN_STATIC_GETTER_BY_VAL
// By value
#define GEN_STATIC_GETTER_BY_VAL(suffix) \
GEN_STATIC_GENERIC_GETTER_BY_VAL(0, _, suffix)
#endif

#ifndef GEN_STATIC_CX_GETTER_BY_VAL
// By value
#define GEN_STATIC_CX_GETTER_BY_VAL(suffix) \
GEN_STATIC_GENERIC_GETTER_BY_VAL(1, _, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_GETTER_BY_CON_REF
// By constant reference
#define GEN_STATIC_GENERIC_GETTER_BY_CON_REF(prefix, suffix) \
static CX_WHEN(cx_cond) inline const decltype(prefix ## suffix) & \
	suffix () const \
{ \
	return prefix ## suffix; \
}
#endif

#ifndef GEN_STATIC_GETTER_BY_CON_REF
// By constant reference
#define GEN_STATIC_GETTER_BY_CON_REF(suffix) \
GEN_STATIC_GENERIC_GETTER_BY_CON_REF(0, _, suffix)
#endif

#ifndef GEN_STATIC_CX_GETTER_BY_CON_REF
// By constant reference
#define GEN_STATIC_CX_GETTER_BY_CON_REF(suffix) \
GEN_STATIC_GENERIC_GETTER_BY_CON_REF(1, _, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_GETTER_BY_REF
// By reference
#define GEN_STATIC_GENERIC_GETTER_BY_REF(prefix, suffix) \
static CX_WHEN(cx_cond) inline decltype(prefix ## suffix)& suffix () \
{ \
	return prefix ## suffix; \
}
#endif

#ifndef GEN_STATIC_GETTER_BY_REF
// By reference
#define GEN_STATIC_GETTER_BY_REF(suffix) \
GEN_STATIC_GENERIC_GETTER_BY_REF(0, _, suffix)
#endif

#ifndef GEN_STATIC_CX_GETTER_BY_REF
// By reference
#define GEN_STATIC_CX_GETTER_BY_REF(suffix) \
GEN_STATIC_GENERIC_GETTER_BY_REF(1, _, suffix)
#endif
//--------
// Setters
//--------
#ifndef GEN_GENERIC_SETTER_BY_VAL
// By value
#define GEN_GENERIC_SETTER_BY_VAL(cx_cond, prefix, suffix) \
template<typename T> \
CX_WHEN(cx_cond) inline decltype(prefix ## suffix) \
	set_ ## suffix (T to_copy) \
{ \
	prefix ## suffix = to_copy; \
	return prefix ## suffix; \
}
#endif

#ifndef GEN_SETTER_BY_VAL
// By value
#define GEN_SETTER_BY_VAL(suffix) \
GEN_GENERIC_SETTER_BY_VAL(0, _, suffix)
#endif

#ifndef GEN_CX_SETTER_BY_VAL
// By value
#define GEN_CX_SETTER_BY_VAL(suffix) \
GEN_GENERIC_SETTER_BY_VAL(1, _, suffix)
#endif



#ifndef GEN_GENERIC_SETTER_BY_CON_REF
// By const reference
#define GEN_GENERIC_SETTER_BY_CON_REF(cx_cond, prefix, suffix) \
template<typename T> \
CX_WHEN(cx_cond) inline const decltype(prefix ## suffix) & \
	set_ ## suffix (const T& to_copy) \
{ \
	prefix ## suffix = to_copy; \
	return prefix ## suffix; \
}
#endif

#ifndef GEN_SETTER_BY_CON_REF
// By const reference
#define GEN_SETTER_BY_CON_REF(suffix) \
GEN_GENERIC_SETTER_BY_CON_REF(0, _, suffix)
#endif

#ifndef GEN_CX_SETTER_BY_CON_REF
// By const reference
#define GEN_CX_SETTER_BY_CON_REF(suffix) \
GEN_GENERIC_SETTER_BY_CON_REF(1, _, suffix)
#endif



#ifndef GEN_GENERIC_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_GENERIC_SETTER_BY_RVAL_REF(cx_cond, prefix, suffix) \
template<typename T> \
CX_WHEN(cx_cond) inline const decltype(prefix ## suffix) & \
	set_ ## suffix (T&& to_move) \
{ \
	prefix ## suffix = std::move(to_move); \
	return prefix ## suffix; \
}
#endif

#ifndef GEN_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_SETTER_BY_RVAL_REF(suffix) \
GEN_GENERIC_SETTER_BY_RVAL_REF(0, _, suffix)
#endif

#ifndef GEN_CX_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_CX_SETTER_BY_RVAL_REF(suffix) \
GEN_GENERIC_SETTER_BY_RVAL_REF(1, _, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_SETTER_BY_VAL
// By value
#define GEN_STATIC_GENERIC_SETTER_BY_VAL(cx_cond, prefix, suffix) \
template<typename T> \
static CX_WHEN(cx_cond) inline decltype(prefix ## suffix) \
	set_ ## suffix (T to_copy) \
{ \
	prefix ## suffix = to_copy; \
	return prefix ## suffix; \
}
#endif

#ifndef GEN_STATIC_SETTER_BY_VAL
// By value
#define GEN_STATIC_SETTER_BY_VAL(suffix) \
GEN_STATIC_GENERIC_SETTER_BY_VAL(0, _, suffix)
#endif

#ifndef GEN_STATIC_CX_SETTER_BY_VAL
// By value
#define GEN_STATIC_CX_SETTER_BY_VAL(suffix) \
GEN_STATIC_GENERIC_SETTER_BY_VAL(1, _, suffix)
#endif


#ifndef GEN_STATIC_GENERIC_SETTER_BY_CON_REF
// By const reference
#define GEN_STATIC_GENERIC_SETTER_BY_CON_REF(cx_cond, prefix, suffix) \
template<typename T> \
static CX_WHEN(cx_cond) inline const decltype(prefix ## suffix) & \
	set_ ## suffix (const T& to_copy) \
{ \
	prefix ## suffix = to_copy; \
	return prefix ## suffix; \
}
#endif

#ifndef GEN_STATIC_SETTER_BY_CON_REF
// By const reference
#define GEN_STATIC_SETTER_BY_CON_REF(suffix) \
GEN_STATIC_GENERIC_SETTER_BY_CON_REF(0, _, suffix)
#endif

#ifndef GEN_STATIC_CX_SETTER_BY_CON_REF
// By const reference
#define GEN_STATIC_CX_SETTER_BY_CON_REF(suffix) \
GEN_STATIC_GENERIC_SETTER_BY_CON_REF(1, _, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_STATIC_GENERIC_SETTER_BY_RVAL_REF(cx_cond, prefix, suffix) \
static CX_WHEN(cx_cond) inline const decltype(prefix ## suffix) & \
	set_ ## suffix (decltype(prefix ## suffix) && to_move) \
{ \
	prefix ## suffix = std::move(to_move); \
	return prefix ## suffix; \
}
#endif

#ifndef GEN_STATIC_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_STATIC_SETTER_BY_RVAL_REF(suffix) \
GEN_STATIC_GENERIC_SETTER_BY_RVAL_REF(0, _, suffix)
#endif

#ifndef GEN_STATIC_CX_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_STATIC_CX_SETTER_BY_RVAL_REF(suffix) \
GEN_STATIC_GENERIC_SETTER_BY_RVAL_REF(1, _, suffix)
#endif
//--------
#define GEN_GETTER_AND_SETTER_BY_CON_REF(stuff) \
	GEN_GETTER_BY_CON_REF(stuff) \
	GEN_SETTER_BY_CON_REF(stuff)
#define GEN_CX_GETTER_AND_CX_SETTER_BY_CON_REF(stuff) \
	GEN_CX_GETTER_BY_CON_REF(stuff) \
	GEN_CX_SETTER_BY_CON_REF(stuff)

#define GEN_GETTER_AND_SETTER_BY_VAL(stuff) \
	GEN_GETTER_BY_VAL(stuff) \
	GEN_SETTER_BY_VAL(stuff)
#define GEN_CX_GETTER_AND_CX_SETTER_BY_VAL(stuff) \
	GEN_CX_GETTER_BY_VAL(stuff) \
	GEN_CX_SETTER_BY_VAL(stuff)


#define GEN_GETTER_BCR_AND_SETTER_BRR(stuff) \
	GEN_GETTER_BY_CON_REF(stuff) \
	GEN_SETTER_BY_RVAL_REF(stuff)
#define GEN_CX_GETTER_BCR_AND_CX_SETTER_BRR(stuff) \
	GEN_CX_GETTER_BY_CON_REF(stuff) \
	GEN_CX_SETTER_BY_RVAL_REF(stuff)
//--------
#endif		// liborangepower_gen_class_innards_defines_hpp
