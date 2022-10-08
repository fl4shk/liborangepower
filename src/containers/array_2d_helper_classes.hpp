#ifndef liborangepower_containers_array_2d_helper_classes_hpp
#define liborangepower_containers_array_2d_helper_classes_hpp

#include "../misc/misc_types.hpp"
#include "../math/vec2_classes.hpp"
#include <concepts>

namespace liborangepower {
namespace containers {
//--------
// This utility class is intended to be used when inherently 2D data, with
// CONSTANT dimensions, is stored within a 1D array.
template<typename T, size_t _width, size_t _height>
class ArrayCsz2dHelper {
public:		// types
	using ElemT = T;
protected:		// variables
	static constexpr math::Vec2<size_t>
		_size_2d = {_width, _height};
	static constexpr size_t
		_size = _size_2d.x * _size_2d.y;

//public:			// variables
	T* _arr = nullptr;

public:			// functions
	inline ArrayCsz2dHelper() {
	}
	inline ArrayCsz2dHelper(T* s_arr)
		: _arr(s_arr) {
	}
	inline ArrayCsz2dHelper(const ArrayCsz2dHelper& to_copy) = default;

	constexpr inline void init(T* s_arr) {
		_arr = s_arr;
	}

	ArrayCsz2dHelper& operator = (const ArrayCsz2dHelper& to_copy) 
		= default;


	constexpr inline T* arr() const {
		return _arr;
	}

	constexpr inline size_t width() const {
		return _size_2d.x;
	}
	constexpr inline size_t height() const {
		return _size_2d.y;
	}

	constexpr inline const math::Vec2<size_t>& size_2d() const {
		return _size_2d;
	}
	constexpr inline size_t size() const {
		return _size;
	}

	T& at(size_t x, size_t y) {
		return _arr[y * _size_2d.x + x];
	}
	template<std::integral PosT>
	T& at(const math::Vec2<PosT>& offset_2d) {
		return _arr[offset_2d.y * _size_2d.x + offset_2d.x];
	}


	const T& at(size_t x, size_t y) const {
		return _arr[y * _size_2d.x + x];
	}
	template<std::integral PosT>
	const T& at(const math::Vec2<PosT>& offset_2d) const {
		return _arr[offset_2d.y * _size_2d.x + offset_2d.x];
	}
};
//--------
// This utility class is intended to be used when inherently 2D data is
// stored within a 1D array.
template<typename T>
class Array2dHelper {
public:		// types
	using ElemT = T;
protected:		// variables
	math::Vec2<size_t> _size_2d;
	size_t _size = 0;

//public:			// variables
	T* _arr = nullptr;

public:			// functions
	//Array2dHelper() : _size_2d({ 0, 0 }), _size(0), _arr(0) {
	//}
	inline Array2dHelper() {
	}
	inline Array2dHelper(
		T* s_arr, 
		const math::Vec2<size_t>& s_size_2d
	)
		: _size_2d(s_size_2d), _size(s_size_2d.x * s_size_2d.y),
		_arr(s_arr) {
	}
	inline Array2dHelper(const Array2dHelper& to_copy) = default;

	void init(T* s_arr, const math::Vec2<size_t>& s_size_2d) {
		_size_2d = s_size_2d;
		_size = _size_2d.x * _size_2d.y;
		_arr = s_arr;
	}

	Array2dHelper& operator = (const Array2dHelper& to_copy) = default;


	T* arr() const {
		return _arr;
	}

	size_t width() const {
		return _size_2d.x;
	}
	size_t height() const {
		return _size_2d.y;
	}

	const math::Vec2<size_t>& size_2d() const {
		return _size_2d;
	}
	size_t size() const {
		return _size;
	}

	T& at(size_t x, size_t y) {
		return _arr[y * _size_2d.x + x];
	}
	template<std::integral PosT>
	T& at(const math::Vec2<PosT>& offset_2d) {
		return _arr[offset_2d.y * _size_2d.x + offset_2d.x];
	}


	const T& at(size_t x, size_t y) const {
		return _arr[y * _size_2d.x + x];
	}
	template<std::integral PosT>
	const T& at(const math::Vec2<PosT>& offset_2d) const {
		return _arr[offset_2d.y * _size_2d.x + offset_2d.x];
	}
};
//--------
} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_array_2d_helper_classes_hpp
