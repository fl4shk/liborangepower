#ifndef liborangepower_make_deferred_restorer_class_define_hpp
#define liborangepower_make_deferred_restorer_class_define_hpp

#include "metaprog_defines.hpp"

#define _INNER_MAKE_DEFERRED_RESTORER_CLASS_MEMB_VAR(type, var_name) \
	type _saved ## var_name

#define _INNER_MAKE_DEFERRED_RESTORER_CLASS_CTOR(type, var_name) \
	_saved_ ## var_name = std::move(self-> var_name )

#define _INNER_MAKE_DEFERRED_RESTORER_CLASS_DTOR(type, var_name) \
	self-> var_name = std::move(_saved ## var_name )


#define MAKE_DEFERRED_RESTORER_CLASS(name, self_t, ...) \
	class name \
	{ \
	protected:		/* variables */ \
		self_t* _self = nullptr; \
		EVAL(MAP_PAIRS(_INNER_MAKE_DEFERRED_RESTORER_CLASS_MEMB_VAR, \
			SEMICOLON, __VA_ARGS__)); \
	\
	public:		/* functions */ \
		inline name (self_t* s_self) \
			: _self(s_self) \
		{ \
			EVAL(MAP_PAIRS(_INNER_MAKE_DEFERRED_RESTORER_CLASS_CTOR, \
				SEMICOLON, __VA_ARGS__)); \
		} \
		virtual inline ~ name () \
		{ \
			EVAL(MAP_PAIRS(_INNER_MAKE_DEFERRED_RESTORER_CLASS_DTOR, \
				SEMICOLON, __VA_ARGS__)); \
		} \
	}

#endif		// liborangepower_make_deferred_restorer_class_define_hpp
