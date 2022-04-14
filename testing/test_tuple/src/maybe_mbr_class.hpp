#ifndef src_maybe_mbr_class_hpp
#define src_maybe_mbr_class_hpp

#include "misc_includes.hpp"

template<bool have_mbr, typename T>
class MaybeMbr
{
public:		// variables
	T mbr;
};

template<typename T>
class MaybeMbr<false, T>
{
};

#endif		// src_maybe_mbr_class_hpp
