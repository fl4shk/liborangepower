#ifndef liborangepower_binser_ex_container_classes_hpp
#define liborangepower_binser_ex_container_classes_hpp

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
//template<template<typename...> typename ContnrEtcT,
//	typename FirstT, typename... RemTs>
//class CsContnrExBase
//{
//public:		// serialized variables
//	ContnrEtcT<FirstT, RemTs...> data;
//public:		// non-serialized variables
//	u64 checked_size;
//	bool cs_is_max = false;
//	u64 min_size = 0;
//};
//--------
using ExSizeT
	= u64;
using ExBoolT
	= bool;

template<typename ExContnrEtcT>
concept LikeExCs = requires(ExContnrEtcT c)
{
	{ c.data } -> std::same_as<typename ExContnrEtcT::DataT>;
	{ c.checked_size } -> std::same_as<ExSizeT>;
	{ c.cs_is_max } -> std::same_as<ExBoolT>;
	{ c.min_size } -> std::same_as<ExSizeT>;
};
template<typename ExContnrEtcT>
concept LikeExMm = requires(ExContnrEtcT c)
{
	{ c.data } -> std::same_as<typename ExContnrEtcT::DataT>;
	{ c.max } -> std::same_as<typename ExContnrEtcT::DataT>;
	{ c.min } -> std::same_as<typename ExContnrEtcT::DataT>;
};
//--------
template<typename T, typename Allocator=std::allocator<T>>
class VectorEx final
{
public:		// types
	using DataT = std::vector<T, Allocator>;
public:		// serialized variables
	DataT data;
public:		// non-serialized variables
	ExSizeT checked_size;
	ExBoolT cs_is_max = false;
	ExSizeT min_size = 0;
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
public:		// types
	using DataT = std::deque<T, Allocator>;
public:		// serialized variables
	DataT data;
public:		// non-serialized variables
	ExSizeT checked_size;
	ExBoolT cs_is_max = false;
	ExSizeT min_size = 0;
};

template<typename T>
constexpr inline bool is_deque_ex()
{
	return concepts::is_specialization<T, DequeEx>();
}
//--------
template<typename T, typename ArgIndexT=size_t,
	typename ArgIndexAllocT=std::allocator<ArgIndexT>,
	typename ArgNodeAllocT=std::allocator
		<liborangepower::containers::IndCllNode<T, ArgIndexT>>>
class IndCircLinkListEx final
{
public:		// types
	using DataT = containers::IndCircLinkList
		<T, ArgIndexT, ArgIndexAllocT, ArgNodeAllocT>;
public:		// serialized variables
	DataT data;
public:		// non-serialized variables
	ExSizeT checked_size;
	ExBoolT cs_is_max = false;
	ExSizeT min_size = 0;
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
public:		// types
	using DataT = T;
public:		// serialized variables
	DataT data;
public:		// non-serialized variables
	DataT max, min;
public:		// functions
	//--------
	inline operator DataT () const
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
public:		// types
	using DataT = math::Vec2<T>;
public:		// serialized variables
	DataT data;
public:		// non-serialized variables
	DataT max, min;
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
	inline operator DataT () const
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
public:		// types
	using DataT = math::Vec3<T>;
public:		// serialized variables
	DataT data;
public:		// non-serialized variables
	DataT max, min;
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
	inline operator DataT () const
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
public:		// types
	using DataT = math::LineSeg2<T>;
public:		// serialized variables
	DataT data;
public:		// non-serialized variables
	DataT max, min;
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
	inline operator DataT () const
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
public:		// types
	using DataT = math::Rect2<T>;
public:		// serialized variables
	DataT data;
public:		// non-serialized variables
	DataT max, min;
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
	inline operator DataT () const
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

#endif		// liborangepower_binser_ex_container_classes_hpp
