#ifndef liborangepower_containers_std_hash_stuff_hpp
#define liborangepower_containers_std_hash_stuff_hpp

#include "../misc/misc_includes.hpp"
#include "../strings/sconcat_etc.hpp"

namespace liborangepower {
namespace containers {

template<typename T>
constexpr inline std::size_t hash_remove_cvref(const T& to_hash) {
	return std::hash<std::remove_cvref_t<T>>{}(to_hash);
}
constexpr inline std::size_t hash_merge(size_t h, size_t next) {
	return h ^ (next << std::size_t(1));
}

template<typename Alloc=std::allocator<size_t>>
constexpr inline std::size_t hash_merge(
	const std::vector<size_t, Alloc>& to_merge_darr
) {
	if (to_merge_darr.size() == 0) {
		throw std::invalid_argument(strings::sconcat(
			"liborangepower::containers::hash_merge(",
				"const std::vector<size_t, Alloc>&",
			"): Error: ",
			"to_merge_darr.size() == 0"
			)
		);
	}

	size_t i = 0;
	size_t h = to_merge_darr.at(i++);

	for (; i<to_merge_darr.size(); ++i) {
		h = hash_merge(h, to_merge_darr.at(i));
	}

	return h;
}

template<typename FirstT, typename... RemTs>
constexpr inline std::size_t hash_va(const FirstT& first_arg,
	const RemTs&...  rem_args) {
	//std::size_t h = std::hash<std::remove_cvref_t<FirstT>>{}(first_arg);
	std::size_t h = hash_remove_cvref<FirstT>(first_arg);

	//if constexpr (sizeof...(rem_args) > 0) {
	//	//return h ^ (hash_va<RemTs...>(rem_args...) << std::size_t(1));
	//	//(h ^= std::hash<std::remove_cvref_t<RemTs>(rem_args)
	//	//	<< std::size_t(1), ...);
	//}
	((h = hash_merge(h, hash_remove_cvref<RemTs>(rem_args))), ...);
	return h;
}

} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_std_hash_stuff_hpp
