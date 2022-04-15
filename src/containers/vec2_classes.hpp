#ifndef liborangepower_containers_vec2_classes_hpp
#define liborangepower_containers_vec2_classes_hpp

#include "../gen_class_innards_defines.hpp"
#include "../concepts/is_specialization_concepts.hpp"
#include "std_hash_stuff.hpp"

#include <cmath>
#include <cstdint>
#include <concepts>

namespace liborangepower
{
namespace containers
{

template<typename T>
concept HasElemT = requires
{
	{ std::declval<typename T::ElemT>() };
};

template<typename Vec2T, typename OtherVec2T>
concept LikeVec2 
	= HasElemT<Vec2T> 
	&& requires(OtherVec2T other)
{
	{ other.x } -> std::convertible_to<typename Vec2T::ElemT>;
	{ other.y } -> std::convertible_to<typename Vec2T::ElemT>;
};

template<typename T>
class Vec2
{
public:		// types
	using ElemT = T;

	class CtorArgs final
	{
	public:		// variables
		ElemT x, y;
	};
public:		// variables
	T x, y;
public:		// functions
	//--------
	inline Vec2() = default;
	inline Vec2(const T& s_x, const T& s_y)
		: x(s_x), y(s_y)
	{
	}
	inline Vec2(T&& s_x, T&& s_y)
		: x(std::move(s_x)), y(std::move(s_y))
	{
	}
	inline Vec2(const CtorArgs& ctor_args)
		: x(ctor_args.x), y(ctor_args.y)
	{
	}
	inline Vec2(CtorArgs&& ctor_args)
		: x(std::move(ctor_args.x)), y(std::move(ctor_args.y))
	{
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Vec2);
	virtual ~Vec2() = default;
	//--------
	template<typename OtherVec2T>
		requires LikeVec2<Vec2<T>, OtherVec2T>
	inline Vec2 operator + (const OtherVec2T& other) const
	{
		return Vec2<T>(x + other.x, y + other.y);
	}
	template<typename OtherVec2T>
		requires LikeVec2<Vec2<T>, OtherVec2T>
	inline Vec2& operator += (const OtherVec2T& other) const
	{
		*this = (*this) + other;
		return *this;
	}

	template<typename OtherVec2T>
		requires LikeVec2<Vec2<T>, OtherVec2T>
	inline Vec2 operator - (const OtherVec2T& other) const
	{
		return Vec2<T>(x - other.x, y - other.y);
	}
	template<typename OtherVec2T>
		requires LikeVec2<Vec2<T>, OtherVec2T>
	inline Vec2& operator -= (const OtherVec2T& other) const
	{
		*this = (*this) - other;
		return *this;
	}

	inline Vec2 operator - () const
	{
		return Vec2(-x, -y);
	}

	template<std::convertible_to<T> OtherT>
	inline Vec2 operator * (const OtherT& scale) const
	{
		return Vec2<T>(x * scale, y * scale);
	}
	template<std::convertible_to<T> OtherT>
	inline Vec2& operator *= (const OtherT& other) const
	{
		*this = (*this) * other;
		return *this;
	}

	template<std::convertible_to<T> OtherT>
	inline Vec2 operator / (const OtherT& scale) const
	{
		return Vec2<T>(x / scale, y / scale);
	}
	template<std::convertible_to<T> OtherT>
	inline Vec2& operator /= (const OtherT& scale) const
	{
		*this = (*this) / scale;
		return *this;
	}
	//--------
	// Dot product
	template<typename OtherVec2T>
		requires LikeVec2<Vec2<T>, OtherVec2T>
	inline T dot_prod(const OtherVec2T& other) const
	{
		return T((x * other.x) + (y * other.y));
	}

	// Z component of a 3D cross product, which is computed as if *this and
	// to_zcross have been converted to 3D vectors with Z components of zero
	template<typename OtherVec2T>
		requires LikeVec2<Vec2<T>, OtherVec2T>
	inline T zcross_prod(const OtherVec2T& other) const
	{
		return T((x * other.y) - (y * other.x));
	}

	inline T norm() const
	{
		return std::sqrt(dot_prod(*this));
	}
	//--------
	// Templates can't be defaulted for some reason
	//template<typename OtherVec2T>
	//	requires LikeVec2<Vec2<T>, OtherVec2T>
	//inline auto operator <=> (const OtherVec2T& other) const
	//	= default;
	template<typename OtherVec2T>
		requires LikeVec2<Vec2<T>, OtherVec2T>
	inline bool operator == (const OtherVec2T& other) const
	{
		return ((x == other.x) && (y == other.y));
	}
	template<typename OtherVec2T>
		requires LikeVec2<Vec2<T>, OtherVec2T>
	inline bool operator != (const OtherVec2T& other) const
	{
		return (!((*this) == other));
	}

	template<typename OtherVec2T>
		requires LikeVec2<Vec2<T>, OtherVec2T>
	inline bool operator < (const OtherVec2T& other) const
	{
		return ((y < other.y) || ((y == other.y) && (x < other.x)));
	}
	template<typename OtherVec2T>
		requires LikeVec2<Vec2<T>, OtherVec2T>
	inline bool operator > (const OtherVec2T& other) const
	{
		return ((y > other.y) || ((y == other.y) && (x > other.x)));
	}
	template<typename OtherVec2T>
		requires LikeVec2<Vec2<T>, OtherVec2T>
	inline bool operator <= (const OtherVec2T& other) const
	{
		return (!((*this) > other));
	}
	template<typename OtherVec2T>
		requires LikeVec2<Vec2<T>, OtherVec2T>
	inline bool operator >= (const OtherVec2T& other) const
	{
		return (!((*this) < other));
	}
	//--------
};

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
struct hash<liborangepower::containers::Vec2<T>>
{
	std::size_t operator ()
		(const liborangepower::containers::Vec2<T>& vec2) const noexcept
		{
			return liborangepower::containers::hash_va(vec2.x, vec2.y);
		}
};
} // namespace std

#endif		// liborangepower_containers_vec2_classes_hpp
