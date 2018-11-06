#ifndef liborangepower_array_2d_helper_classes_hpp
#define liborangepower_array_2d_helper_classes_hpp

#include "misc_types.hpp"
#include "vec2_classes.hpp"



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
	static constexpr Vec2<size_t> ___size_2d = {_width, _height};
	static constexpr size_t ___size = ___size_2d.x * ___size_2d.y;

//public:			// variables
	Type* ___arr = nullptr;

public:			// functions
	inline ArrayCsz2dHelper()
	{
	}
	inline ArrayCsz2dHelper(Type* s____arr)
		: ___arr(s____arr)
	{
	}
	inline ArrayCsz2dHelper(const ArrayCsz2dHelper& to_copy) = default;

	void init(Type* s____arr)
	{
		___arr = s____arr;
	}

	ArrayCsz2dHelper& operator = (const ArrayCsz2dHelper& to_copy) 
		= default;


	Type* arr() const
	{
		return ___arr;
	}

	size_t width() const
	{
		return ___size_2d.x;
	}
	size_t height() const
	{
		return ___size_2d.y;
	}

	const Vec2<size_t>& size_2d() const
	{
		return ___size_2d;
	}
	size_t size() const
	{
		return ___size;
	}

	Type& at(size_t x, size_t y)
	{
		return ___arr[y * ___size_2d.x + x];
	}
	Type& at(const Vec2<size_t>& offset_2d)
	{
		return ___arr[offset_2d.y * ___size_2d.x + offset_2d.x];
	}
	Type& at(const Vec2S32& offset_2d)
	{
		return ___arr[offset_2d.y * ___size_2d.x + offset_2d.x];
	}


	const Type& at(size_t x, size_t y) const
	{
		return ___arr[y * ___size_2d.x + x];
	}
	const Type& at(const Vec2<size_t>& offset_2d) const
	{
		return ___arr[offset_2d.y * ___size_2d.x + offset_2d.x];
	}
	const Type& at(const Vec2S32& offset_2d) const
	{
		return ___arr[offset_2d.y * ___size_2d.x + offset_2d.x];
	}



};

// This utility class is intended to be used when inherently 2D data is
// stored within a 1D array.
template<typename Type>
class Array2dHelper
{
protected:		// variables
	Vec2<size_t> ___size_2d;
	size_t ___size = 0;

//public:			// variables
	Type* ___arr = nullptr;

public:			// functions
	//Array2dHelper() : ___size_2d({ 0, 0 }), ___size(0), ___arr(0)
	//{
	//}
	inline Array2dHelper()
	{
	}
	inline Array2dHelper(Type* s____arr, 
		const Vec2<size_t>& s_size_2d)
		: ___size_2d(s_size_2d), ___size(s_size_2d.x * s_size_2d.y),
		___arr(s____arr)
	{
	}
	inline Array2dHelper(const Array2dHelper& to_copy) = default;

	void init(Type* s____arr, const Vec2<size_t>& s_size_2d)
	{
		___size_2d = s_size_2d;
		___size = ___size_2d.x * ___size_2d.y;
		___arr = s____arr;
	}

	Array2dHelper& operator = (const Array2dHelper& to_copy) = default;


	Type* arr() const
	{
		return ___arr;
	}

	size_t width() const
	{
		return ___size_2d.x;
	}
	size_t height() const
	{
		return ___size_2d.y;
	}

	const Vec2<size_t>& size_2d() const
	{
		return ___size_2d;
	}
	size_t size() const
	{
		return ___size;
	}

	Type& at(size_t x, size_t y)
	{
		return ___arr[y * ___size_2d.x + x];
	}
	Type& at(const Vec2<size_t>& offset_2d)
	{
		return ___arr[offset_2d.y * ___size_2d.x + offset_2d.x];
	}
	Type& at(const Vec2S32& offset_2d)
	{
		return ___arr[offset_2d.y * ___size_2d.x + offset_2d.x];
	}


	const Type& at(size_t x, size_t y) const
	{
		return ___arr[y * ___size_2d.x + x];
	}
	const Type& at(const Vec2<size_t>& offset_2d) const
	{
		return ___arr[offset_2d.y * ___size_2d.x + offset_2d.x];
	}
	const Type& at(const Vec2S32& offset_2d) const
	{
		return ___arr[offset_2d.y * ___size_2d.x + offset_2d.x];
	}



};


} // namespace containers


} // namespace liborangepower



#endif		// liborangepower_array_2d_helper_classes_hpp
