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

template<typename Vec3T, typename OtherVec3T>
concept LikeVec3 
	= HasElemT<Vec3T> 
	&& requires(OtherVec3T other)
{
	{ other.x } -> std::convertible_to<typename Vec3T::ElemT>;
	{ other.y } -> std::convertible_to<typename Vec3T::ElemT>;
	{ other.z } -> std::convertible_to<typename Vec3T::ElemT>;
};

template<typename T>
class Vec3
{
public:		// types
	using ElemT = T;

	class CtorArgs final
	{
	public:		// variables
		ElemT x, y, z;
	};
public:		// variables
	T x, y, z;
public:		// functions
	//--------
	inline Vec3() = default;
	inline Vec3(const T& s_x, const T& s_y, const T& s_z)
		: x(s_x), y(s_y), z(s_z)
	{
	}
	inline Vec3(T&& s_x, T&& s_y, T&& s_z)
		: x(std::move(s_x)), y(std::move(s_y)), z(std::move(s_z))
	{
	}
	inline Vec3(const CtorArgs& ctor_args)
		: x(ctor_args.x), y(ctor_args.y), z(ctor_args.z)
	{
	}
	inline Vec3(CtorArgs&& ctor_args)
		: x(std::move(ctor_args.x)),
		y(std::move(ctor_args.y)),
		z(std::move(ctor_args.z))
	{
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Vec3);
	virtual inline ~Vec3() = default;
	//--------
	template<typename OtherVec3T>
		requires LikeVec3<Vec3<T>, OtherVec3T>
	inline Vec3 operator + (const OtherVec3T& other) const
	{
		return Vec3<T>(x + other.x, y + other.y, z + other.z);
	}
	template<typename OtherVec3T>
		requires LikeVec3<Vec3<T>, OtherVec3T>
	inline Vec3& operator += (const OtherVec3T& other) const
	{
		*this = (*this) + other;
		return *this;
	}

	template<typename OtherVec3T>
		requires LikeVec3<Vec3<T>, OtherVec3T>
	inline Vec3 operator - (const OtherVec3T& other) const
	{
		return Vec3<T>(x - other.x, y - other.y, z - other.z);
	}
	template<typename OtherVec3T>
		requires LikeVec3<Vec3<T>, OtherVec3T>
	inline Vec3& operator -= (const OtherVec3T& other) const
	{
		*this = (*this) - other;
		return *this;
	}

	inline Vec3 operator - () const
	{
		return Vec3(-x, -y, -z);
	}

	template<std::convertible_to<T> OtherT>
	inline Vec3 operator * (const OtherT& scale) const
	{
		return Vec3(x * scale, y * scale, z * scale);
	}
	template<std::convertible_to<T> OtherT>
	inline Vec3& operator *= (const OtherT& other) const
	{
		*this = (*this) * other;
		return *this;
	}

	template<std::convertible_to<T> OtherT>
	inline Vec3 operator / (const OtherT& scale) const
	{
		return Vec3<T>(x / scale, y / scale, z / scale);
	}
	template<std::convertible_to<T> OtherT>
	inline Vec3& operator /= (const OtherT& scale) const
	{
		*this = (*this) / scale;
		return *this;
	}
	//--------
	// Dot product
	template<typename OtherVec3T>
		requires LikeVec3<Vec3<T>, OtherVec3T>
	inline T dot_prod(const OtherVec3T& other) const
	{
		return ((x * other.x) + (y * other.y) + (z * other.z));
	}

	// Cross product
	template<typename OtherVec3T>
		requires LikeVec3<Vec3<T>, OtherVec3T>
	inline Vec3 cross_prod(const OtherVec3T& other) const
	{
		return Vec3<T>((y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x));
	}

	inline T norm() const
	{
		return std::sqrt(dot_prod(*this));
	}
	//--------
	// Templates can't be defaulted for some reason
	//template<typename OtherVec3T>
	//	requires LikeVec3<Vec3<T>, OtherVec3T>
	//inline auto operator <=> (const OtherVec3T& other) const
	//	= default;
	template<typename OtherVec3T>
		requires LikeVec3<Vec3<T>, OtherVec3T>
	inline bool operator == (const OtherVec3T& other) const
	{
		return ((x == other.x) && (y == other.y) && (z == other.z));
	}
	template<typename OtherVec3T>
		requires LikeVec3<Vec3<T>, OtherVec3T>
	inline bool operator != (const OtherVec3T& other) const
	{
		return (!((*this) == other));
	}

	template<typename OtherVec3T>
		requires LikeVec3<Vec3<T>, OtherVec3T>
	inline bool operator < (const OtherVec3T& other) const
	{
		return ((z < other.z)
			|| ((z == other.z) && (Vec2(x, y) < Vec2(other.x, other.y))));
	}
	template<typename OtherVec3T>
		requires LikeVec3<Vec3<T>, OtherVec3T>
	inline bool operator > (const OtherVec3T& other) const
	{
		return ((z > other.z)
			|| ((z == other.z) && (Vec2(x, y) > Vec2(other.x, other.y))));
	}
	template<typename OtherVec3T>
		requires LikeVec3<Vec3<T>, OtherVec3T>
	inline bool operator <= (const OtherVec3T& other) const
	{
		return (!((*this) > other));
	}
	template<typename OtherVec3T>
		requires LikeVec3<Vec3<T>, OtherVec3T>
	inline bool operator >= (const OtherVec3T& other) const
	{
		return (!((*this) < other));
	}
	//--------
};

//template<typename T>
//extern uint32_t _is_vec3_func(const Vec3<T>&);
//template<typename T>
//extern uint8_t _is_vec3_func(const T&);
//
//template<typename T>
//constexpr inline bool is_vec3()
//{
//	return (sizeof(_is_vec3_func(std::declval<T>()))
//		== sizeof(uint32_t));
//}
//template<typename T>
//constexpr inline bool is_vec3()
//{
//	return misc_util::is_specialization<T, Vec3>();
//}

template<typename T>
constexpr inline bool is_vec3()
{
	return concepts::is_specialization<T, Vec3>();
}
} // namespace containers
} // namespace liborangepower

namespace std
{

template<typename T>
struct hash<liborangepower::containers::Vec3<T>>
{
	std::size_t operator ()
		(const liborangepower::containers::Vec3<T>& vec3) const noexcept
	{
		//const std::size_t& hx = std::hash<T>{}(vec3.x);
		//const std::size_t& hy = std::hash<T>{}(vec3.y);
		//const std::size_t& hz = std::hash<T>{}(vec3.z);

		//return ((hx 
		//	^ (hy << std::size_t(1)))
		//	^ (hz << std::size_t(1)));
		return liborangepower::containers::hash_va(vec3.x, vec3.y, vec3.z);
	}
};

} // namespace std
#endif		// liborangepower_containers_vec3_classes_hpp

