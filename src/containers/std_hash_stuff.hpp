#ifndef liborangepower_containers_std_hash_stuff_hpp
#define liborangepower_containers_std_hash_stuff_hpp

#include "../misc/misc_includes.hpp"

namespace liborangepower
{
namespace containers
{

template<typename FirstT, typename... RemTs>
inline std::size_t hash_va(const FirstT& first_arg,
	const RemTs&&...  rem_args)
{
	const std::size_t h = std::hash<FirstT>{}(first_arg);

	if constexpr (sizeof...(rem_args) > 0)
	{
		return h ^ (hash_va<RemTs...>(rem_args...) << std::size_t(1));
	}
	else
	{
		return h;
	}
}

} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_std_hash_stuff_hpp
