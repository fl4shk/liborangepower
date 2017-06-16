#ifndef liborangepower_array_2d_helper_classes_hpp
#define liborangepower_array_2d_helper_classes_hpp

#include "misc_types.hpp"
#include "Vec2_classes.hpp"



namespace liborangepower
{

namespace containers
{

// This utility class is intended to be used when inherently 2D data, with
// CONSTANT dimensions, is stored within a 1D array.
template<typename Type, size_t _width, size_t _height>
class ArrayCsz2dHelper
{
protected:		// variables
	static constexpr Vec2<size_t> size_2d = { _width, _height };
	static constexpr size_t size = size_2d.x * size_2d.y;
	
public:			// variables
	Type* the_array = NULL;
	
public:			// functions
	inline ArrayCsz2dHelper()
	{
	}
	inline ArrayCsz2dHelper(Type* s_the_array)
		: the_array(s_the_array)
	{
	}
	
	void init(Type* s_the_array)
	{
		the_array = s_the_array;
	}
	
	ArrayCsz2dHelper<Type, _width, _height>& operator = 
		(const ArrayCsz2dHelper<Type, _width, _height>& to_copy)
	{
		the_array = to_copy.the_array;
		
		return *this;
	}
	
	
	const Type* get_the_array() const
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
	
	const Vec2<size_t>& get_size_2d() const
	{
		return size_2d;
	}
	size_t get_size() const
	{
		return size;
	}
	
	Type& at(size_t x, size_t y)
	{
		return the_array[y * size_2d.x + x];
	}
	Type& at(const Vec2<size_t>& offset_2d)
	{
		return the_array[offset_2d.y * size_2d.x + offset_2d.x];
	}
	Type& at(const Vec2_s32& offset_2d)
	{
		return the_array[offset_2d.y * size_2d.x + offset_2d.x];
	}
	
	
	const Type& at(size_t x, size_t y) const
	{
		return the_array[y * size_2d.x + x];
	}
	const Type& at(const Vec2<size_t>& offset_2d) const
	{
		return the_array[offset_2d.y * size_2d.x + offset_2d.x];
	}
	const Type& at(const Vec2_s32& offset_2d) const
	{
		return the_array[offset_2d.y * size_2d.x + offset_2d.x];
	}
	
	
	
} __attribute__((_align4));

// This utility class is intended to be used when inherently 2D data is
// stored within a 1D array.
template<typename Type>
class Array2dHelper
{
protected:		// variables
	Vec2<size_t> size_2d;
	size_t size = 0;
	
public:			// variables
	Type* the_array = NULL;
	
public:			// functions
	//Array2dHelper() : size_2d({ 0, 0 }), size(0), the_array(0)
	//{
	//}
	inline Array2dHelper()
	{
	}
	inline Array2dHelper(Type* s_the_array, 
		const Vec2<size_t>& s_size_2d)
		: size_2d(s_size_2d), size(s_size_2d.x * s_size_2d.y),
		the_array(s_the_array)
	{
	}
	
	void init(Type* s_the_array, const Vec2<size_t>& s_size_2d)
	{
		size_2d = s_size_2d;
		size = size_2d.x * size_2d.y;
		the_array = s_the_array;
	}
	
	Array2dHelper<Type>& operator = 
		(const Array2dHelper<Type>& to_copy)
	{
		size_2d = to_copy.size_2d;
		size = to_copy.size;
		the_array = to_copy.the_array;
		
		return *this;
	}
	
	
	const Type* get_the_array() const
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
	
	const Vec2<size_t>& get_size_2d() const
	{
		return size_2d;
	}
	size_t get_size() const
	{
		return size;
	}
	
	Type& at(size_t x, size_t y)
	{
		return the_array[y * size_2d.x + x];
	}
	Type& at(const Vec2<size_t>& offset_2d)
	{
		return the_array[offset_2d.y * size_2d.x + offset_2d.x];
	}
	Type& at(const Vec2_s32& offset_2d)
	{
		return the_array[offset_2d.y * size_2d.x + offset_2d.x];
	}
	
	
	const Type& at(size_t x, size_t y) const
	{
		return the_array[y * size_2d.x + x];
	}
	const Type& at(const Vec2<size_t>& offset_2d) const
	{
		return the_array[offset_2d.y * size_2d.x + offset_2d.x];
	}
	const Type& at(const Vec2_s32& offset_2d) const
	{
		return the_array[offset_2d.y * size_2d.x + offset_2d.x];
	}
	
	
	
} __attribute__((_align4));


}


}



#endif		// liborangepower_array_2d_helper_classes_hpp
