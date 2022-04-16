#ifndef liborangepower_binser_ex_containers_classes_hpp
#define liborangepower_binser_ex_containers_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/is_specialization_concepts.hpp"

#include "../containers/vec2_classes.hpp"
#include "../containers/vec3_classes.hpp"

namespace liborangepower
{
namespace binser
{
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
template<typename T>
class Vec2Ex final
{
public:		// serialized variables
	containers::Vec2<T> data;
public:		// non-serialized variables
	containers::Vec2<T> max, min;
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
	inline operator Vec2<T> () const
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
	containers::Vec3<T> data;
public:		// non-serialized variables
	containers::Vec3<T> max, min;
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
	inline operator Vec3<T> () const
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
} // namespace binser
} // namespace liborangepower

#endif		// liborangepower_binser_ex_containers_classes_hpp
