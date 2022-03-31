#ifndef liborangepower_misc_memwhatever_wrappers_hpp
#define liborangepower_misc_memwhatever_wrappers_hpp

#include <cstring>
#include <array>
#include <vector>
#include <deque>

#include "misc_includes.hpp"
#include "misc_types.hpp"


namespace liborangepower
{

namespace misc_util
{

template<typename T>
inline void* arr_memcpy(T* dst, const void* src, size_t num_elems)
{
	return std::memcpy((void*)dst, src, num_elems * sizeof(T) 
		/ sizeof(integer_types::u8));
}
template<typename T>
inline void* arr_memset(T* dst, int c, size_t num_elems)
{
	return std::memset((void*)dst, c, num_elems * sizeof(T) 
		/ sizeof(integer_types::u8));
}

template<typename DstT, typename SrcT, size_t size>
inline void* arr_memcpy(std::array<DstT, size>& dst, 
	const std::array<SrcT, size>& src)
{
	return arr_memcpy<DstT>(dst.data(), src.data(), size);
}
template<typename T, size_t size>
inline void* arr_memcpy(std::array<T, size>& dst, const void* src)
{
	return arr_memcpy<T>(dst.data(), src, size);
}
template<typename T, size_t size>
inline void* arr_memset(std::array<T, size>& dst, size_t src)
{
	return arr_memset<T>(dst.data(), src, size);
}

} // namespace misc_util

} // namespace liborangepower


#endif		// liborangepower_misc_memwhatever_wrappers_hpp
