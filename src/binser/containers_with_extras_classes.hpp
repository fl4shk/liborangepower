#ifndef liborangepower_binser_containers_with_extras_classes_hpp
#define liborangepower_binser_containers_with_extras_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/is_specialization_concepts.hpp"

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
};

template<typename T>
constexpr inline bool is_deque_with_extras()
{
	return concepts::is_specialization<T, DequeWithExtras>();
}
//--------
} // namespace binser
} // namespace liborangepower

#endif		// liborangepower_binser_containers_with_extras_classes_hpp
