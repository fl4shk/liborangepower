#ifndef liborangepower_containers_array_2d_helper_classes_hpp
#define liborangepower_containers_array_2d_helper_classes_hpp

#include "../misc/misc_types.hpp"
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
	static constexpr Vec2<size_t> _size_2d = {_width, _height};
	static constexpr size_t _size = _size_2d.x * _size_2d.y;

//public:			// variables
	Type* _arr = nullptr;

public:			// functions
	inline ArrayCsz2dHelper()
	{
	}
	inline ArrayCsz2dHelper(Type* s_arr)
		: _arr(s_arr)
	{
	}
	inline ArrayCsz2dHelper(const ArrayCsz2dHelper& to_copy) = default;

	void init(Type* s_arr)
	{
		_arr = s_arr;
	}

	ArrayCsz2dHelper& operator = (const ArrayCsz2dHelper& to_copy) 
		= default;


	Type* arr() const
	{
		return _arr;
	}

	size_t width() const
	{
		return _size_2d.x;
	}
	size_t height() const
	{
		return _size_2d.y;
	}

	const Vec2<size_t>& size_2d() const
	{
		return _size_2d;
	}
	size_t size() const
	{
		return _size;
	}

	Type& at(size_t x, size_t y)
	{
		return _arr[y * _size_2d.x + x];
	}
	template<typename PosType>
	Type& at(const Vec2<PosType>& offset_2d)
	{
		return _arr[offset_2d.y * _size_2d.x + offset_2d.x];
	}


	const Type& at(size_t x, size_t y) const
	{
		return _arr[y * _size_2d.x + x];
	}
	template<typename PosType>
	const Type& at(const Vec2<PosType>& offset_2d) const
	{
		return _arr[offset_2d.y * _size_2d.x + offset_2d.x];
	}



};

// This utility class is intended to be used when inherently 2D data is
// stored within a 1D array.
template<typename Type>
class Array2dHelper
{
protected:		// variables
	Vec2<size_t> _size_2d;
	size_t _size = 0;

//public:			// variables
	Type* _arr = nullptr;

public:			// functions
	//Array2dHelper() : _size_2d({ 0, 0 }), _size(0), _arr(0)
	//{
	//}
	inline Array2dHelper()
	{
	}
	inline Array2dHelper(Type* s_arr, 
		const Vec2<size_t>& s_size_2d)
		: _size_2d(s_size_2d), _size(s_size_2d.x * s_size_2d.y),
		_arr(s_arr)
	{
	}
	inline Array2dHelper(const Array2dHelper& to_copy) = default;

	void init(Type* s_arr, const Vec2<size_t>& s_size_2d)
	{
		_size_2d = s_size_2d;
		_size = _size_2d.x * _size_2d.y;
		_arr = s_arr;
	}

	Array2dHelper& operator = (const Array2dHelper& to_copy) = default;


	Type* arr() const
	{
		return _arr;
	}

	size_t width() const
	{
		return _size_2d.x;
	}
	size_t height() const
	{
		return _size_2d.y;
	}

	const Vec2<size_t>& size_2d() const
	{
		return _size_2d;
	}
	size_t size() const
	{
		return _size;
	}

	Type& at(size_t x, size_t y)
	{
		return _arr[y * _size_2d.x + x];
	}
	template<typename PosType>
	Type& at(const Vec2<PosType>& offset_2d)
	{
		return _arr[offset_2d.y * _size_2d.x + offset_2d.x];
	}


	const Type& at(size_t x, size_t y) const
	{
		return _arr[y * _size_2d.x + x];
	}
	template<typename PosType>
	const Type& at(const Vec2<PosType>& offset_2d) const
	{
		return _arr[offset_2d.y * _size_2d.x + offset_2d.x];
	}



};


} // namespace containers


} // namespace liborangepower



#endif		// liborangepower_containers_array_2d_helper_classes_hpp
