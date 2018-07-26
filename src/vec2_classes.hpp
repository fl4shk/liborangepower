#ifndef liborangepower_vec2_classes_hpp
#define liborangepower_vec2_classes_hpp

#include "misc_types.hpp"
#include "misc_defines.hpp"
#include "misc_utility_funcs.hpp"

#include <utility>

namespace liborangepower
{

namespace containers
{

static constexpr size_t vec2_index_for_x = 0, vec2_index_for_y = 1;

template<typename Type>
class Vec2
{
//public:		// constants
//	static constexpr size_t the_index_for_x = 0, the_index_for_y = 1;
//	
public:		// variables
	Type x, y;

public:		// functions
	constexpr inline Vec2() : x(Type()), y(Type())
	{
	}

	//inline Vec2(const Type& s_x, const Type& s_y) : x(s_x), y(s_y)
	//{
	//}
	//
	//inline Vec2(const Vec2<Type>& to_copy) : x(to_copy.x), y(to_copy.y)
	//{
	//}



	template<typename Type1, typename Type2>
	constexpr inline Vec2(const Type1& s_x, const Type2& s_y)
		: x(s_x), y(s_y)
	{
	}
	template<typename OtherType>
	constexpr inline Vec2(const Vec2<OtherType>& to_copy)
		: x(to_copy.x), y(to_copy.y)
	{
	}
	template<typename OtherType>
	constexpr inline Vec2(Vec2<OtherType>&& to_move)
		: x(std::move(to_move.x)), y(std::move(to_move.y))
	{
	}


	template<typename OtherType>
	inline Vec2& operator = (const Vec2<OtherType>& to_copy)
	{
		x = to_copy.x;
		y = to_copy.y;

		return *this;
	}
	template<typename OtherType>
	inline Vec2& operator = (Vec2<OtherType>&& to_move)
	{
		x = std::move(to_move.x);
		y = std::move(to_move.y);

		return *this;
	}


	template<typename OtherType>
	inline Vec2 operator + (const Vec2<OtherType>& to_add) const
	{
		return Vec2(x + to_add.x, y + to_add.y);
	}
	template<typename OtherType>
	inline Vec2 operator - (const Vec2<OtherType>& to_sub) const
	{
		return Vec2(x - to_sub.x, y - to_sub.y);
	}

	template<typename OtherType>
	inline Vec2 operator * (const OtherType& scale) const
	{
		return Vec2(x * scale, y * scale);
	}

	// Dot product
	template<typename OtherType>
	inline Type dot_prod(const Vec2<OtherType>& to_dot) const
	{
		return (x * to_dot.x) + (y * to_dot.y);
	}

	// Z component of a 3D cross product, which is computed as if *this and
	// to_zcross have been converted to 3D vectors with Z components of zero
	template<typename OtherType>
	inline Type zcross_prod(const Vec2<OtherType>& to_zcross) const
	{
		return (x * to_zcross.y) - (y * to_zcross.x);
	}


	template<typename OtherType>
	inline Vec2& operator += (const Vec2<OtherType>& to_add)
	{
		x += to_add.x;
		y += to_add.y;
		return *this;
	}
	template<typename OtherType>
	inline Vec2& operator -= (const Vec2<OtherType>& to_sub)
	{
		x -= to_sub.x;
		y -= to_sub.y;
		return *this;
	}

	template<typename OtherType>
	inline Vec2& operator *= (const OtherType& scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}


	// Comparison Operator Overloads
	template<typename OtherType>
	inline bool operator == (const Vec2<OtherType>& to_cmp) const
	{
		return ((x == to_cmp.x) && (y == to_cmp.y));
	}

	template<typename OtherType>
	inline bool operator != (const Vec2<OtherType>& to_cmp) const
	{
		return ((x != to_cmp.x) || (y != to_cmp.y));
	}


	template<typename OtherType>
	inline operator Vec2<OtherType>() const
	{
		return Vec2<OtherType>(x, y);
	}

	inline Type& operator [] (size_t index)
	{
		if (index == vec2_index_for_x)
		{
			return x;
		}
		else //if (index != vec2_index_for_x)
		{
			return y;
		}
	}

	inline const Type& operator [] (size_t index) const
	{
		if (index == vec2_index_for_x)
		{
			return x;
		}
		else //if (index != vec2_index_for_x)
		{
			return y;
		}
	}

};




template<typename Type>
inline Vec2<Type> operator * (const Type& scale, 
	const Vec2<Type>& vec2_to_mul)
{
	return vec2_to_mul * scale;
}


typedef Vec2<integer_types::u16> Vec2U16;
typedef Vec2<integer_types::s16> Vec2S16;
typedef Vec2<integer_types::u32> Vec2U32;
typedef Vec2<integer_types::s32> Vec2S32;
typedef Vec2<integer_types::u64> Vec2U64;
typedef Vec2<integer_types::s64> Vec2S64;
typedef Vec2<size_t> SizeT2d;


#define generate_specific_vec2_class_contents(specific_type) \
public:		/* variables */ \
	specific_type x, y; \
	\
public:		/* functions */ \
	constexpr inline Vec2() : x(specific_type()), y(specific_type()) \
	{ \
	} \
	\
	constexpr inline Vec2(const specific_type& s_x, \
		const specific_type& s_y) : x(s_x), y(s_y) \
	{ \
	} \
	constexpr inline Vec2(const Vec2& to_copy) \
		: x(to_copy.x), y(to_copy.y) \
	{ \
	} \
	constexpr inline Vec2(Vec2&& to_move) \
		: x(std::move(to_move.x)), y(std::move(to_move.y)) \
	{ \
	} \
	\
	inline Vec2& operator = \
		(const Vec2& to_copy) \
	{ \
		x = to_copy.x; \
		y = to_copy.y; \
		\
		return *this; \
	} \
	inline Vec2& operator = \
		(Vec2&& to_move) \
	{ \
		x = std::move(to_move.x); \
		y = std::move(to_move.y); \
		\
		return *this; \
	} \
	\
	template<typename OtherType> \
	inline Vec2 operator + \
		(const Vec2<OtherType>& to_add) const \
	{ \
		return Vec2 (x + to_add.x, y + to_add.y); \
	} \
	template<typename OtherType> \
	inline Vec2 operator - \
		(const Vec2<OtherType>& to_sub) const \
	{ \
		return Vec2 (x - to_sub.x, y - to_sub.y); \
	} \
	\
	template<typename OtherType> \
	inline Vec2 operator * (const OtherType& scale) \
		const \
	{ \
		return Vec2 (x * scale, y * scale); \
	} \
	\
	/* Dot product */ \
	template<typename OtherType> \
	inline specific_type dot_prod (const Vec2<OtherType>& to_dot) \
		const \
	{ \
		return (x * to_dot.x) + (y * to_dot.y); \
	} \
	\
	/*
	Z component of a 3D cross product, which is computed as if *this and
	to_zcross have been converted to 3D vectors with Z components of zero
	*/ \
	template<typename OtherType> \
	inline specific_type zcross_prod(const Vec2<OtherType>& to_zcross) const \
	{ \
		return (x * to_zcross.y) - (y * to_zcross.x); \
	} \
	\
	inline Vec2& operator += \
		(const Vec2& to_add) \
	{ \
		x += to_add.x; \
		y += to_add.y; \
		return *this; \
	} \
	inline Vec2& operator -= \
		(const Vec2& to_sub) \
	{ \
		x -= to_sub.x; \
		y -= to_sub.y; \
		return *this; \
	} \
	\
	template<typename OtherType> \
	inline Vec2& operator *= (const OtherType& scale) \
	{ \
		x *= scale; \
		y *= scale; \
		return *this; \
	} \
	\
	/* Comparison Operator Overloads */ \
	inline bool operator == (const Vec2& to_cmp) const \
	{ \
		return ((x == to_cmp.x) && (y == to_cmp.y)); \
	} \
	\
	inline bool operator != (const Vec2& to_cmp) const \
	{ \
		return ((x != to_cmp.x) || (y != to_cmp.y)); \
	} \
	\
	template<typename OtherType> \
	inline operator Vec2<OtherType>() const \
	{ \
		return Vec2<OtherType>(x, y); \
	} \
	\
	inline specific_type& operator [] (size_t index) \
	{ \
		if (index == vec2_index_for_x) \
		{ \
			return x; \
		} \
		else /* if (index != vec2_index_for_x) */ \
		{ \
			return y; \
		} \
	} \
	\
	inline const specific_type& operator [] (size_t index) const \
	{ \
		if (index == vec2_index_for_x) \
		{ \
			return x; \
		} \
		else /* if (index != vec2_index_for_x) */ \
		{ \
			return y; \
		} \
	} \

#define generate_float_pt_vec2_extra_class_contents(specific_type) \
	/* Division */ \
	template<typename OtherType> \
	inline Vec2 operator / (const OtherType& scale) \
		const \
	{ \
		return Vec2 (x / scale, y / scale); \
	} \
	\
	template<typename OtherType> \
	inline Vec2& operator /= (const OtherType& scale) \
		const \
	{ \
		x /= scale; \
		y /= scale; \
		return *this; \
	} \
	\
	/* Approximately Equal, using a Tolerance */ \
	template<typename OtherType> \
	inline bool almost_equal(const Vec2<OtherType>& to_cmp, \
		const Vec2& tolerance_vec) const \
	{ \
		return ((misc_util::custom_abs<specific_type>(x - to_cmp.x) \
			< misc_util::custom_abs<specific_type>(tolerance_vec.x)) \
			&& (misc_util::custom_abs<specific_type>(y - to_cmp.y) \
			< misc_util::custom_abs<specific_type>(tolerance_vec.y))); \
	} \
	\
	/* Approximately Not Equal, using a Tolerance */ \
	template<typename OtherType> \
	inline bool almost_not_equal(const Vec2<OtherType>& to_cmp, \
		const Vec2& tolerance_vec) const \
	{ \
		return ((misc_util::custom_abs<specific_type>(x - to_cmp.x) \
			>= misc_util::custom_abs<specific_type>(tolerance_vec.x)) \
			|| (misc_util::custom_abs<specific_type>(y - to_cmp.y) \
			>= misc_util::custom_abs<specific_type>(tolerance_vec.y))); \
	} \
	/* Magnitude of the vector */ \
	inline specific_type mag() const \
	{ \
		return sqrt(dot_prod(*this)); \
	} \
	/* Unit vector in the direction of *this */ \
	inline Vec2 norm() const \
	{ \
		return (*this) / mag(); \
	}

template<>
class Vec2<float>
{
	generate_specific_vec2_class_contents(float);
	generate_float_pt_vec2_extra_class_contents(float);
};


template<>
class Vec2<double>
{
	generate_specific_vec2_class_contents(double);
	generate_float_pt_vec2_extra_class_contents(double);
};


typedef Vec2<float> Vec2_flt;
typedef Vec2<double> Vec2_dbl;



template<typename Type>
inline Vec2<Type> custom_abs(const Vec2<Type>& val)
{
	return Vec2<Type>(misc_util::custom_abs(val.x), 
		misc_util::custom_abs(val.y));
}

} // namespace containers

} // namespace liborangepower

#endif		// liborangepower_vec2_classes_hpp
