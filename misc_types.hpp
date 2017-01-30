#ifndef misc_types_hpp
#define misc_types_hpp

#include <cstdint>

typedef uint8_t u8; typedef int8_t s8;
typedef uint16_t u16; typedef int16_t s16;
typedef uint32_t u32; typedef int32_t s32;
typedef uint64_t u64; typedef int64_t s64;
typedef unsigned int uint;


#define _align4 aligned(4)
#define alignas_regular alignas(4)

#define asm_comment( stuff ) \
	asm volatile( "@ ---" stuff " ---" )


#endif		// misc_types_hpp
