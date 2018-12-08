#ifndef thing_class_hpp
#define thing_class_hpp

#include "misc_includes.hpp"


class Thing
{
public:		// variables
	s32 x;

public:		// functions
	Thing();

	void set_x(s32 n_x);

};

//extern "C"
//{
//
//extern Thing* thing;
//
//}

#endif		// thing_class_hpp
