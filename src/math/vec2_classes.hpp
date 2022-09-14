#ifndef liborangepower_math_vec2_classes_hpp
#define liborangepower_math_vec2_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_output_classes.hpp"
#include "../gen_class_innards_defines.hpp"
#include "../concepts/is_specialization_concepts.hpp"
#include "../concepts/math_concepts.hpp"
#include "../containers/std_hash_stuff.hpp"
#include "misc_funcs.hpp"

#include <cmath>
#include <cstdint>
#include <concepts>

namespace liborangepower
{
namespace math
{

template<typename T>
concept HasElemT = requires
{
	{ std::declval<typename T::ElemT>() };
};

//template<typename Vec2T, typename OtherVec2T>
//concept LikeVec2
//	= HasElemT<Vec2T>
//	&& requires(OtherVec2T other)
//{
//	{ other.x } -> std::convertible_to<typename Vec2T::ElemT>;
//	{ other.y } -> std::convertible_to<typename Vec2T::ElemT>;
//};

template<typename T>
class Vec2
{
public:		// types
	using ElemT = T;

	class CtorArgs final
	{
	public:		// variables
		T
			x,
			y;
	};
public:		// variables
	#define MEMB_LIST_VEC2(X) \
		X(x, std::nullopt) \
		X(y, std::nullopt) \

	T
		x = T(),
		y = T();
public:		// functions
	//--------
	constexpr inline Vec2() = default;
	constexpr inline Vec2(const T& s_x, const T& s_y)
		: x(s_x), y(s_y)
	{
	}
	constexpr inline Vec2(T&& s_x, T&& s_y)
		: x(std::move(s_x)), y(std::move(s_y))
	{
	}
	constexpr inline Vec2(const CtorArgs& ctor_args)
		: x(ctor_args.x), y(ctor_args.y)
	{
	}
	constexpr inline Vec2(CtorArgs&& ctor_args)
		: x(std::move(ctor_args.x)), y(std::move(ctor_args.y))
	{
	}

	constexpr inline Vec2(const Vec2&) = default;
	constexpr inline Vec2(Vec2&&) = default;

	constexpr inline Vec2& operator = (const Vec2&) = default;
	constexpr inline Vec2& operator = (Vec2&&) = default;
	//--------
	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec2 operator + (const Vec2<OtherElemT>& other) const
	{
		//return Vec2<T>({.x=x + other.x, .y=y + other.y});
		Vec2<T> ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec2& operator += (const Vec2<OtherElemT>& other)
		const
	{
		*this = *this + other;
		return *this;
	}

	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec2 operator - (const Vec2<OtherElemT>& other) const
	{
		//return Vec2<T>({.x=x - other.x, .y=y - other.y});
		Vec2<T> ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec2& operator -= (const Vec2<OtherElemT>& other)
		const
	{
		*this = *this - other;
		return *this;
	}

	constexpr inline Vec2 operator - () const
	{
		//return Vec2<T>({.x=-x, .y=-y});
		Vec2<T> ret;
		ret.x = -x;
		ret.y = -y;
		return ret;
	}

	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec2 operator * (const OtherElemT& scale) const
	{
		//return Vec2<T>({.x=x * scale, .y=y * scale});
		Vec2<T> ret;
		ret.x = x * scale;
		ret.y = y * scale;
		return ret;
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec2& operator *= (const OtherElemT& other) const
	{
		*this = *this * other;
		return *this;
	}

	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec2 operator / (const OtherElemT& scale) const
	{
		//return Vec2<T>({.x=x / scale, .y=y / scale});
		Vec2<T> ret;
		ret.x = x / scale;
		ret.y = y / scale;
		return ret;
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec2& operator /= (const OtherElemT& scale) const
	{
		*this = *this / scale;
		return *this;
	}

	constexpr inline Vec2 div_2() const
	{
		return Vec2({.x=math::div_2(x), .y=math::div_2(y)});
	}
	//--------
	// Dot product
	template<std::convertible_to<T> OtherElemT>
	constexpr inline T dot(const Vec2<OtherElemT>& other) const
	{
		//return T((x * other.x) + (y * other.y));
		const T ret = (x * other ) + (y * other.y);
		return ret;
	}

	// Z component of a 3D cross product, which is computed as if *this and
	// to_zcross have been converted to 3D vectors with Z components of zero
	template<std::convertible_to<T> OtherElemT>
	constexpr inline T zcross(const Vec2<OtherElemT>& other) const
	{
		//return T((x * other.y) - (y * other.x));
		const T ret = (x * other.y) - (y * other.x);
		return ret;
	}

	inline T norm() const
	{
		return std::sqrt(dot(*this));
	}
	//--------
	// Templates can't be defaulted for some reason
	//template<std::convertible_to<T> OtherElemT>
	//inline auto operator <=> (const Vec2<OtherElemT>& other) const
	//	= default;
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator == (const Vec2<OtherElemT>& other) const
	{
		return (x == other.x) && (y == other.y);
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator != (const Vec2<OtherElemT>& other) const
	{
		return !(*this == other);
	}

	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator < (const Vec2<OtherElemT>& other) const
	{
		return ((y < other.y) || ((y == other.y) && (x < other.x)));
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator > (const Vec2<OtherElemT>& other) const
	{
		return ((y > other.y) || ((y == other.y) && (x > other.x)));
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator <= (const Vec2<OtherElemT>& other) const
	{
		return !(*this > other);
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator >= (const Vec2<OtherElemT>& other) const
	{
		return !(*this < other);
	}
	//--------
};

template<typename T, std::convertible_to<T> OtherElemT>
constexpr inline Vec2<T> operator * (const OtherElemT& scale,
	const Vec2<T>& self)
{
	//return Vec2<T>({.x=scale * self.x, .y=scale * self.y});
	Vec2<T> ret;
	ret.x = scale * self.x;
	ret.y = scale * self.y;
	return ret;
	//return self * scale;
}
template<typename T, std::convertible_to<T> OtherElemT>
constexpr inline Vec2<T> operator / (const OtherElemT& inv_scale,
	const Vec2<T>& self)
{
	//return Vec2<T>({.x=inv_scale / self.x, .y=inv_scale / self.y});
	Vec2<T> ret;
	ret.x = inv_scale / self.x;
	ret.y = inv_scale / self.y;
	return ret;
}

template<typename T, typename CharT, typename Traits>
inline BasOstm<CharT, Traits>& operator << (BasOstm<CharT, Traits>& os,
	const Vec2<T>& arg)
{
	return misc_output::osprintout
	(
		os,
		"{",
			arg.x, ", ",
			arg.y,
		"}"
	);
}

//template<typename T>
//extern uint32_t _is_vec2_func(const Vec2<T>&);
//template<typename T>
//extern uint8_t _is_vec2_func(const T&);
//
//template<typename T>
//constexpr inline bool is_vec2()
//{
//	return (sizeof(_is_vec2_func(std::declval<T>()))
//		== sizeof(uint32_t));
//}
//template<typename T>
//constexpr inline bool is_vec2()
//{
//	return misc_util::is_specialization<T, Vec2>();
//}

//GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTYPES(is_vec2, Vec2);
//template<typename T>
//constexpr inline bool is_vec2()
//{
//	GEN_IS_SPECIALIZATION_FUNC_CONTENTS(is_vec2);
//}
template<typename T>
constexpr inline bool is_vec2()
{
	return concepts::is_specialization<T, Vec2>();
}

} // namespace containers
} // namespace liborangepower

namespace std
{
template<typename T>
struct hash<liborangepower::math::Vec2<T>>
{
	std::size_t operator ()
		(const liborangepower::math::Vec2<T>& vec2) const noexcept
		{
			return liborangepower::containers::hash_va(vec2.x, vec2.y);
		}
};
} // namespace std

#endif		// liborangepower_math_vec2_classes_hpp
