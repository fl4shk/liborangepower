#ifndef liborangepower_containers_vec3_classes_hpp
#define liborangepower_containers_vec3_classes_hpp

#include "../gen_class_innards_defines.hpp"
#include "../concepts/is_specialization_concepts.hpp"
#include "vec2_classes.hpp"

#include <cstdint>
#include <concepts>

namespace liborangepower
{
namespace containers
{

template<typename Vec3Type, typename OtherVec3Type>
concept LikeVec3 
	= HasElemType<Vec3Type> 
	&& requires(OtherVec3Type other)
{
	{ other.x } -> std::convertible_to<typename Vec3Type::ElemType>;
	{ other.y } -> std::convertible_to<typename Vec3Type::ElemType>;
	{ other.z } -> std::convertible_to<typename Vec3Type::ElemType>;
};

template<typename Type>
class Vec3
{
public:		// types
	using ElemType = Type;
public:		// variables
	Type x, y, z;
public:		// functions
	//--------
	inline Vec3() = default;
	inline Vec3(const Type& s_x, const Type& s_y, const Type& s_z)
		: x(s_x), y(s_y), z(s_z)
	{
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Vec3);
	virtual inline ~Vec3() = default;
	//--------
	template<typename OtherVec3Type>
		requires LikeVec3<Vec3<Type>, OtherVec3Type>
	inline Vec3 operator + (const OtherVec3Type& other) const
	{
		return Vec3<Type>(x + other.x, y + other.y, z + other.z);
	}
	template<typename OtherVec3Type>
		requires LikeVec3<Vec3<Type>, OtherVec3Type>
	inline Vec3& operator += (const OtherVec3Type& other) const
	{
		*this = (*this) + other;
		return *this;
	}

	template<typename OtherVec3Type>
		requires LikeVec3<Vec3<Type>, OtherVec3Type>
	inline Vec3 operator - (const OtherVec3Type& other) const
	{
		return Vec3<Type>(x - other.x, y - other.y, z - other.z);
	}
	template<typename OtherVec3Type>
		requires LikeVec3<Vec3<Type>, OtherVec3Type>
	inline Vec3& operator -= (const OtherVec3Type& other) const
	{
		*this = (*this) - other;
		return *this;
	}

	inline Vec3 operator - () const
	{
		return Vec3(-x, -y, -z);
	}

	template<std::convertible_to<Type> OtherType>
	inline Vec3 operator * (const OtherType& scale) const
	{
		return Vec3(x * scale, y * scale, z * scale);
	}
	template<std::convertible_to<Type> OtherType>
	inline Vec3& operator *= (const OtherType& other) const
	{
		*this = (*this) * other;
		return *this;
	}

	template<std::convertible_to<Type> OtherType>
	inline Vec3 operator / (const OtherType& scale) const
	{
		return Vec3<Type>(x / scale, y / scale, z / scale);
	}
	template<std::convertible_to<Type> OtherType>
	inline Vec3& operator /= (const OtherType& scale) const
	{
		*this = (*this) / scale;
		return *this;
	}
	//--------
	// Dot product
	template<typename OtherVec3Type>
		requires LikeVec3<Vec3<Type>, OtherVec3Type>
	inline Type dot_prod(const OtherVec3Type& other) const
	{
		return ((x * other.x) + (y * other.y) + (z * other.z));
	}

	// Cross product
	template<typename OtherVec3Type>
		requires LikeVec3<Vec3<Type>, OtherVec3Type>
	inline Vec3 cross_prod(const OtherVec3Type& other) const
	{
		return Vec3<Type>((y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x));
	}

	inline Type norm() const
	{
		return std::sqrt(dot_prod(*this));
	}
	//--------
	// Templates can't be defaulted for some reason
	//template<typename OtherVec3Type>
	//	requires LikeVec3<Vec3<Type>, OtherVec3Type>
	//inline auto operator <=> (const OtherVec3Type& other) const
	//	= default;
	template<typename OtherVec3Type>
		requires LikeVec3<Vec3<Type>, OtherVec3Type>
	inline bool operator == (const OtherVec3Type& other) const
	{
		return ((x == other.x) && (y == other.y) && (z == other.z));
	}
	template<typename OtherVec3Type>
		requires LikeVec3<Vec3<Type>, OtherVec3Type>
	inline bool operator != (const OtherVec3Type& other) const
	{
		return (!((*this) == other));
	}

	template<typename OtherVec3Type>
		requires LikeVec3<Vec3<Type>, OtherVec3Type>
	inline bool operator < (const OtherVec3Type& other) const
	{
		return ((z < other.z)
			|| ((z == other.z) && (Vec2(x, y) < Vec2(other.x, other.y))));
	}
	template<typename OtherVec3Type>
		requires LikeVec3<Vec3<Type>, OtherVec3Type>
	inline bool operator > (const OtherVec3Type& other) const
	{
		return ((z > other.z)
			|| ((z == other.z) && (Vec2(x, y) > Vec2(other.x, other.y))));
	}
	template<typename OtherVec3Type>
		requires LikeVec3<Vec3<Type>, OtherVec3Type>
	inline bool operator <= (const OtherVec3Type& other) const
	{
		return (!((*this) > other));
	}
	template<typename OtherVec3Type>
		requires LikeVec3<Vec3<Type>, OtherVec3Type>
	inline bool operator >= (const OtherVec3Type& other) const
	{
		return (!((*this) < other));
	}
	//--------
};

//template<typename Type>
//extern uint32_t _is_vec3_func(const Vec3<Type>&);
//template<typename Type>
//extern uint8_t _is_vec3_func(const Type&);
//
//template<typename Type>
//constexpr inline bool is_vec3()
//{
//	return (sizeof(_is_vec3_func(std::declval<Type>()))
//		== sizeof(uint32_t));
//}
//template<typename Type>
//constexpr inline bool is_vec3()
//{
//	return misc_util::is_specialization<Type, Vec3>();
//}

GEN_IS_SPECIALIZATION_CHECK_FUNCS(is_vec3, Vec3);
template<typename Type>
constexpr inline bool is_vec3()
{
	GEN_IS_SPECIALIZATION_FUNC_CONTENTS(is_vec3);
}
} // namespace containers
} // namespace liborangepower
#endif		// liborangepower_containers_vec3_classes_hpp

