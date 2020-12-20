#ifndef liborangepower_misc_byte_vec_accessors_hpp
#define liborangepower_misc_byte_vec_accessors_hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"

namespace liborangepower
{

namespace misc_util
{

using namespace integer_types;

inline std::string get_string(const std::vector<u8>& byte_vec,
	size_t index, size_t len)
{
	std::string ret;

	for (size_t i=index; i<(index + len); ++i)
	{
		ret += static_cast<char>(byte_vec.at(i));
	}
	return ret;
}
inline void set_string(std::vector<u8>& byte_vec, size_t index,
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
inline void push_back_string(std::vector<u8>& byte_vec,
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

inline u16 get_u16_le(const std::vector<u8>& byte_vec, size_t index)
{
	const u16 ret 
		= ((static_cast<u16>(byte_vec.at(index + 1))
			<< static_cast<u16>(8))
		| (static_cast<u16>(byte_vec.at(index + 0))
			<< static_cast<u16>(0)));
	return ret;
}
inline void set_u16_le(std::vector<u8>& byte_vec, size_t index, u16 n_val)
{
	byte_vec.at(index + 1) = ((static_cast<u16>(n_val)
		>> static_cast<u16>(8)) & 0xff);
	byte_vec.at(index + 0) = ((static_cast<u16>(n_val)
		>> static_cast<u16>(0)) & 0xff);
}
inline void push_back_u16_le(std::vector<u8>& byte_vec, u16 n_val)
{
	const auto old_size = byte_vec.size(); 
	for (size_t i=0; i<sizeof(n_val); ++i)
	{
		byte_vec.push_back(0x00);
	}
	set_u16_le(byte_vec, old_size, n_val);
}

inline i16 get_i16_le(const std::vector<u8>& byte_vec, size_t index)
{
	const i16 ret 
		= ((static_cast<i16>(byte_vec.at(index + 1))
			<< static_cast<i16>(8))
		| (static_cast<i16>(byte_vec.at(index + 0))
			<< static_cast<i16>(0)));
	return ret;
}
inline void set_i16_le(std::vector<u8>& byte_vec, size_t index, i16 n_val)
{
	byte_vec.at(index + 1) = ((static_cast<i16>(n_val)
		>> static_cast<i16>(8)) & 0xff);
	byte_vec.at(index + 0) = ((static_cast<i16>(n_val)
		>> static_cast<i16>(0)) & 0xff);
}
inline void push_back_i16_le(std::vector<u8>& byte_vec, i16 n_val)
{
	const auto old_size = byte_vec.size(); 
	for (size_t i=0; i<sizeof(n_val); ++i)
	{
		byte_vec.push_back(0x00);
	}
	set_i16_le(byte_vec, old_size, n_val);
}

inline u32 get_u32_le(const std::vector<u8>& byte_vec, size_t index)
{
	const u32 ret 
		= ((static_cast<u32>(byte_vec.at(index + 3))
			<< static_cast<u32>(24))
		| (static_cast<u32>(byte_vec.at(index + 2))
			<< static_cast<u32>(16))
		| (static_cast<u32>(byte_vec.at(index + 1))
			<< static_cast<u32>(8))
		| (static_cast<u32>(byte_vec.at(index + 0))
			<< static_cast<u32>(0)));
	return ret;
}
inline void set_u32_le(std::vector<u8>& byte_vec, size_t index, u32 n_val)
{
	byte_vec.at(index + 3) = ((static_cast<u32>(n_val)
		>> static_cast<u32>(24)) & 0xff);
	byte_vec.at(index + 2) = ((static_cast<u32>(n_val)
		>> static_cast<u32>(16)) & 0xff);
	byte_vec.at(index + 1) = ((static_cast<u32>(n_val)
		>> static_cast<u32>(8)) & 0xff);
	byte_vec.at(index + 0) = ((static_cast<u32>(n_val)
		>> static_cast<u32>(0)) & 0xff);
}
inline void push_back_u32_le(std::vector<u8>& byte_vec, u32 n_val)
{
	const auto old_size = byte_vec.size(); 
	for (size_t i=0; i<sizeof(n_val); ++i)
	{
		byte_vec.push_back(0x00);
	}
	set_u32_le(byte_vec, old_size, n_val);
}

inline i32 get_i32_le(const std::vector<u8>& byte_vec, size_t index)
{
	const i32 ret 
		= ((static_cast<i32>(byte_vec.at(index + 3))
			<< static_cast<i32>(24))
		| (static_cast<i32>(byte_vec.at(index + 2))
			<< static_cast<i32>(16))
		| (static_cast<i32>(byte_vec.at(index + 1))
			<< static_cast<i32>(8))
		| (static_cast<i32>(byte_vec.at(index + 0))
			<< static_cast<i32>(0)));
	return ret;
}
inline void set_i32_le(std::vector<u8>& byte_vec, size_t index, i32 n_val)
{
	byte_vec.at(index + 3) = ((static_cast<i32>(n_val)
		>> static_cast<i32>(24)) & 0xff);
	byte_vec.at(index + 2) = ((static_cast<i32>(n_val)
		>> static_cast<i32>(16)) & 0xff);
	byte_vec.at(index + 1) = ((static_cast<i32>(n_val)
		>> static_cast<i32>(8)) & 0xff);
	byte_vec.at(index + 0) = ((static_cast<i32>(n_val)
		>> static_cast<i32>(0)) & 0xff);
}
inline void push_back_i32_le(std::vector<u8>& byte_vec, i32 n_val)
{
	const auto old_size = byte_vec.size(); 
	for (size_t i=0; i<sizeof(n_val); ++i)
	{
		byte_vec.push_back(0x00);
	}
	set_i32_le(byte_vec, old_size, n_val);
}


inline u64 get_u64_le(const std::vector<u8>& byte_vec, size_t index)
{
	const u64 ret 
		= ((static_cast<u64>(byte_vec.at(index + 7))
			<< static_cast<u64>(56))
		| (static_cast<u64>(byte_vec.at(index + 6))
			<< static_cast<u64>(48))
		| (static_cast<u64>(byte_vec.at(index + 5))
			<< static_cast<u64>(40))
		| (static_cast<u64>(byte_vec.at(index + 4))
			<< static_cast<u64>(32))
		| (static_cast<u64>(byte_vec.at(index + 3))
			<< static_cast<u64>(24))
		| (static_cast<u64>(byte_vec.at(index + 2))
			<< static_cast<u64>(16))
		| (static_cast<u64>(byte_vec.at(index + 1))
			<< static_cast<u64>(8))
		| (static_cast<u64>(byte_vec.at(index + 0))
			<< static_cast<u64>(0)));
	return ret;
}
inline void set_u64_le(std::vector<u8>& byte_vec, size_t index, u64 n_val)
{
	byte_vec.at(index + 7) = ((static_cast<u64>(n_val)
		>> static_cast<u64>(56)) & 0xff);
	byte_vec.at(index + 6) = ((static_cast<u64>(n_val)
		>> static_cast<u64>(48)) & 0xff);
	byte_vec.at(index + 5) = ((static_cast<u64>(n_val)
		>> static_cast<u64>(40)) & 0xff);
	byte_vec.at(index + 4) = ((static_cast<u64>(n_val)
		>> static_cast<u64>(32)) & 0xff);
	byte_vec.at(index + 3) = ((static_cast<u64>(n_val)
		>> static_cast<u64>(24)) & 0xff);
	byte_vec.at(index + 2) = ((static_cast<u64>(n_val)
		>> static_cast<u64>(16)) & 0xff);
	byte_vec.at(index + 1) = ((static_cast<u64>(n_val)
		>> static_cast<u64>(8)) & 0xff);
	byte_vec.at(index + 0) = ((static_cast<u64>(n_val)
		>> static_cast<u64>(0)) & 0xff);
}
inline void push_back_u64_le(std::vector<u8>& byte_vec, u64 n_val)
{
	const auto old_size = byte_vec.size(); 
	for (size_t i=0; i<sizeof(n_val); ++i)
	{
		byte_vec.push_back(0x00);
	}
	set_u64_le(byte_vec, old_size, n_val);
}


inline i64 get_i64_le(const std::vector<u8>& byte_vec, size_t index)
{
	const i64 ret 
		= ((static_cast<i64>(byte_vec.at(index + 7))
			<< static_cast<i64>(56))
		| (static_cast<i64>(byte_vec.at(index + 6))
			<< static_cast<i64>(48))
		| (static_cast<i64>(byte_vec.at(index + 5))
			<< static_cast<i64>(40))
		| (static_cast<i64>(byte_vec.at(index + 4))
			<< static_cast<i64>(32))
		| (static_cast<i64>(byte_vec.at(index + 3))
			<< static_cast<i64>(24))
		| (static_cast<i64>(byte_vec.at(index + 2))
			<< static_cast<i64>(16))
		| (static_cast<i64>(byte_vec.at(index + 1))
			<< static_cast<i64>(8))
		| (static_cast<i64>(byte_vec.at(index + 0))
			<< static_cast<i64>(0)));
	return ret;
}
inline void set_i64_le(std::vector<u8>& byte_vec, size_t index, i64 n_val)
{
	byte_vec.at(index + 7) = ((static_cast<i64>(n_val)
		>> static_cast<i64>(56)) & 0xff);
	byte_vec.at(index + 6) = ((static_cast<i64>(n_val)
		>> static_cast<i64>(48)) & 0xff);
	byte_vec.at(index + 5) = ((static_cast<i64>(n_val)
		>> static_cast<i64>(40)) & 0xff);
	byte_vec.at(index + 4) = ((static_cast<i64>(n_val)
		>> static_cast<i64>(32)) & 0xff);
	byte_vec.at(index + 3) = ((static_cast<i64>(n_val)
		>> static_cast<i64>(24)) & 0xff);
	byte_vec.at(index + 2) = ((static_cast<i64>(n_val)
		>> static_cast<i64>(16)) & 0xff);
	byte_vec.at(index + 1) = ((static_cast<i64>(n_val)
		>> static_cast<i64>(8)) & 0xff);
	byte_vec.at(index + 0) = ((static_cast<i64>(n_val)
		>> static_cast<i64>(0)) & 0xff);
}
inline void push_back_i64_le(std::vector<u8>& byte_vec, i64 n_val)
{
	size_t i;
	for (i=0; i<sizeof(n_val); ++i)
	{
		byte_vec.push_back(0x00);
	}
	set_i64_le(byte_vec, i, n_val);
}

} // namespace misc_util

} // namespace liborangepower

#endif		// liborangepower_misc_accessors_hpp
