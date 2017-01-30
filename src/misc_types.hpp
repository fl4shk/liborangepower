// This file is part of Lib Orange Power.
// 
// Copyright (C) 2017 Andrew Clark (FL4SHK)
// 
// Lib Orange Power is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Lib Orange Power is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
// General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with Lib Orange Power.  If not, see
// <http://www.gnu.org/licenses/>.


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
