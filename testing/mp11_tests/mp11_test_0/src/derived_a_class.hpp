#ifndef src_derived_a_class_hpp
#define src_derived_a_class_hpp

// src/derived_a_class.hpp

#include "misc_includes.hpp"

#define DERIVED_CLASS
#include "base_class.hpp"

class DerivedA : public Base
{
public:		// static variables
	MP11_DECLARE_IDENT_STATIC_VARS
};

#undef DERIVED_CLASS


#endif		// src_derived_a_class_hpp
