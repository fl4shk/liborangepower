#ifndef liborangepower_vec2_classes_hpp
#define liborangepower_vec2_classes_hpp

#include "misc_types.hpp"
#include "misc_defines.hpp"
#include "misc_utility_funcs.hpp"

#include <utility>

namespace liborangepower
{

static constexpr size_t vec2_index_for_x = 0, vec2_index_for_y = 1;

template< typename type >
class Vec2
{
//public:		// constants
//	static constexpr size_t the_index_for_x = 0, the_index_for_y = 1;
//	
public:		// variables
	type x, y;
	
public:		// functions
	constexpr inline Vec2() : x(type()), y(type())
	{
	}
	
	//inline Vec2(const type& s_x, const type& s_y) : x(s_x), y(s_y)
	//{
	//}
	//
	//inline Vec2(const Vec2<type>& to_copy) : x(to_copy.x), y(to_copy.y)
	//{
	//}
	
	
	
	template< typename type_1, typename type_2 >
	constexpr inline Vec2(const type_1& s_x, const type_2& s_y)
		: x(s_x), y(s_y)
	{
	}
	template< typename other_type >
	constexpr inline Vec2(const Vec2<other_type>& to_copy)
		: x(to_copy.x), y(to_copy.y)
	{
	}
	template< typename other_type >
	constexpr inline Vec2(Vec2<other_type>&& to_move)
		: x(std::move(to_move.x)), y(std::move(to_move.y))
	{
	}
	
	
	template< typename other_type >
	inline Vec2<type>& operator = (const Vec2<other_type>& to_copy)
	{
		x = to_copy.x;
		y = to_copy.y;
		
		return *this;
	}
	template< typename other_type >
	inline Vec2<type>& operator = (Vec2<other_type>&& to_move)
	{
		x = std::move(to_move.x);
		y = std::move(to_move.y);
		
		return *this;
	}
	
	
	template< typename other_type >
	inline Vec2<type> operator + (const Vec2<other_type>& to_add) const
	{
		return Vec2<type>(x + to_add.x, y + to_add.y);
	}
	template< typename other_type >
	inline Vec2<type> operator - (const Vec2<other_type>& to_sub) const
	{
		return Vec2<type>(x - to_sub.x, y - to_sub.y);
	}
	
	template< typename other_type >
	inline Vec2<type> operator * (const other_type& scale) const
	{
		return Vec2<type>(x * scale, y * scale);
	}
	
	// Dot product
	template< typename other_type >
	inline type dot_prod(const Vec2<other_type>& to_dot) const
	{
		return (x * to_dot.x) + (y * to_dot.y);
	}
	
	// Z component of a 3D cross product, which is computed as if *this and
	// to_zcross have been converted to 3D vectors with Z components of zero
	template< typename other_type >
	inline type zcross_prod(const Vec2<other_type>& to_zcross) const
	{
		return (x * to_zcross.y) - (y * to_zcross.x);
	}
	
	
	template< typename other_type >
	inline Vec2<type>& operator += (const Vec2<other_type>& to_add)
	{
		x += to_add.x;
		y += to_add.y;
		return *this;
	}
	template< typename other_type >
	inline Vec2<type>& operator -= (const Vec2<other_type>& to_sub)
	{
		x -= to_sub.x;
		y -= to_sub.y;
		return *this;
	}
	
	template< typename other_type >
	inline Vec2<type>& operator *= (const other_type& scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}
	
	
	// Comparison Operator Overloads
	template< typename other_type >
	inline bool operator == (const Vec2<other_type>& to_cmp) const
	{
		return ((x == to_cmp.x) && (y == to_cmp.y));
	}
	
	template< typename other_type >
	inline bool operator != (const Vec2<other_type>& to_cmp) const
	{
		return ((x != to_cmp.x) || (y != to_cmp.y));
	}
	
	
	template< typename other_type >
	inline operator Vec2<other_type>() const
	{
		return Vec2<other_type>(x, y);
	}
	
	inline type& operator [] (size_t index)
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
	
	inline const type& operator [] (size_t index) const
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
	
} __attribute__((_align4));




template< typename type >
inline Vec2<type> operator * (const type& scale, 
	const Vec2<type>& vec2_to_mul)
{
	return vec2_to_mul * scale;
}


typedef Vec2<u16> Vec2_u16; typedef Vec2<s16> Vec2_s16;
typedef Vec2<u32> Vec2_u32; typedef Vec2<s32> Vec2_s32;
typedef Vec2<u64> Vec2_u64; typedef Vec2<s64> Vec2_s64;


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
	constexpr inline Vec2(const Vec2<specific_type>& to_copy) \
		: x(to_copy.x), y(to_copy.y) \
	{ \
	} \
	constexpr inline Vec2(Vec2<specific_type>&& to_move) \
		: x(std::move(to_move.x)), y(std::move(to_move.y)) \
	{ \
	} \
	\
	inline Vec2<specific_type>& operator = \
		(const Vec2<specific_type>& to_copy) \
	{ \
		x = to_copy.x; \
		y = to_copy.y; \
		\
		return *this; \
	} \
	inline Vec2<specific_type>& operator = \
		(Vec2<specific_type>&& to_move) \
	{ \
		x = std::move(to_move.x); \
		y = std::move(to_move.y); \
		\
		return *this; \
	} \
	\
	template< typename other_type > \
	inline Vec2<specific_type> operator + \
		(const Vec2<other_type>& to_add) const \
	{ \
		return Vec2<specific_type> (x + to_add.x, y + to_add.y); \
	} \
	template< typename other_type > \
	inline Vec2<specific_type> operator - \
		(const Vec2<other_type>& to_sub) const \
	{ \
		return Vec2<specific_type> (x - to_sub.x, y - to_sub.y); \
	} \
	\
	template< typename other_type > \
	inline Vec2<specific_type> operator * (const other_type& scale) \
		const \
	{ \
		return Vec2<specific_type> (x * scale, y * scale); \
	} \
	\
	/* Dot product */ \
	template< typename other_type > \
	inline specific_type dot_prod (const Vec2<other_type>& to_dot) \
		const \
	{ \
		return (x * to_dot.x) + (y * to_dot.y); \
	} \
	\
	/*
	Z component of a 3D cross product, which is computed as if *this and
	to_zcross have been converted to 3D vectors with Z components of zero
	*/ \
	template< typename other_type > \
	inline specific_type zcross_prod(const Vec2<other_type>& to_zcross) const \
	{ \
		return (x * to_zcross.y) - (y * to_zcross.x); \
	} \
	\
	inline Vec2<specific_type>& operator += \
		(const Vec2<specific_type>& to_add) \
	{ \
		x += to_add.x; \
		y += to_add.y; \
		return *this; \
	} \
	inline Vec2<specific_type>& operator -= \
		(const Vec2<specific_type>& to_sub) \
	{ \
		x -= to_sub.x; \
		y -= to_sub.y; \
		return *this; \
	} \
	\
	template< typename other_type > \
	inline Vec2<specific_type>& operator *= (const other_type& scale) \
	{ \
		x *= scale; \
		y *= scale; \
		return *this; \
	} \
	\
	/* Comparison Operator Overloads */ \
	inline bool operator == (const Vec2<specific_type>& to_cmp) const \
	{ \
		return ((x == to_cmp.x) && (y == to_cmp.y)); \
	} \
	\
	inline bool operator != (const Vec2<specific_type>& to_cmp) const \
	{ \
		return ((x != to_cmp.x) || (y != to_cmp.y)); \
	} \
	\
	template< typename other_type > \
	inline operator Vec2<other_type>() const \
	{ \
		return Vec2<other_type>(x, y); \
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
	template< typename other_type > \
	inline Vec2<specific_type> operator / (const other_type& scale) \
		const \
	{ \
		return Vec2<specific_type> (x / scale, y / scale); \
	} \
	\
	template< typename other_type > \
	inline Vec2<specific_type>& operator /= (const other_type& scale) \
		const \
	{ \
		x /= scale; \
		y /= scale; \
		return *this; \
	} \
	\
	/* Approximately Equal, using a Tolerance */ \
	template< typename other_type > \
	inline bool almost_equal(const Vec2<other_type>& to_cmp, \
		const Vec2<specific_type>& tolerance_vec) const \
	{ \
		return ((custom_abs<specific_type>(x - to_cmp.x) \
			< custom_abs<specific_type>(tolerance_vec.x)) \
			&& (custom_abs<specific_type>(y - to_cmp.y) \
			< custom_abs<specific_type>(tolerance_vec.y))); \
	} \
	\
	/* Approximately Not Equal, using a Tolerance */ \
	template< typename other_type > \
	inline bool almost_not_equal(const Vec2<other_type>& to_cmp, \
		const Vec2<specific_type>& tolerance_vec) const \
	{ \
		return ((custom_abs<specific_type>(x - to_cmp.x) \
			>= custom_abs<specific_type>(tolerance_vec.x)) \
			|| (custom_abs<specific_type>(y - to_cmp.y) \
			>= custom_abs<specific_type>(tolerance_vec.y))); \
	} \
	/* Magnitude of the vector */ \
	inline specific_type mag() const \
	{ \
		return sqrt(dot_prod(*this)); \
	} \
	/* Unit vector in the direction of *this */ \
	inline Vec2<specific_type> norm() const \
	{ \
		return (*this) / mag(); \
	}

template<>
class Vec2<float>
{
	generate_specific_vec2_class_contents(float);
	generate_float_pt_vec2_extra_class_contents(float);
} __attribute__((_align4));


template<>
class Vec2<double>
{
	generate_specific_vec2_class_contents(double);
	generate_float_pt_vec2_extra_class_contents(double);
} __attribute__((_align4));


typedef Vec2<float> Vec2_flt;
typedef Vec2<double> Vec2_dbl;



template< typename type >
inline Vec2<type> custom_abs(const Vec2<type>& val)
{
	return Vec2<type>(custom_abs(val.x), custom_abs(val.y));
}

}

#endif		// liborangepower_vec2_classes_hpp
