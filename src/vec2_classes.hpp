#ifndef liborangepower_vec2_classes_hpp
#define liborangepower_vec2_classes_hpp

#include "misc_types.hpp"
#include "misc_defines.hpp"
#include "misc_utility_funcs.hpp"

#include <utility>

static constexpr size_t vec2_index_for_x = 0, vec2_index_for_y = 1;

template< typename type >
class vec2
{
//public:		// constants
//	static constexpr size_t the_index_for_x = 0, the_index_for_y = 1;
//	
public:		// variables
	type x, y;
	
public:		// functions
	constexpr inline vec2() : x( type() ), y( type() )
	{
	}
	
	//inline vec2( const type& s_x, const type& s_y ) : x(s_x), y(s_y)
	//{
	//}
	//
	//inline vec2( const vec2<type>& to_copy ) : x(to_copy.x), y(to_copy.y)
	//{
	//}
	
	
	
	template< typename type_1, typename type_2 >
	constexpr inline vec2( const type_1& s_x, const type_2& s_y )
		: x(s_x), y(s_y)
	{
	}
	template< typename other_type >
	constexpr inline vec2( const vec2<other_type>& to_copy )
		: x(to_copy.x), y(to_copy.y)
	{
	}
	template< typename other_type >
	constexpr inline vec2( vec2<other_type>&& to_move )
		: x(std::move(to_move.x)), y(std::move(to_move.y))
	{
	}
	
	
	template< typename other_type >
	inline vec2<type>& operator = ( const vec2<other_type>& to_copy )
	{
		x = to_copy.x;
		y = to_copy.y;
		
		return *this;
	}
	template< typename other_type >
	inline vec2<type>& operator = ( vec2<other_type>&& to_move )
	{
		x = std::move(to_move.x);
		y = std::move(to_move.y);
		
		return *this;
	}
	
	
	template< typename other_type >
	inline vec2<type> operator + ( const vec2<other_type>& to_add ) const
	{
		return vec2<type>( x + to_add.x, y + to_add.y );
	}
	template< typename other_type >
	inline vec2<type> operator - ( const vec2<other_type>& to_sub ) const
	{
		return vec2<type>( x - to_sub.x, y - to_sub.y );
	}
	
	template< typename other_type >
	inline vec2<type> operator * ( const other_type& scale ) const
	{
		return vec2<type>( x * scale, y * scale );
	}
	
	// Dot product
	template< typename other_type >
	inline type dot_prod( const vec2<other_type>& to_dot ) const
	{
		return ( x * to_dot.x ) + ( y * to_dot.y );
	}
	
	// Z component of a 3D cross product, which is computed as if *this and
	// to_zcross have been converted to 3D vectors with Z components of zero
	template< typename other_type >
	inline type zcross_prod( const vec2<other_type>& to_zcross ) const
	{
		return ( x * to_zcross.y ) - ( y * to_zcross.x );
	}
	
	
	template< typename other_type >
	inline vec2<type>& operator += ( const vec2<other_type>& to_add )
	{
		x += to_add.x;
		y += to_add.y;
		return *this;
	}
	template< typename other_type >
	inline vec2<type>& operator -= ( const vec2<other_type>& to_sub )
	{
		x -= to_sub.x;
		y -= to_sub.y;
		return *this;
	}
	
	template< typename other_type >
	inline vec2<type>& operator *= ( const other_type& scale )
	{
		x *= scale;
		y *= scale;
		return *this;
	}
	
	
	// Comparison Operator Overloads
	template< typename other_type >
	inline bool operator == ( const vec2<other_type>& to_cmp ) const
	{
		return ( ( x == to_cmp.x ) && ( y == to_cmp.y ) );
	}
	
	template< typename other_type >
	inline bool operator != ( const vec2<other_type>& to_cmp ) const
	{
		return ( ( x != to_cmp.x ) || ( y != to_cmp.y ) );
	}
	
	
	template< typename other_type >
	inline operator vec2<other_type>() const
	{
		return vec2<other_type>( x, y );
	}
	
	inline type& operator [] ( size_t index )
	{
		if ( index == vec2_index_for_x )
		{
			return x;
		}
		else //if ( index != vec2_index_for_x )
		{
			return y;
		}
	}
	
	inline const type& operator [] ( size_t index ) const
	{
		if ( index == vec2_index_for_x )
		{
			return x;
		}
		else //if ( index != vec2_index_for_x )
		{
			return y;
		}
	}
	
} __attribute__((_align4));




template< typename type >
inline vec2<type> operator * ( const type& scale, 
	const vec2<type>& vec2_to_mul )
{
	return vec2_to_mul * scale;
}


typedef vec2<u16> vec2_u16; typedef vec2<s16> vec2_s16;
typedef vec2<u32> vec2_u32; typedef vec2<s32> vec2_s32;
typedef vec2<u64> vec2_u64; typedef vec2<s64> vec2_s64;


#define generate_specific_vec2_class_contents( specific_type ) \
public:		/* variables */ \
	specific_type x, y; \
	\
public:		/* functions */ \
	constexpr inline vec2() : x(specific_type()), y(specific_type()) \
	{ \
	} \
	\
	constexpr inline vec2( const specific_type& s_x, \
		const specific_type& s_y ) : x(s_x), y(s_y) \
	{ \
	} \
	constexpr inline vec2( const vec2<specific_type>& to_copy ) \
		: x(to_copy.x), y(to_copy.y) \
	{ \
	} \
	constexpr inline vec2( vec2<specific_type>&& to_move ) \
		: x(std::move(to_move.x)), y(std::move(to_move.y)) \
	{ \
	} \
	\
	inline vec2<specific_type>& operator = \
		( const vec2<specific_type>& to_copy ) \
	{ \
		x = to_copy.x; \
		y = to_copy.y; \
		\
		return *this; \
	} \
	inline vec2<specific_type>& operator = \
		( vec2<specific_type>&& to_move ) \
	{ \
		x = std::move(to_move.x); \
		y = std::move(to_move.y); \
		\
		return *this; \
	} \
	\
	template< typename other_type > \
	inline vec2<specific_type> operator + \
		( const vec2<other_type>& to_add ) const \
	{ \
		return vec2<specific_type> ( x + to_add.x, y + to_add.y ); \
	} \
	template< typename other_type > \
	inline vec2<specific_type> operator - \
		( const vec2<other_type>& to_sub ) const \
	{ \
		return vec2<specific_type> ( x - to_sub.x, y - to_sub.y ); \
	} \
	\
	template< typename other_type > \
	inline vec2<specific_type> operator * ( const other_type& scale ) \
		const \
	{ \
		return vec2<specific_type> ( x * scale, y * scale ); \
	} \
	\
	/* Dot product */ \
	template< typename other_type > \
	inline specific_type dot_prod ( const vec2<other_type>& to_dot ) \
		const \
	{ \
		return ( x * to_dot.x ) + ( y * to_dot.y ); \
	} \
	\
	/*
	Z component of a 3D cross product, which is computed as if *this and
	to_zcross have been converted to 3D vectors with Z components of zero
	*/ \
	template< typename other_type > \
	inline specific_type zcross_prod( const vec2<other_type>& to_zcross ) const \
	{ \
		return ( x * to_zcross.y ) - ( y * to_zcross.x ); \
	} \
	\
	inline vec2<specific_type>& operator += \
		( const vec2<specific_type>& to_add ) \
	{ \
		x += to_add.x; \
		y += to_add.y; \
		return *this; \
	} \
	inline vec2<specific_type>& operator -= \
		( const vec2<specific_type>& to_sub ) \
	{ \
		x -= to_sub.x; \
		y -= to_sub.y; \
		return *this; \
	} \
	\
	template< typename other_type > \
	inline vec2<specific_type>& operator *= ( const other_type& scale ) \
	{ \
		x *= scale; \
		y *= scale; \
		return *this; \
	} \
	\
	/* Comparison Operator Overloads */ \
	inline bool operator == ( const vec2<specific_type>& to_cmp ) const \
	{ \
		return ( ( x == to_cmp.x ) && ( y == to_cmp.y ) ); \
	} \
	\
	inline bool operator != ( const vec2<specific_type>& to_cmp ) const \
	{ \
		return ( ( x != to_cmp.x ) || ( y != to_cmp.y ) ); \
	} \
	\
	template< typename other_type > \
	inline operator vec2<other_type>() const \
	{ \
		return vec2<other_type>( x, y ); \
	} \
	\
	inline specific_type& operator [] ( size_t index ) \
	{ \
		if ( index == vec2_index_for_x ) \
		{ \
			return x; \
		} \
		else /* if ( index != vec2_index_for_x ) */ \
		{ \
			return y; \
		} \
	} \
	\
	inline const specific_type& operator [] ( size_t index ) const \
	{ \
		if ( index == vec2_index_for_x ) \
		{ \
			return x; \
		} \
		else /* if ( index != vec2_index_for_x ) */ \
		{ \
			return y; \
		} \
	} \

#define generate_float_pt_vec2_extra_class_contents( specific_type ) \
	/* Division */ \
	template< typename other_type > \
	inline vec2<specific_type> operator / ( const other_type& scale ) \
		const \
	{ \
		return vec2<specific_type> ( x / scale, y / scale ); \
	} \
	\
	template< typename other_type > \
	inline vec2<specific_type>& operator /= ( const other_type& scale ) \
		const \
	{ \
		x /= scale; \
		y /= scale; \
		return *this; \
	} \
	\
	/* Approximately Equal, using a Tolerance */ \
	template< typename other_type > \
	inline bool almost_equal( const vec2<other_type>& to_cmp, \
		const vec2<specific_type>& tolerance_vec ) const \
	{ \
		return ( ( custom_abs<specific_type>( x - to_cmp.x ) \
			< custom_abs<specific_type>(tolerance_vec.x) ) \
			&& ( custom_abs<specific_type>( y - to_cmp.y ) \
			< custom_abs<specific_type>(tolerance_vec.y) ) ); \
	} \
	\
	/* Approximately Not Equal, using a Tolerance */ \
	template< typename other_type > \
	inline bool almost_not_equal( const vec2<other_type>& to_cmp, \
		const vec2<specific_type>& tolerance_vec ) const \
	{ \
		return ( ( custom_abs<specific_type>( x - to_cmp.x ) \
			>= custom_abs<specific_type>(tolerance_vec.x) ) \
			|| ( custom_abs<specific_type>( y - to_cmp.y ) \
			>= custom_abs<specific_type>(tolerance_vec.y) ) ); \
	} \
	/* Magnitude of the vector */ \
	inline specific_type mag() const \
	{ \
		return sqrt(dot_prod(*this)); \
	} \
	/* Unit vector in the direction of *this */ \
	inline vec2<specific_type> norm() const \
	{ \
		return (*this) / mag(); \
	}

template<>
class vec2<float>
{
	generate_specific_vec2_class_contents(float);
	generate_float_pt_vec2_extra_class_contents(float);
} __attribute__((_align4));


template<>
class vec2<double>
{
	generate_specific_vec2_class_contents(double);
	generate_float_pt_vec2_extra_class_contents(double);
} __attribute__((_align4));


typedef vec2<float> vec2_flt;
typedef vec2<double> vec2_dbl;



template< typename type >
inline vec2<type> custom_abs( const vec2<type>& val )
{
	return vec2<type>( custom_abs(val.x), custom_abs(val.y) );
}

#endif		// liborangepower_vec2_classes_hpp
