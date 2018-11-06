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
	Type* ___arr = nullptr;

protected:		// variables
	static constexpr size_t ___size = _size;

public:			// functions
	ArrayCszHelper()
	{
	}

	ArrayCszHelper(Type* s_the_array) : ___arr(s_the_array)
	{
	}

	ArrayCszHelper(const ArrayCszHelper& to_copy) = default;

	void init(Type* s_the_array)
	{
		___arr = s_the_array;
	}


	ArrayCszHelper& operator = (const ArrayCszHelper& to_copy) = default;


	const Type* arr() const
	{
		return ___arr;
	}

	size_t size() const
	{
		return ___size;
	}

	Type& at(size_t offset)
	{
		return ___arr[offset];
	}
	const Type& at(size_t offset) const
	{
		return ___arr[offset];
	}


};



// This is a VERY thin wrapper class for working with 1D arrays of
// arbitrary sizes
template<typename Type>
class ArrayHelper
{
//public:			// variables
protected:		// variables
	Type* ___arr = nullptr;

protected:		// variables
	size_t ___size = 0;

public:			// functions
	inline ArrayHelper()
	{
	}

	inline ArrayHelper(Type* s_the_array, size_t s_size)
		: ___arr(s_the_array), ___size(s_size)
	{
	}

	inline ArrayHelper(const ArrayHelper& to_copy) = default;

	void init(Type* s_the_array, size_t s_size)
	{
		___arr = s_the_array;
		___size = s_size;
	}


	inline ArrayHelper& operator = (const ArrayHelper& to_copy) = default;


	const Type* arr() const
	{
		return ___arr;
	}

	size_t size() const
	{
		return ___size;
	}

	Type& at(size_t offset)
	{
		return ___arr[offset];
	}
	const Type& at(size_t offset) const
	{
		return ___arr[offset];
	}


};

} // namespace containers

} // namespace liborangepower

#endif		// liborangepower_array_helper_classes_hpp
