#ifndef liborangepower_memwhatever_wrappers_hpp
#define liborangepower_memwhatever_wrappers_hpp

#include <string.h>
#include <array>

#include "misc_includes.hpp"
#include "misc_types.hpp"


namespace liborangepower
{

template< typename type >
inline void* arr_memcpy( type* dst, const void* src, u32 num_elems )
{
	return memcpy( (void*)dst, src, num_elems * sizeof(type) / sizeof(u8) );
}
template< typename type >
inline void* arr_memset( type* dst, int c, u32 num_elems )
{
	return memset( (void*)dst, c, num_elems * sizeof(type) / sizeof(u8) );
}



template< typename dst_type, typename src_type, size_t size >
inline void* arr_memcpy( std::array< dst_type, size >& dst, 
	std::array< src_type, size >& src )
{
	return arr_memcpy<dst_type>( dst.data(), src.data(), size );
}
template< typename type, size_t size >
inline void* arr_memcpy( std::array< type, size >& dst, const void* src )
{
	return arr_memcpy<type>( dst.data(), src, size );
}
template< typename type, size_t size >
inline void* arr_memset( std::array< type, size >& dst, u32 src )
{
	return arr_memset<type>( dst.data(), src, size );
}

}



#endif		// liborangepower_memwhatever_wrappers_hpp
