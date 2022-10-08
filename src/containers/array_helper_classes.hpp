#ifndef liborangepower_containers_array_helper_classes_hpp
#define liborangepower_containers_array_helper_classes_hpp



#include "../misc/misc_types.hpp"
#include "../misc/misc_defines.hpp"

namespace liborangepower {
namespace containers {
//--------
template<typename T, size_t _size>
class ArrayCszHelper {
public:			// variables
	T* _arr = nullptr;
public:		// constants
	static constexpr size_t SIZE = _size;
public:			// functions
	ArrayCszHelper() {
	}
	ArrayCszHelper(T* s_the_array) : _arr(s_the_array) {
	}
	ArrayCszHelper(const ArrayCszHelper& to_copy) = default;
	void init(T* s_the_array) {
		_arr = s_the_array;
	}
	ArrayCszHelper& operator = (const ArrayCszHelper& to_copy) = default;

	const T* arr() const {
		return _arr;
	}
	size_t size() const {
		return SIZE;
	}

	T& at(size_t offset) {
		return _arr[offset];
	}
	const T& at(size_t offset) const {
		return _arr[offset];
	}
};
//--------
// This is a VERY thin wrapper class for working with 1D arrays of
// arbitrary sizes
template<typename T>
class ArrayHelper {
//public:			// variables
protected:		// variables
	T* _arr = nullptr;
protected:		// variables
	size_t _size = 0;
public:			// functions
	inline ArrayHelper() {
	}
	inline ArrayHelper(T* s_the_array, size_t s_size)
		: _arr(s_the_array), _size(s_size) {
	}
	inline ArrayHelper(const ArrayHelper& to_copy) = default;

	void init(T* s_the_array, size_t s_size) {
		_arr = s_the_array;
		_size = s_size;
	}
	inline ArrayHelper& operator = (const ArrayHelper& to_copy) = default;

	const T* arr() const {
		return _arr;
	}

	size_t size() const {
		return _size;
	}

	T& at(size_t offset) {
		return _arr[offset];
	}
	const T& at(size_t offset) const {
		return _arr[offset];
	}

};
//--------
} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_array_helper_classes_hpp
