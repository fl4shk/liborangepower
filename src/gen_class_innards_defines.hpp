#ifndef liborangepower_gen_class_innards_defines_hpp
#define liborangepower_gen_class_innards_defines_hpp

#define GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(Type, copy_dd, move_dd) \
	inline Type(const Type& to_copy) = copy_dd; \
	inline Type(Type&& to_move) = move_dd; \
	inline Type& operator = (const Type& to_copy) = copy_dd; \
	inline Type& operator = (Type&& to_move) = move_dd;


/*
#define GEN_COPY_CONSTRUCTOR_AND_ASSIGN(Type) \
	inline Type(const Type& to_copy) = default; \
	inline Type& operator = (const Type& to_copy) = default;
*/

#define GEN_COPY_ONLY_CONSTRUCTORS_AND_ASSIGN(Type) \
	GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(Type, default, delete)

#define GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Type) \
	GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(Type, delete, default)

#define GEN_NO_CM_CONSTRUCTORS_AND_ASSIGN(Type) \
	GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(Type, delete, delete)

#define GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Type) \
	GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(Type, default, default)


/*
#define GEN_COPY_CONSTRUCTOR(Type, dd) \
	inline Type(const Type& to_copy) = dd;
#define GEN_MOVE_CONSTRUCTOR(Type, dd) \
	inline Type(Type&& to_move) = dd;

#define GEN_COPY_ASSIGN_OP(Type, dd) \
	inline Type& operator = (const Type& to_copy) = dd;
#define GEN_MOVE_ASSIGN_OP(Type, dd) \
	inline Type& operator = (Type&& to_move) = dd;
*/

// Getters

#ifndef GEN_GENERIC_GETTER_BY_VAL
// By value
#define GEN_GENERIC_GETTER_BY_VAL(prefix, suffix) \
inline decltype(prefix##suffix) suffix() const \
{ \
	return prefix##suffix; \
}
#endif

#ifndef GEN_GENERIC_GETTER_AS_POINTER
// As a pointer
#define GEN_GENERIC_GETTER_AS_POINTER(prefix, suffix) \
inline decltype(prefix##suffix)* suffix() \
{ \
	return &prefix##suffix; \
}
#endif

#ifndef GEN_GETTER_BY_VAL
// By value
#define GEN_GETTER_BY_VAL(suffix) \
GEN_GENERIC_GETTER_BY_VAL(_, suffix)
#endif


#ifndef GEN_GETTER_AS_POINTER
// As a pointer
#define GEN_GETTER_AS_POINTER(suffix) \
GEN_GENERIC_GETTER_AS_POINTER(_, suffix)
#endif



#ifndef GEN_GENERIC_GETTER_BY_CON_REF
// By constant reference
#define GEN_GENERIC_GETTER_BY_CON_REF(prefix, suffix) \
inline const decltype(prefix##suffix)& suffix() const \
{ \
	return prefix##suffix; \
}
#endif

#ifndef GEN_GETTER_BY_CON_REF
// By constant reference
#define GEN_GETTER_BY_CON_REF(suffix) \
GEN_GENERIC_GETTER_BY_CON_REF(_, suffix)
#endif



#ifndef GEN_GENERIC_GETTER_BY_REF
// By reference
#define GEN_GENERIC_GETTER_BY_REF(prefix, suffix) \
inline decltype(prefix##suffix)& suffix() \
{ \
	return prefix##suffix; \
}
#endif

#ifndef GEN_GETTER_BY_REF
// By reference
#define GEN_GETTER_BY_REF(suffix) \
GEN_GENERIC_GETTER_BY_REF(_, suffix)
#endif

#ifndef GEN_GETTERS_BY_CON_REF_AND_REF
#define GEN_GETTERS_BY_CON_REF_AND_REF(suffix) \
GEN_GETTER_BY_CON_REF(suffix) \
GEN_GETTER_BY_REF(suffix)
#endif



#ifndef GEN_STATIC_GENERIC_GETTER_BY_VAL
// By value
#define GEN_STATIC_GENERIC_GETTER_BY_VAL(prefix, suffix) \
static inline decltype(prefix##suffix) suffix() const \
{ \
	return prefix##suffix; \
}
#endif

#ifndef GEN_STATIC_GETTER_BY_VAL
// By value
#define GEN_STATIC_GETTER_BY_VAL(suffix) \
GEN_STATIC_GENERIC_GETTER_BY_VAL(_, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_GETTER_BY_CON_REF
// By constant reference
#define GEN_STATIC_GENERIC_GETTER_BY_CON_REF(prefix, suffix) \
static inline const decltype(prefix##suffix)& suffix() const \
{ \
	return prefix##suffix; \
}
#endif

#ifndef GEN_STATIC_GETTER_BY_CON_REF
// By constant reference
#define GEN_STATIC_GETTER_BY_CON_REF(suffix) \
GEN_STATIC_GENERIC_GETTER_BY_CON_REF(_, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_GETTER_BY_REF
// By reference
#define GEN_STATIC_GENERIC_GETTER_BY_REF(prefix, suffix) \
static inline decltype(prefix##suffix)& suffix() \
{ \
	return prefix##suffix; \
}
#endif

#ifndef GEN_STATIC_GETTER_BY_REF
// By reference
#define GEN_STATIC_GETTER_BY_REF(suffix) \
GEN_STATIC_GENERIC_GETTER_BY_REF(_, suffix)
#endif


// Setters

#ifndef GEN_GENERIC_SETTER_BY_VAL
// By value
#define GEN_GENERIC_SETTER_BY_VAL(prefix, suffix) \
template<typename Type> \
inline decltype(prefix##suffix) set_##suffix(Type to_copy) \
{ \
	prefix##suffix = to_copy; \
	return prefix##suffix; \
}
#endif

#ifndef GEN_SETTER_BY_VAL
// By value
#define GEN_SETTER_BY_VAL(suffix) \
GEN_GENERIC_SETTER_BY_VAL(_, suffix)
#endif



#ifndef GEN_GENERIC_SETTER_BY_CON_REF
// By const reference
#define GEN_GENERIC_SETTER_BY_CON_REF(prefix, suffix) \
template<typename Type> \
inline const decltype(prefix##suffix)& set_##suffix(const Type& to_copy) \
{ \
	prefix##suffix = to_copy; \
	return prefix##suffix; \
}
#endif

#ifndef GEN_SETTER_BY_CON_REF
// By const reference
#define GEN_SETTER_BY_CON_REF(suffix) \
GEN_GENERIC_SETTER_BY_CON_REF(_, suffix)
#endif



#ifndef GEN_GENERIC_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_GENERIC_SETTER_BY_RVAL_REF(prefix, suffix) \
template<typename Type> \
inline const decltype(prefix##suffix)& set_##suffix(Type&& to_move) \
{ \
	prefix##suffix = std::move(to_move); \
	return prefix##suffix; \
}
#endif

#ifndef GEN_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_SETTER_BY_RVAL_REF(suffix) \
GEN_GENERIC_SETTER_BY_RVAL_REF(_, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_SETTER_BY_VAL
// By value
#define GEN_STATIC_GENERIC_SETTER_BY_VAL(prefix, suffix) \
template<typename Type> \
static inline decltype(prefix##suffix) set_##suffix(Type to_copy) \
{ \
	prefix##suffix = to_copy; \
	return prefix##suffix; \
}
#endif

#ifndef GEN_STATIC_SETTER_BY_VAL
// By value
#define GEN_STATIC_SETTER_BY_VAL(suffix) \
GEN_STATIC_GENERIC_SETTER_BY_VAL(_, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_SETTER_BY_CON_REF
// By const reference
#define GEN_STATIC_GENERIC_SETTER_BY_CON_REF(prefix, suffix) \
template<typename Type> \
static inline const decltype(prefix##suffix)& set_##suffix \
	(const Type& to_copy) \
{ \
	prefix##suffix = to_copy; \
	return prefix##suffix; \
}
#endif

#ifndef GEN_STATIC_SETTER_BY_CON_REF
// By const reference
#define GEN_STATIC_SETTER_BY_CON_REF(suffix) \
GEN_STATIC_GENERIC_SETTER_BY_CON_REF(_, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_STATIC_GENERIC_SETTER_BY_RVAL_REF(prefix, suffix) \
static inline const decltype(prefix##suffix)& set_##suffix \
	(decltype(prefix##suffix)&& to_move) \
{ \
	prefix##suffix = std::move(to_move); \
	return prefix##suffix; \
}
#endif

#ifndef GEN_STATIC_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_STATIC_SETTER_BY_RVAL_REF(suffix) \
GEN_STATIC_GENERIC_SETTER_BY_RVAL_REF(_, suffix)
#endif



#define GEN_GETTER_AND_SETTER_BY_CON_REF(stuff) \
	GEN_GETTER_BY_CON_REF(stuff) \
	GEN_SETTER_BY_CON_REF(stuff)


#define GEN_GETTER_AND_SETTER_BY_VAL(stuff) \
	GEN_GETTER_BY_VAL(stuff) \
	GEN_SETTER_BY_VAL(stuff)


#define GEN_GETTER_BCR_AND_SETTER_BRR(stuff) \
	GEN_GETTER_BY_CON_REF(stuff) \
	GEN_SETTER_BY_RVAL_REF(stuff)

#endif		// liborangepower_gen_class_innards_defines_hpp
