#ifndef liborangepower_gen_getter_setter_defines_hpp
#define liborangepower_gen_getter_setter_defines_hpp


// Getters

#ifndef GEN_GENERIC_GETTER_BY_VAL
// By value
#define GEN_GENERIC_GETTER_BY_VAL(prefix, suffix) \
inline decltype(prefix##suffix) suffix() const \
{ \
	return prefix##suffix; \
}
#endif

#ifndef GEN_GETTER_BY_VAL
// By value
#define GEN_GETTER_BY_VAL(suffix) \
GEN_GENERIC_GETTER_BY_VAL(_, suffix)
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
inline decltype(prefix##suffix) set_##suffix(decltype(prefix##suffix) to_copy) \
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
inline const decltype(prefix##suffix)& set_##suffix \
	(const decltype(prefix##suffix)& to_copy) \
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
inline const decltype(prefix##suffix)& set_##suffix \
	(decltype(prefix##suffix)&& to_move) \
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
static inline decltype(prefix##suffix) set_##suffix(decltype(prefix##suffix) to_copy) \
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
static inline const decltype(prefix##suffix)& set_##suffix \
	(const decltype(prefix##suffix)& to_copy) \
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

#endif		// liborangepower_gen_getter_setter_defines_hpp
