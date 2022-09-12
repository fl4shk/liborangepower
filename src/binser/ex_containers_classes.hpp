#ifndef liborangepower_binser_ex_containers_classes_hpp
#define liborangepower_binser_ex_containers_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/is_specialization_concepts.hpp"

#include "../math/vec2_classes.hpp"
#include "../math/vec3_classes.hpp"
#include "../math/shape_2d_classes.hpp"
#include "../containers/linked_list_classes.hpp"

namespace liborangepower
{
namespace binser
{
//--------
// This didn't work
//template<template<typename...> typename CntnrEtcT,
//	typename FirstT, typename... RemTs>
//class CsCntnrExBase
//{
//public:		// serialized variables
//	CntnrEtcT<FirstT, RemTs...> data;
//public:		// non-serialized variables
//	u64 checked_size;
//	bool cs_is_max = false;
//	u64 min_size = 0;
//};
//--------
template<typename T, typename Allocator=std::allocator<T>>
class VectorEx final
{
public:		// serialized variables
	std::vector<T, Allocator> data;
public:		// non-serialized variables
	u64 checked_size;
	bool cs_is_max = false;
	u64 min_size = 0;
};

template<typename T>
constexpr inline bool is_vector_ex()
{
	return concepts::is_specialization<T, VectorEx>();
}
//--------
template<typename T, typename Allocator=std::allocator<T>>
class DequeEx final
{
public:		// serialized variables
	std::deque<T, Allocator> data;
public:		// non-serialized variables
	u64 checked_size;
	bool cs_is_max = false;
	u64 min_size = 0;
};

template<typename T>
constexpr inline bool is_deque_ex()
{
	return concepts::is_specialization<T, DequeEx>();
}
//--------
template<typename T, typename ArgIndexT=uint64_t>
class IndCircLinkListEx final
{
public:		// serialized variables
	containers::IndCircLinkList<T, ArgIndexT> data;
public:		// non-serialized variables
	u64 checked_size;
	bool cs_is_max = false;
	u64 min_size = 0;
};

template<typename T>
constexpr inline bool is_ind_circ_link_list_ex()
{
	return concepts::is_specialization<T, IndCircLinkListEx>();
}
//--------
template<typename T>
class ScalarEx final
{
public:		// serialized variables
	T data;
public:		// non-serialized variables
	T max, min;
public:		// functions
	//--------
	inline operator T () const
	{
		return data;
	}
	//--------
};

template<typename T>
constexpr inline bool is_scalar_ex()
{
	return concepts::is_specialization<T, ScalarEx>();
}
//--------
template<typename T>
class Vec2Ex final
{
public:		// serialized variables
	math::Vec2<T> data;
public:		// non-serialized variables
	math::Vec2<T> max, min;
public:		// functions
	//--------
	inline T& x()
	{
		return data.x;
	}
	inline const T& x() const
	{
		return data.x;
	}
	inline T& y()
	{
		return data.y;
	}
	inline const T& y() const
	{
		return data.y;
	}
	//--------
	inline operator math::Vec2<T> () const
	{
		return data;
	}
	//--------
};

template<typename T>
constexpr inline bool is_vec2_ex()
{
	return concepts::is_specialization<T, Vec2Ex>();
}
//--------
template<typename T>
class Vec3Ex final
{
public:		// serialized variables
	math::Vec3<T> data;
public:		// non-serialized variables
	math::Vec3<T> max, min;
public:		// functions
	//--------
	inline T& x()
	{
		return data.x;
	}
	inline const T& x() const
	{
		return data.x;
	}
	inline T& y()
	{
		return data.y;
	}
	inline const T& y() const
	{
		return data.y;
	}
	inline T& z()
	{
		return data.z;
	}
	inline const T& z() const
	{
		return data.z;
	}
	//--------
	inline operator math::Vec3<T> () const
	{
		return data;
	}
	//--------
};

template<typename T>
constexpr inline bool is_vec3_ex()
{
	return concepts::is_specialization<T, Vec3Ex>();
}
//--------
//template<typename T>
//class Hit2Ex final
//{
//};
//template<typename T>
//constexpr inline bool is_hit2_ex()
//{
//	return concepts::is_specialization<T, Hit2Ex>();
//}
//--------
//template<typename T>
//constexpr inline bool is_sweep2_ex()
//{
//	return concepts::is_specialization<T, Sweep2Ex>();
//}
//--------
template<typename T>
class LineSeg2Ex final
{
public:		// serialized variables
	math::LineSeg2<T> data;
public:		// non-serialized variables
	math::LineSeg2<T> max, min;
public:		// functions
	//--------
	inline math::Vec2<T>& p0()
	{
		return data.p0;
	}
	inline const math::Vec2<T>& p0() const
	{
		return data.p0;
	}

	inline math::Vec2<T>& p1()
	{
		return data.p1;
	}
	inline const math::Vec2<T>& p1() const
	{
		return data.p1;
	}
	//--------
	inline operator math::LineSeg2<T> () const
	{
		return data;
	}
	//--------
};
template<typename T>
constexpr inline bool is_line_seg2_ex()
{
	return concepts::is_specialization<T, LineSeg2Ex>();
}
//--------
template<typename T>
class Rect2Ex final
{
public:		// serialized variables
	math::Rect2<T> data;
public:		// non-serialized variables
	math::Rect2<T> max, min;
public:		// functions
	//--------
	inline math::Vec2<T>& pos()
	{
		return data.pos;
	}
	inline const math::Vec2<T>& pos() const
	{
		return data.pos;
	}

	inline math::Vec2<T>& size_2d()
	{
		return data.size_2d;
	}
	inline const math::Vec2<T>& size_2d() const
	{
		return data.size_2d;
	}
	//--------
	inline operator math::Rect2<T> () const
	{
		return data;
	}
	//--------
};

template<typename T>
constexpr inline bool is_rect2_ex()
{
	return concepts::is_specialization<T, Rect2Ex>();
}
//--------
} // namespace binser
} // namespace liborangepower

#endif		// liborangepower_binser_ex_containers_classes_hpp
