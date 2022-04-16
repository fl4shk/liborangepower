#ifndef liborangepower_binser_containers_with_extras_classes_hpp
#define liborangepower_binser_containers_with_extras_classes_hpp

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
class VectorWithExtras final
{
public:		// serialized variables
	std::vector<T, Allocator> data;
public:		// non-serialized variables
	u64 checked_size;
	bool cs_is_max = false;
	u64 min_size = 0;
};

template<typename T>
constexpr inline bool is_vector_with_extras()
{
	return concepts::is_specialization<T, VectorWithExtras>();
}
//--------
template<typename T, typename Allocator=std::allocator<T>>
class DequeWithExtras final
{
public:		// serialized variables
	std::deque<T, Allocator> data;
public:		// non-serialized variables
	u64 checked_size;
	bool cs_is_max = false;
	u64 min_size = 0;
};

template<typename T>
constexpr inline bool is_deque_with_extras()
{
	return concepts::is_specialization<T, DequeWithExtras>();
}
//--------
template<typename T>
class Vec2WithExtras final
{
public:		// serialized variables
	Vec2<T> data;
public:		// non-serialized variables
	Vec2<T> max, min;
};

template<typename T>
constexpr inline bool is_vec2_with_extras()
{
	return concepts::is_specialization<T, Vec2WithExtras>();
}
//--------
template<typename T>
class Vec3WithExtras final
{
public:		// serialized variables
	Vec3<T> data;
public:		// non-serialized variables
	Vec3<T> max, min;
};

template<typename T>
constexpr inline bool is_vec3_with_extras()
{
	return concepts::is_specialization<T, Vec3WithExtras>();
}
//--------
} // namespace binser
} // namespace liborangepower

#endif		// liborangepower_binser_containers_with_extras_classes_hpp
