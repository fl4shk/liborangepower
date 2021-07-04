#ifndef liborangepower_containers_vec3_classes_hpp
#define liborangepower_containers_vec3_classes_hpp

#include "../gen_class_innards_defines.hpp"
#include "vec2_classes.hpp"

namespace liborangepower
{

namespace containers
{

template<typename Type>
class Vec3
{
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
	template<typename OtherType>
	inline Vec3 operator + (const Vec3<OtherType>& other) const
	{
		return Vec3<Type>(x + other.x, y + other.y, z + other.z);
	}
	template<typename OtherType>
	inline Vec3& operator += (const Vec3<OtherType>& other) const
	{
		*this = (*this) + other;
		return *this;
	}

	template<typename OtherType>
	inline Vec3 operator - (const Vec3<OtherType>& other) const
	{
		return Vec3<Type>(x - other.x, y - other.y, z - other.z);
	}
	template<typename OtherType>
	inline Vec3& operator -= (const Vec3<OtherType>& other) const
	{
		*this = (*this) - other;
		return *this;
	}

	inline Vec3 operator - () const
	{
		return Vec3(-x, -y, -z);
	}

	template<typename OtherType>
	inline Vec3 operator * (const OtherType& scale) const
	{
		return Vec3(x * scale, y * scale, z * scale);
	}
	template<typename OtherType>
	inline Vec3& operator *= (const OtherType& other) const
	{
		*this = (*this) * other;
		return *this;
	}

	template<typename OtherType>
	inline Vec3 operator / (const OtherType& scale) const
	{
		return Vec3<Type>(x / scale, y / scale, z / scale);
	}
	template<typename OtherType>
	inline Vec3& operator /= (const OtherType& scale) const
	{
		*this = (*this) / scale;
		return *this;
	}
	//--------
	// Dot product
	template<typename OtherType>
	inline Type dot_prod(const Vec3<OtherType>& other) const
	{
		return ((x * other.x) + (y * other.y) + (z * other.z));
	}

	// Cross product
	template<typename OtherType>
	inline Vec3 cross_prod(const Vec3<OtherType>& other) const
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
	template<typename OtherType>
	inline bool operator == (const Vec3<OtherType>& other) const
	{
		return ((x == other.x) && (y == other.y) && (z == other.z));
	}
	template<typename OtherType>
	inline bool operator != (const Vec3<OtherType>& other) const
	{
		return (!((*this) == other));
	}

	template<typename OtherType>
	inline bool operator < (const Vec3<OtherType>& other) const
	{
		return ((z < other.z)
			|| ((z == other.z) && (Vec2(x, y) < Vec2(other.x, other.y))));
	}
	template<typename OtherType>
	inline bool operator > (const Vec3<OtherType>& other) const
	{
		return ((z > other.z)
			|| ((z == other.z) && (Vec2(x, y) > Vec2(other.x, other.y))));
	}
	template<typename OtherType>
	inline bool operator <= (const Vec3<OtherType>& other) const
	{
		return (!((*this) > other));
	}
	template<typename OtherType>
	inline bool operator >= (const Vec3<OtherType>& other) const
	{
		return (!((*this) < other));
	}
	//--------
};

} // namespace containers

} // namespace liborangepower
#endif		// liborangepower_containers_vec3_classes_hpp

