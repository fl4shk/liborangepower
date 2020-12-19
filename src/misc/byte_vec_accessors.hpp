#ifndef liborangepower_misc_byte_vec_accessors_hpp
#define liborangepower_misc_byte_vec_accessors_hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"

namespace liborangepower
{

namespace misc_util
{

inline std::string byte_vec_get_string(const std::vector<u8>& byte_vec,
	size_t index, size_t len)
{
	std::string ret;

	for (size_t i=index; i<(index + len); ++i)
	{
		ret += static_cast<char>(byte_vec.at(i));
	}
	return ret;
}
inline void byte_vec_set_string(std::vector<u8>& byte_vec, size_t index,
	const std::string& n_val, bool null_term)
{
	size_t i = 0;
	for (i=0; i<n_val.size(); ++i)
	{
		byte_vec.at(index + i) = static_cast<u8>(n_val.at(i));
	}
	if (null_term)
	{
		byte_vec.at(i) = '\0';
	}
}
inline void byte_vec_push_back_string(std::vector<u8>& byte_vec,
	const std::string& n_val, bool null_term)
{
	for (const auto& item: n_val)
	{
		byte_vec.push_back(static_cast<u8>(item));
	}
	if (null_term)
	{
		byte_vec.push_back('\0');
	}
}

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
inline void byte_vec_push_back_u16_le(std::vector<u8>& byte_vec, u16 n_val)
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
inline void byte_vec_push_back_i16_le(std::vector<u8>& byte_vec, i16 n_val)
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
inline void byte_vec_push_back_u32_le(std::vector<u8>& byte_vec, u32 n_val)
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
inline void byte_vec_push_back_i32_le(std::vector<u8>& byte_vec, i32 n_val)
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
inline void byte_vec_push_back_u64_le(std::vector<u8>& byte_vec, u64 n_val)
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
inline void byte_vec_push_back_i64_le(std::vector<u8>& byte_vec, i64 n_val)
{
	for (size_t i=0; i<sizeof(n_val); ++i)
	{
		byte_vec.push_back(0x00);
	}
	byte_vec_set_i64_le(byte_vec, index, n_val);
}

} // namespace misc_util

} // namespace liborangepower

#endif		// liborangepower_misc_byte_vec_accessors_hpp
