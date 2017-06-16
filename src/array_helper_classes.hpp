#ifndef liborangepower_array_helper_classes_hpp
#define liborangepower_array_helper_classes_hpp



#include "misc_types.hpp"
#include "misc_defines.hpp"

namespace liborangepower
{

namespace containers
{

template<typename Type, size_t _size>
class ArrayCszHelper
{
public:			// variables
	Type* the_array = NULL;
	
protected:		// variables
	static constexpr size_t size = _size;
	
public:			// functions
	ArrayCszHelper()
	{
	}
	
	ArrayCszHelper(Type* s_the_array) : the_array(s_the_array)
	{
	}
	
	ArrayCszHelper(const ArrayCszHelper<Type>& to_copy)
		: the_array(to_copy.the_array)
	{
	}
	
	void init(Type* s_the_array)
	{
		the_array = s_the_array;
	}
	
	
	ArrayCszHelper<Type>& operator = 
		(const ArrayCszHelper<Type>& to_copy)
	{
		the_array = to_copy.the_array;
		
		return *this;
	}
	
	
	const Type* get_the_array() const
	{
		return the_array;
	}
	
	size_t get_size() const
	{
		return size;
	}
	
	Type& at(size_t offset)
	{
		return the_array[offset];
	}
	const Type& at(size_t offset) const
	{
		return the_array[offset];
	}
	
	
} __attribute__((_align4));



// This is a VERY thin wrapper class for working with 1D arrays of
// arbitrary sizes
template<typename Type>
class ArrayHelper
{
public:			// variables
	Type* the_array = NULL;
	
protected:		// variables
	size_t size = 0;
	
public:			// functions
	ArrayHelper()
	{
	}
	
	ArrayHelper(Type* s_the_array, size_t s_size)
		: the_array(s_the_array), size(s_size)
	{
	}
	
	ArrayHelper(const ArrayHelper<Type>& to_copy)
		: the_array(to_copy.the_array), size(to_copy.size)
	{
	}
	
	void init(Type* s_the_array, size_t s_size)
	{
		the_array = s_the_array;
		size = s_size;
	}
	
	
	ArrayHelper<Type>& operator = (const ArrayHelper<Type>& to_copy)
	{
		the_array = to_copy.the_array;
		size = to_copy.size;
		
		return *this;
	}
	
	
	const Type* get_the_array() const
	{
		return the_array;
	}
	
	size_t get_size() const
	{
		return size;
	}
	
	Type& at(size_t offset)
	{
		return the_array[offset];
	}
	const Type& at(size_t offset) const
	{
		return the_array[offset];
	}
	
	
} __attribute__((_align4));

}

}

#endif		// liborangepower_array_helper_classes_hpp
