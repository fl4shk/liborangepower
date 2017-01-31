#ifndef liborangepower_array_helper_class_hpp
#define liborangepower_array_helper_class_hpp



#include "misc_types.hpp"
#include "misc_defines.hpp"


// This is a VERY thin wrapper class for working with 1D arrays
template< typename type >
class array_helper
{
public:			// variables
	type* the_array = NULL;
	
protected:		// variables
	u32 size = 0;
	
public:			// functions
	array_helper()
	{
	}
	
	array_helper( type* s_the_array, u32 s_size )
		: the_array(s_the_array), size(s_size)
	{
	}
	
	array_helper( const array_helper<type>& to_copy )
		: the_array(to_copy.the_array), size(to_copy.size)
	{
	}
	
	void init( type* s_the_array, u32 s_size )
	{
		the_array = s_the_array;
		size = s_size;
	}
	
	
	array_helper<type>& operator = ( const array_helper<type>& to_copy )
	{
		the_array = to_copy.the_array;
		size = to_copy.size;
		
		return *this;
	}
	
	
	const type* get_the_array() const
	{
		return the_array;
	}
	
	u32 get_size() const
	{
		return size;
	}
	
	type& at( u32 offset )
	{
		return the_array[offset];
	}
	const type& at( u32 offset ) const
	{
		return the_array[offset];
	}
	
	
} __attribute__((_align4));


#endif		// liborangepower_array_helper_class_hpp
