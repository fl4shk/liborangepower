#ifndef liborangepower_containers_vec2_classes_hpp
#define liborangepower_containers_vec2_classes_hpp

#include "../gen_class_innards_defines.hpp"

#include <cmath>

namespace liborangepower
{

namespace containers
{

template<typename Type>
class Vec2
{
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
	template<typename OtherType>
	inline Vec2 operator + (const Vec2<OtherType>& other) const
	{
		return Vec2<Type>(x + other.x, y + other.y);
	}
	template<typename OtherType>
	inline Vec2& operator += (const Vec2<OtherType>& other) const
	{
		*this = (*this) + other;
		return *this;
	}

	template<typename OtherType>
	inline Vec2 operator - (const Vec2<OtherType>& other) const
	{
		return Vec2<Type>(x - other.x, y - other.y);
	}
	template<typename OtherType>
	inline Vec2& operator -= (const Vec2<OtherType>& other) const
	{
		*this = (*this) - other;
		return *this;
	}

	inline Vec2 operator - () const
	{
		return Vec2(-x, -y);
	}

	template<typename OtherType>
	inline Vec2 operator * (const OtherType& scale) const
	{
		return Vec2<Type>(x * scale, y * scale);
	}
	template<typename OtherType>
	inline Vec2& operator *= (const OtherType& other) const
	{
		*this = (*this) * other;
		return *this;
	}

	template<typename OtherType>
	inline Vec2 operator / (const OtherType& scale) const
	{
		return Vec2<Type>(x / scale, y / scale);
	}
	template<typename OtherType>
	inline Vec2& operator /= (const OtherType& scale) const
	{
		*this = (*this) / scale;
		return *this;
	}
	//--------
	// Dot product
	template<typename OtherType>
	inline Type dot_prod(const Vec2<OtherType>& other) const
	{
		return Type((x * other.x) + (y * other.y));
	}

	// Z component of a 3D cross product, which is computed as if *this and
	// to_zcross have been converted to 3D vectors with Z components of zero
	template<typename OtherType>
	inline Type zcross_prod(const Vec2<OtherType>& other) const
	{
		return Type((x * other.y) - (y * other.x));
	}

	inline Type norm() const
	{
		return std::sqrt(dot_prod(*this));
	}
	//--------
	template<typename OtherType>
	inline bool operator == (const Vec2<OtherType>& other) const
	{
		return ((x == other.x) && (y == other.y));
	}
	template<typename OtherType>
	inline bool operator != (const Vec2<OtherType>& other) const
	{
		return (!((*this) == other));
	}

	template<typename OtherType>
	inline bool operator < (const Vec2<OtherType>& other) const
	{
		return ((y < other.y) || ((y == other.y) && (x < other.x)));
	}
	template<typename OtherType>
	inline bool operator > (const Vec2<OtherType>& other) const
	{
		return ((y > other.y) || ((y == other.y) && (x > other.x)));
	}
	template<typename OtherType>
	inline bool operator <= (const Vec2<OtherType>& other) const
	{
		return (!((*this) > other));
	}
	template<typename OtherType>
	inline bool operator >= (const Vec2<OtherType>& other) const
	{
		return (!((*this) < other));
	}
	//--------
};

} // namespace containers

} // namespace liborangepower

#endif		// liborangepower_containers_vec2_classes_hpp
