#ifndef liborangepower_containers_vec2_classes_hpp
#define liborangepower_containers_vec2_classes_hpp

#include "../gen_class_innards_defines.hpp"
#include "../concepts/is_specialization_concepts.hpp"

#include <cmath>
#include <cstdint>
#include <concepts>

namespace liborangepower
{
namespace containers
{
template<typename Type>
concept HasElemType = requires
{
	{ std::declval<typename Type::ElemType>() };
};

template<typename Vec2Type, typename OtherVec2Type>
concept LikeVec2 
	= HasElemType<Vec2Type> 
	&& requires(OtherVec2Type other)
{
	{ other.x } -> std::convertible_to<typename Vec2Type::ElemType>;
	{ other.y } -> std::convertible_to<typename Vec2Type::ElemType>;
};

template<typename Type>
class Vec2
{
public:		// types
	using ElemType = Type;
public:		// variables
	Type x, y;
public:		// functions
	//--------
	inline Vec2() = default;
	inline Vec2(const Type& s_x, const Type& s_y)
		: x(s_x), y(s_y)
	{
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Vec2);
	virtual ~Vec2() = default;
	//--------
	template<typename OtherVec2Type>
		requires LikeVec2<Vec2<Type>, OtherVec2Type>
	inline Vec2 operator + (const OtherVec2Type& other) const
	{
		return Vec2<Type>(x + other.x, y + other.y);
	}
	template<typename OtherVec2Type>
		requires LikeVec2<Vec2<Type>, OtherVec2Type>
	inline Vec2& operator += (const OtherVec2Type& other) const
	{
		*this = (*this) + other;
		return *this;
	}

	template<typename OtherVec2Type>
		requires LikeVec2<Vec2<Type>, OtherVec2Type>
	inline Vec2 operator - (const OtherVec2Type& other) const
	{
		return Vec2<Type>(x - other.x, y - other.y);
	}
	template<typename OtherVec2Type>
		requires LikeVec2<Vec2<Type>, OtherVec2Type>
	inline Vec2& operator -= (const OtherVec2Type& other) const
	{
		*this = (*this) - other;
		return *this;
	}

	inline Vec2 operator - () const
	{
		return Vec2(-x, -y);
	}

	template<std::convertible_to<Type> OtherType>
	inline Vec2 operator * (const OtherType& scale) const
	{
		return Vec2<Type>(x * scale, y * scale);
	}
	template<std::convertible_to<Type> OtherType>
	inline Vec2& operator *= (const OtherType& other) const
	{
		*this = (*this) * other;
		return *this;
	}

	template<std::convertible_to<Type> OtherType>
	inline Vec2 operator / (const OtherType& scale) const
	{
		return Vec2<Type>(x / scale, y / scale);
	}
	template<std::convertible_to<Type> OtherType>
	inline Vec2& operator /= (const OtherType& scale) const
	{
		*this = (*this) / scale;
		return *this;
	}
	//--------
	// Dot product
	template<typename OtherVec2Type>
		requires LikeVec2<Vec2<Type>, OtherVec2Type>
	inline Type dot_prod(const OtherVec2Type& other) const
	{
		return Type((x * other.x) + (y * other.y));
	}

	// Z component of a 3D cross product, which is computed as if *this and
	// to_zcross have been converted to 3D vectors with Z components of zero
	template<typename OtherVec2Type>
		requires LikeVec2<Vec2<Type>, OtherVec2Type>
	inline Type zcross_prod(const OtherVec2Type& other) const
	{
		return Type((x * other.y) - (y * other.x));
	}

	inline Type norm() const
	{
		return std::sqrt(dot_prod(*this));
	}
	//--------
	// Templates can't be defaulted for some reason
	//template<typename OtherVec2Type>
	//	requires LikeVec2<Vec2<Type>, OtherVec2Type>
	//inline auto operator <=> (const OtherVec2Type& other) const
	//	= default;
	template<typename OtherVec2Type>
		requires LikeVec2<Vec2<Type>, OtherVec2Type>
	inline bool operator == (const OtherVec2Type& other) const
	{
		return ((x == other.x) && (y == other.y));
	}
	template<typename OtherVec2Type>
		requires LikeVec2<Vec2<Type>, OtherVec2Type>
	inline bool operator != (const OtherVec2Type& other) const
	{
		return (!((*this) == other));
	}

	template<typename OtherVec2Type>
		requires LikeVec2<Vec2<Type>, OtherVec2Type>
	inline bool operator < (const OtherVec2Type& other) const
	{
		return ((y < other.y) || ((y == other.y) && (x < other.x)));
	}
	template<typename OtherVec2Type>
		requires LikeVec2<Vec2<Type>, OtherVec2Type>
	inline bool operator > (const OtherVec2Type& other) const
	{
		return ((y > other.y) || ((y == other.y) && (x > other.x)));
	}
	template<typename OtherVec2Type>
		requires LikeVec2<Vec2<Type>, OtherVec2Type>
	inline bool operator <= (const OtherVec2Type& other) const
	{
		return (!((*this) > other));
	}
	template<typename OtherVec2Type>
		requires LikeVec2<Vec2<Type>, OtherVec2Type>
	inline bool operator >= (const OtherVec2Type& other) const
	{
		return (!((*this) < other));
	}
	//--------
};

//template<typename Type>
//extern uint32_t _is_vec2_func(const Vec2<Type>&);
//template<typename Type>
//extern uint8_t _is_vec2_func(const Type&);
//
//template<typename Type>
//constexpr inline bool is_vec2()
//{
//	return (sizeof(_is_vec2_func(std::declval<Type>()))
//		== sizeof(uint32_t));
//}
//template<typename Type>
//constexpr inline bool is_vec2()
//{
//	return misc_util::is_specialization<Type, Vec2>();
//}
GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTYPES(is_vec2, Vec2);
template<typename Type>
constexpr inline bool is_vec2()
{
	GEN_IS_SPECIALIZATION_FUNC_CONTENTS(is_vec2);
}

} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_vec2_classes_hpp
