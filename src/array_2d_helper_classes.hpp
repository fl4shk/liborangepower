#ifndef liborangepower_array_2d_helper_classes_hpp
#define liborangepower_array_2d_helper_classes_hpp

#include "misc_types.hpp"
#include "vec2_classes.hpp"



// This utility class is intended to be used when inherently 2D data, with
// CONSTANT dimensions, is stored within a 1D array.
template< typename type, size_t _width, size_t _height >
class array_csz_2d_helper
{
protected:		// variables
	static constexpr vec2<size_t> size_2d = { _width, _height };
	static constexpr size_t size = size_2d.x * size_2d.y;
	
public:			// variables
	type* the_array = NULL;
	
public:			// functions
	inline array_csz_2d_helper()
	{
	}
	inline array_csz_2d_helper( type* s_the_array )
		: the_array(s_the_array)
	{
	}
	
	void init( type* s_the_array )
	{
		the_array = s_the_array;
	}
	
	array_csz_2d_helper< type, _width, _height >& operator = 
		( const array_csz_2d_helper< type, _width, _height >& to_copy )
	{
		the_array = to_copy.the_array;
		
		return *this;
	}
	
	
	const type* get_the_array() const
	{
		return the_array;
	}
	
	size_t width() const
	{
		return size_2d.x;
	}
	size_t height() const
	{
		return size_2d.y;
	}
	
	const vec2<size_t>& get_size_2d() const
	{
		return size_2d;
	}
	size_t get_size() const
	{
		return size;
	}
	
	type& at( size_t x, size_t y )
	{
		return the_array[ y * size_2d.x + x ];
	}
	type& at( const vec2<size_t>& offset_2d )
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	type& at( const vec2_s32& offset_2d )
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	
	
	const type& at( size_t x, size_t y ) const
	{
		return the_array[ y * size_2d.x + x ];
	}
	const type& at( const vec2<size_t>& offset_2d ) const
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	const type& at( const vec2_s32& offset_2d ) const
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	
	
	
} __attribute__((_align4));

// This utility class is intended to be used when inherently 2D data is
// stored within a 1D array.
template< typename type >
class array_2d_helper
{
protected:		// variables
	vec2<size_t> size_2d;
	size_t size = 0;
	
public:			// variables
	type* the_array = NULL;
	
public:			// functions
	//array_2d_helper() : size_2d({ 0, 0 }), size(0), the_array(0)
	//{
	//}
	inline array_2d_helper()
	{
	}
	inline array_2d_helper( type* s_the_array, 
		const vec2<size_t>& s_size_2d )
		: size_2d(s_size_2d), size( s_size_2d.x * s_size_2d.y ),
		the_array(s_the_array)
	{
	}
	
	void init( type* s_the_array, const vec2<size_t>& s_size_2d )
	{
		size_2d = s_size_2d;
		size = size_2d.x * size_2d.y;
		the_array = s_the_array;
	}
	
	array_2d_helper<type>& operator = 
		( const array_2d_helper<type>& to_copy )
	{
		size_2d = to_copy.size_2d;
		size = to_copy.size;
		the_array = to_copy.the_array;
		
		return *this;
	}
	
	
	const type* get_the_array() const
	{
		return the_array;
	}
	
	size_t width() const
	{
		return size_2d.x;
	}
	size_t height() const
	{
		return size_2d.y;
	}
	
	const vec2<size_t>& get_size_2d() const
	{
		return size_2d;
	}
	size_t get_size() const
	{
		return size;
	}
	
	type& at( size_t x, size_t y )
	{
		return the_array[ y * size_2d.x + x ];
	}
	type& at( const vec2<size_t>& offset_2d )
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	type& at( const vec2_s32& offset_2d )
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	
	
	const type& at( size_t x, size_t y ) const
	{
		return the_array[ y * size_2d.x + x ];
	}
	const type& at( const vec2<size_t>& offset_2d ) const
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	const type& at( const vec2_s32& offset_2d ) const
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	
	
	
} __attribute__((_align4));



#endif		// liborangepower_array_2d_helper_classes_hpp
