#ifndef liborangepower_misc_misc_types_hpp
#define liborangepower_misc_misc_types_hpp

#include <cstdint>

namespace liborangepower
{

namespace integer_types
{

typedef uint8_t u8;
typedef int8_t i8;

typedef uint16_t u16;
typedef int16_t i16;

typedef uint32_t u32;
typedef int32_t i32;

typedef uint64_t u64;
typedef int64_t i64;

typedef unsigned int uint;

inline u16 byte_vec_get_u16_le(const std::vector<u8>& byte_vec,
	size_t index)
{
	const u16 ret = ((byte_vec.at(index + 1) << 8) 
		| byte_vec.at(index + 0));
	return ret;
}
inline void byte_vec_set_u16_le(std::vector<u8>& byte_vec, size_t index,
	u16 n_val)
{
	byte_vec.at(index + 0) = ((n_val >> 0) & 0xff);
	byte_vec.at(index + 1) = ((n_val >> 8) & 0xff);
}
inline void byte_vec_push_back_u16_le(std::vector<u8>& byte_vec,
	size_t index, u16 n_val)
{
	for (size_t i=0; i<sizeof(n_val); ++i)
	{
		byte_vec.push_back(0x00);
	}
	byte_vec_set_u16_le(byte_vec, index, n_val);
}

inline i16 byte_vec_get_i16_le(const std::vector<u8>& byte_vec,
	size_t index)
{
	const i16 ret = ((byte_vec.at(index + 1) << 8) 
		| byte_vec.at(index + 0));
	return ret;
}
inline void byte_vec_set_i16_le(std::vector<u8>& byte_vec, size_t index,
	i16 n_val)
{
	byte_vec.at(index + 0) = ((n_val >> 0) & 0xff);
	byte_vec.at(index + 1) = ((n_val >> 8) & 0xff);
}
inline void byte_vec_push_back_i16_le(std::vector<u8>& byte_vec,
	size_t index, i16 n_val)
{
	for (size_t i=0; i<sizeof(n_val); ++i)
	{
		byte_vec.push_back(0x00);
	}
	byte_vec_set_i16_le(byte_vec, index, n_val);
}

inline u32 byte_vec_get_u32_le(const std::vector<u8>& byte_vec,
	size_t index)
{
	const u32 ret = ((byte_vec.at(index + 3) << 24)
		| (byte_vec.at(index + 2) << 16)
		| (byte_vec.at(index + 1) << 8) 
		| byte_vec.at(index + 0));
	return ret;
}
inline void byte_vec_set_u32_le(std::vector<u8>& byte_vec, size_t index,
	u32 n_val)
{
	byte_vec.at(index + 0) = ((n_val >> 0) & 0xff);
	byte_vec.at(index + 1) = ((n_val >> 8) & 0xff);
	byte_vec.at(index + 2) = ((n_val >> 16) & 0xff);
	byte_vec.at(index + 3) = ((n_val >> 24) & 0xff);
}
inline void byte_vec_push_back_u32_le(std::vector<u8>& byte_vec,
	size_t index, u32 n_val)
{
	for (size_t i=0; i<sizeof(n_val); ++i)
	{
		byte_vec.push_back(0x00);
	}
	byte_vec_set_u32_le(byte_vec, index, n_val);
}

inline i32 byte_vec_get_i32_le(const std::vector<u8>& byte_vec,
	size_t index)
{
	const i32 ret = ((byte_vec.at(index + 3) << 24)
		| (byte_vec.at(index + 2) << 16)
		| (byte_vec.at(index + 1) << 8) 
		| byte_vec.at(index + 0));
	return ret;
}
inline void byte_vec_set_i32_le(std::vector<u8>& byte_vec, size_t index,
	i32 n_val)
{
	byte_vec.at(index + 0) = ((n_val >> 0) & 0xff);
	byte_vec.at(index + 1) = ((n_val >> 8) & 0xff);
	byte_vec.at(index + 2) = ((n_val >> 16) & 0xff);
	byte_vec.at(index + 3) = ((n_val >> 24) & 0xff);
}
inline void byte_vec_push_back_i32_le(std::vector<u8>& byte_vec,
	size_t index, i32 n_val)
{
	for (size_t i=0; i<sizeof(n_val); ++i)
	{
		byte_vec.push_back(0x00);
	}
	byte_vec_set_i32_le(byte_vec, index, n_val);
}


inline u64 byte_vec_get_u64_le(const std::vector<u8>& byte_vec,
	size_t index)
{
	const u64 ret = ((byte_vec.at(index + 7) << 56)
		| (byte_vec.at(index + 6) << 48)
		| (byte_vec.at(index + 5) << 40)
		| (byte_vec.at(index + 4) << 32)
		| (byte_vec.at(index + 3) << 24)
		| (byte_vec.at(index + 2) << 16)
		| (byte_vec.at(index + 1) << 8) 
		| byte_vec.at(index + 0));
	return ret;
}
inline void byte_vec_set_u64_le(std::vector<u8>& byte_vec, size_t index,
	u64 n_val)
{
	byte_vec.at(index + 0) = ((n_val >> 0) & 0xff);
	byte_vec.at(index + 1) = ((n_val >> 8) & 0xff);
	byte_vec.at(index + 2) = ((n_val >> 16) & 0xff);
	byte_vec.at(index + 3) = ((n_val >> 24) & 0xff);
	byte_vec.at(index + 4) = ((n_val >> 32) & 0xff);
	byte_vec.at(index + 5) = ((n_val >> 40) & 0xff);
	byte_vec.at(index + 6) = ((n_val >> 48) & 0xff);
	byte_vec.at(index + 7) = ((n_val >> 56) & 0xff);
}
inline void byte_vec_push_back_u64_le(std::vector<u8>& byte_vec,
	size_t index, u64 n_val)
{
	for (size_t i=0; i<sizeof(n_val); ++i)
	{
		byte_vec.push_back(0x00);
	}
	byte_vec_set_u64_le(byte_vec, index, n_val);
}


inline i64 byte_vec_get_i64_le(const std::vector<u8>& byte_vec,
	size_t index)
{
	const i64 ret = ((byte_vec.at(index + 7) << 56)
		| (byte_vec.at(index + 6) << 48)
		| (byte_vec.at(index + 5) << 40)
		| (byte_vec.at(index + 4) << 32)
		| (byte_vec.at(index + 3) << 24)
		| (byte_vec.at(index + 2) << 16)
		| (byte_vec.at(index + 1) << 8) 
		| byte_vec.at(index + 0));
	return ret;
}
inline void byte_vec_set_i64_le(std::vector<u8>& byte_vec, size_t index,
	i64 n_val)
{
	byte_vec.at(index + 0) = ((n_val >> 0) & 0xff);
	byte_vec.at(index + 1) = ((n_val >> 8) & 0xff);
	byte_vec.at(index + 2) = ((n_val >> 16) & 0xff);
	byte_vec.at(index + 3) = ((n_val >> 24) & 0xff);
	byte_vec.at(index + 4) = ((n_val >> 32) & 0xff);
	byte_vec.at(index + 5) = ((n_val >> 40) & 0xff);
	byte_vec.at(index + 6) = ((n_val >> 48) & 0xff);
	byte_vec.at(index + 7) = ((n_val >> 56) & 0xff);
}
inline void byte_vec_push_back_i64_le(std::vector<u8>& byte_vec,
	size_t index, i64 n_val)
{
	for (size_t i=0; i<sizeof(n_val); ++i)
	{
		byte_vec.push_back(0x00);
	}
	byte_vec_set_i64_le(byte_vec, index, n_val);
}

} // namespace integer_types

} // namespace liborangepower


#endif		// liborangepower_misc_misc_types_hpp
