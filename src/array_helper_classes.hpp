#ifndef liborangepower_array_helper_classes_hpp
#define liborangepower_array_helper_classes_hpp



#include "misc_types.hpp"
#include "misc_defines.hpp"

template< typename type, size_t _size >
class array_csz_helper
{
public:			// variables
	type* the_array = NULL;
	
protected:		// variables
	static constexpr size_t size = _size;
	
public:			// functions
	array_csz_helper()
	{
	}
	
	array_csz_helper( type* s_the_array ) : the_array(s_the_array)
	{
	}
	
	array_csz_helper( const array_csz_helper<type>& to_copy )
		: the_array(to_copy.the_array)
	{
	}
	
	void init( type* s_the_array )
	{
		the_array = s_the_array;
	}
	
	
	array_csz_helper<type>& operator = 
		( const array_csz_helper<type>& to_copy )
	{
		the_array = to_copy.the_array;
		
		return *this;
	}
	
	
	const type* get_the_array() const
	{
		return the_array;
	}
	
	size_t get_size() const
	{
		return size;
	}
	
	type& at( size_t offset )
	{
		return the_array[offset];
	}
	const type& at( size_t offset ) const
	{
		return the_array[offset];
	}
	
	
} __attribute__((_align4));



// This is a VERY thin wrapper class for working with 1D arrays of
// arbitrary sizes
template< typename type >
class array_helper
{
public:			// variables
	type* the_array = NULL;
	
protected:		// variables
	size_t size = 0;
	
public:			// functions
	array_helper()
	{
	}
	
	array_helper( type* s_the_array, size_t s_size )
		: the_array(s_the_array), size(s_size)
	{
	}
	
	array_helper( const array_helper<type>& to_copy )
		: the_array(to_copy.the_array), size(to_copy.size)
	{
	}
	
	void init( type* s_the_array, size_t s_size )
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
	
	size_t get_size() const
	{
		return size;
	}
	
	type& at( size_t offset )
	{
		return the_array[offset];
	}
	const type& at( size_t offset ) const
	{
		return the_array[offset];
	}
	
	
} __attribute__((_align4));


#endif		// liborangepower_array_helper_classes_hpp
