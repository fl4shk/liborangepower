#ifndef liborangepower_math_vec3_classes_hpp
#define liborangepower_math_vec3_classes_hpp

#include "../gen_class_innards_defines.hpp"
#include "../concepts/is_specialization_concepts.hpp"
#include "../concepts/math_concepts.hpp"
#include "vec2_classes.hpp"

#include <cstdint>
#include <concepts>

namespace liborangepower
{
namespace math
{

//template<typename Vec3T, typename OtherVec3T>
//concept LikeVec3
//	= HasElemT<Vec3T>
//	&& requires(OtherVec3T other)
//{
//	{ other.x } -> std::convertible_to<typename Vec3T::ElemT>;
//	{ other.y } -> std::convertible_to<typename Vec3T::ElemT>;
//	{ other.z } -> std::convertible_to<typename Vec3T::ElemT>;
//};

template<typename T>
class Vec3
{
public:		// types
	using ElemT = T;
public:		// variables
	#define MEMB_LIST_VEC3(X) \
		X(x, std::nullopt) \
		X(y, std::nullopt) \
		X(z, std::nullopt) \

	T
		x = T(),
		y = T(),
		z = T();
public:		// functions
	//--------
	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec3 operator + (const Vec3<OtherElemT>& other) const
	{
		//return Vec3<T>(x + other.x, y + other.y, z + other.z);
		return Vec3
		(
			x + other.x,
			y + other.y,
			z + other.z
		);
		//Vec3<T> ret;
		//ret.x = x + other.x;
		//ret.y = y + other.y;
		//ret.z = z + other.z;
		//return ret;
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec3& operator += (const Vec3<OtherElemT>& other)
		const
	{
		*this = *this + other;
		return *this;
	}

	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec3 operator - (const Vec3<OtherElemT>& other) const
	{
		//return Vec3<T>(x - other.x, y - other.y, z - other.z);
		return Vec3
		(
			x - other.x,
			y - other.y,
			z - other.z
		);
		//Vec3<T> ret;
		//ret.x = x - other.x;
		//ret.y = y - other.y;
		//ret.z = z - other.z;
		//return ret;
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec3& operator -= (const Vec3<OtherElemT>& other)
		const
	{
		*this = *this - other;
		return *this;
	}

	constexpr inline Vec3 operator - () const
	{
		//return Vec3<T>({.x=-x, .y=-y, .z=-z});
		return Vec3
		(
			-x,
			-y,
			-z
		);
		//Vec3<T> ret;
		//ret.x = -x;
		//ret.y = -y;
		//ret.z = -z;
		//return ret;
	}

	template<std::convertible_to<T> OtherT>
	constexpr inline Vec3 operator * (const OtherT& scale) const
	{
		//return Vec3<T>({.x=x * scale, .y=y * scale, .z=z * scale});
		return Vec3
		(
			x * scale,
			y * scale,
			z * scale
		);
		//Vec3<T> ret;
		//ret.x = x * scale;
		//ret.y = y * scale;
		//ret.z = z * scale;
		//return ret;
	}
	template<std::convertible_to<T> OtherT>
	constexpr inline Vec3& operator *= (const OtherT& other) const
	{
		*this = *this * other;
		return *this;
	}

	template<std::convertible_to<T> OtherT>
	constexpr inline Vec3 operator / (const OtherT& scale) const
	{
		return Vec3
		(
			x / scale,
			y / scale,
			z / scale
		);
		//Vec3<T> ret;
		//ret.x = x / scale;
		//ret.y = y / scale;
		//ret.z = z / scale;
		//return ret;
	}
	template<std::convertible_to<T> OtherT>
	constexpr inline Vec3& operator /= (const OtherT& scale) const
	{
		*this = *this / scale;
		return *this;
	}

	constexpr inline Vec3 div_2() const
	{
		//return Vec3
		//({
		//	.x=math::div_2(x),
		//	.y=math::div_2(y),
		//	.z=math::div_2(z),
		//});
		return Vec3
		(
			math::div_2(x),
			math::div_2(y),
			math::div_2(z)
		);
	}
	constexpr inline Vec3 recip() const
	{
		//return Vec3
		//({
		//	.x=math::recip(x),
		//	.y=math::recip(y),
		//	.z=math::recip(z),
		//});
		return Vec3
		(
			math::recip(x),
			math::recip(y),
			math::recip(z)
		);
	}
	//--------
	// Dot product
	template<std::convertible_to<T> OtherElemT>
	constexpr inline T dot(const Vec3<OtherElemT>& other) const
	{
		//return ((x * other.x) + (y * other.y) + (z * other.z));
		const T ret = (x * other.x) + (y * other.y) + (z * other.z);
		return ret;
	}

	// Cross product
	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec3 cross(const Vec3<OtherElemT>& other) const
	{
		//return Vec3<T>
		//({
		//	.x=(y * other.z) - (z * other.y),
		//	.y=(z * other.x) - (x * other.z),
		//	.z=(x * other.y) - (y * other.x)
		//});
		return Vec3<T>
		(
			(y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x)
		);
		//Vec3<T> ret;
		//ret.x = (y * other.z) - (z * other.y);
		//ret.y = (z * other.x) - (x * other.z);
		//ret.z = (x * other.y) - (y * other.x);
		//return ret;
	}

	constexpr inline T magnitude() const
	{
		//return std::sqrt(dot(*this));
		return math::cstm_sqrt(dot(*this));
	}
	constexpr inline Vec3<T> norm() const
	{
		return *this / magnitude();
	}
	//--------
	// Templates can't be defaulted for some reason
	//template<std::convertible_to<T> OtherElemT>
	//inline auto operator <=> (const Vec3<OtherElemT>& other) const
	//	= default;
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator == (const Vec3<OtherElemT>& other) const
	{
		return (x == other.x && y == other.y && z == other.z);
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator != (const Vec3<OtherElemT>& other) const
	{
		return !(*this == other);
	}

	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator < (const Vec3<OtherElemT>& other) const
	{
		return z < other.z
			|| (z == other.z && Vec2(x, y) < Vec2(other.x, other.y));
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator > (const Vec3<OtherElemT>& other) const
	{
		return z > other.z
			|| (z == other.z && Vec2(x, y) > Vec2(other.x, other.y));
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator <= (const Vec3<OtherElemT>& other) const
	{
		return !(*this > other);
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator >= (const Vec3<OtherElemT>& other) const
	{
		return !(*this < other);
	}
	//--------
};
template<typename T, std::convertible_to<T> OtherElemT>
constexpr inline Vec3<T> operator * (const OtherElemT& scale,
	const Vec3<T>& self)
{
	//return Vec3<T>
	//({
	//	.x=scale * self.x,
	//	.y=scale * self.y,
	//	.z=scale * self.z
	//});
	return Vec3<T>
	(
		scale * self.x,
		scale * self.y,
		scale * self.z
	);
	//Vec3<T> ret;
	//ret.x = scale * self.x;
	//ret.y = scale * self.y;
	//ret.z = scale * self.z;
	//return ret;
	//return self * scale;
}
template<typename T, std::convertible_to<T> OtherElemT>
constexpr inline Vec3<T> operator / (const OtherElemT& inv_scale,
	const Vec3<T>& self)
{
	//return Vec3<T>
	//({
	//	.x=inv_scale / self.x,
	//	.y=inv_scale / self.y,
	//	.z=inv_scale / self.z,
	//});
	return Vec3<T>
	(
		inv_scale / self.x,
		inv_scale / self.y,
		inv_scale / self.z
	);

	//Vec3<T> ret;
	//ret.x = inv_scale / self.x;
	//ret.y = inv_scale / self.y;
	//ret.z = inv_scale / self.z;
	//return ret;
}
template<typename T>
constexpr inline std::ostream& operator << (std::ostream& os,
	const Vec3<T>& arg)
{
	return misc_output::osprintout
	(
		os,
		"{",
			//arg.x, ", ",
			//arg.y, ", ",
			//arg.z,

			#define X(memb, dummy_arg) \
				strings::sconcat( arg . memb ),

			strings::strjoin2
			(
				std::string(", "),
				std::vector<std::string>
				({
					MEMB_LIST_VEC3(X)
				})
				//std::make_tuple
				//(
				//	sconcat(arg.x),
				//	sconcat(arg.y),
				//	sconcat(arg.z)
				//)
			),

			#undef X
		"}"
	);
}

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
} // namespace math
} // namespace liborangepower

namespace std
{
//--------
template<typename T>
struct hash<liborangepower::math::Vec3<T>>
{
	std::size_t operator ()
		(const liborangepower::math::Vec3<T>& vec3) const noexcept
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
//--------
} // namespace std
#endif		// liborangepower_math_vec3_classes_hpp
