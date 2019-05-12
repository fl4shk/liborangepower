#ifndef src_base_class_hpp
#define src_base_class_hpp

// src/base_class.hpp

#include "misc_includes.hpp"

class Base
{
MP11_MAKE_BASE_CLASS_INSIDES
};

#ifndef DERIVED_CLASS
#include "hierarchy_list.hpp"

MP11_MAKE_BASE_CLASS_ARR_GETTER_OUTSIDES(Base, HierarchyList)

#endif		// !defined(DERIVED_CLASS)

#endif		// src_base_class_hpp
