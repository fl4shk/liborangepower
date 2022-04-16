#ifndef liborangepower_binser_ex_containers_classes_hpp
#define liborangepower_binser_ex_containers_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/is_specialization_concepts.hpp"

#include "../containers/vec2_classes.hpp"
#include "../containers/vec3_classes.hpp"
#include "../containers/linked_list_classes.hpp"

namespace liborangepower
{
namespace binser
{
//--------
template<template<typename...> typename CntnrEtcT,
	typename FirstT, typename... RemTs>
class CsCntnrExBase
{
public:		// serialized variables
	CntnrEtcT<FirstT, RemTs...> data;
public:		// non-serialized variables
	u64 checked_size;
	bool cs_is_max = false;
	u64 min_size = 0;
};
//--------
template<typename T, typename Allocator=std::allocator<T>>
class VectorEx final: public CsCntnrExBase<std::vector, T, Allocator>
{
};

template<typename T>
constexpr inline bool is_vector_ex()
{
	return concepts::is_specialization<T, VectorEx>();
}
//--------
template<typename T, typename Allocator=std::allocator<T>>
class DequeEx final: public CsCntnrExBase<std::deque, T, Allocator>
{
};

template<typename T>
constexpr inline bool is_deque_ex()
{
	return concepts::is_specialization<T, DequeEx>();
}
//--------
template<typename T, typename ArgIndexT=uint64_t>
class IndCircLinkListEx final:
	public CsCntnrExBase<containers::IndCircLinkList, T, ArgIndexT>
{
};

template<typename T>
constexpr inline bool is_ind_circ_link_list_ex()
{
	return concepts::is_specialization<T, IndCircLinkListEx>();
}
//--------
template<typename T>
class JustMaxMinCntnrExBase
{
public:		// variables
	T data;
public:		// non-serialized variables
	T max, min;
public:		// variables
	inline operator T () const
	{
		return data;
	}
};
//--------
template<typename T>
class ScalarEx final: public JustMaxMinCntnrExBase<T>
{
};

template<typename T>
constexpr inline bool is_scalar_ex()
{
	return concepts::is_specialization<T, ScalarEx>();
}
//--------
template<typename T>
class Vec2Ex final: public JustMaxMinCntnrExBase<containers::Vec2<T>>
{
public:		// types
	using Base = JustMaxMinCntnrExBase<containers::Vec2<T>>;
public:		// functions
	//--------
	inline T& x()
	{
		return Base::data.x;
	}
	inline const T& x() const
	{
		return Base::data.x;
	}
	inline T& y()
	{
		return Base::data.y;
	}
	inline const T& y() const
	{
		return Base::data.y;
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
class Vec3Ex final: public JustMaxMinCntnrExBase<containers::Vec3<T>>
{
public:		// types
	using Base = JustMaxMinCntnrExBase<containers::Vec3<T>>;
public:		// functions
	//--------
	inline T& x()
	{
		return Base::data.x;
	}
	inline const T& x() const
	{
		return Base::data.x;
	}
	inline T& y()
	{
		return Base::data.y;
	}
	inline const T& y() const
	{
		return Base::data.y;
	}
	inline T& z()
	{
		return Base::data.z;
	}
	inline const T& z() const
	{
		return Base::data.z;
	}
	//--------
};

template<typename T>
constexpr inline bool is_vec3_ex()
{
	return concepts::is_specialization<T, Vec3Ex>();
}
//--------
} // namespace binser
} // namespace liborangepower

#endif		// liborangepower_binser_ex_containers_classes_hpp
