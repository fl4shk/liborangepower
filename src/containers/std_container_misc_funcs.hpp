#ifndef liborangepower_containers_std_container_misc_funcs_hpp
#define liborangepower_containers_std_container_misc_funcs_hpp

#include <tuple>
#include <vector>


namespace liborangepower
{
namespace containers
{
//--------
// `std::tuple` stuff
template<size_t index, typename FirstArgT, typename... RemArgTs>
inline auto _tuple_rm_last_backend
	(const std::tuple<FirstArgT, RemArgTs...>& tup)
{
	constexpr auto
		tup_cnt = std::tuple_size<std::remove_cvref_t<decltype(tup)>>{};

	if constexpr (index < tup_cnt)
	{
		return std::tuple_cat(std::make_tuple(std::get<index>(tup)),
			_tuple_rm_last_backend<index + size_t(1)>(tup));
	}
	else // if constexpr (index >= tup_cnt)
	{
		return std::make_tuple();
	}
}
template<typename FirstArgT, typename... RemArgTs>
inline auto tuple_rm_last(const std::tuple<FirstArgT, RemArgTs...>& tup)
{
	return _tuple_rm_last_backend<0>(tup);
}

inline auto make_tuple_rm_last(const auto& first_arg,
	const auto&... rem_args)
{
	if constexpr (sizeof...(rem_args) > 0)
	{
		return std::tuple_cat(std::make_tuple(first_arg),
			make_tuple_rm_last(rem_args...));
	}
	else // if constexpr (sizeof...(rem_args) == 0)
	{
		return std::make_tuple();
	}
}

template
<
	typename Tuple,
	typename T=std::decay_t<std::tuple_element_t<0, std::decay_t<Tuple>>>,
	typename Alloc=std::allocator<T>
>
inline std::vector<T, Alloc> tup_to_vec(Tuple&& tup)
{
	// Both of these are from this web page:
	// https://stackoverflow.com/questions/42494715/c-transform-a-stdtuplea-a-a-to-a-stdvector-or-stddeque

	//return std::apply
	//(
	//	[](auto&&... elems)
	//	{
	//		using expander = int[];

	//		std::vector<T> result;
	//		result.reserve(sizeof...(elems));
	//		expander{(void(
	//			result.push_back(std::forward<decltype(elems)>(elems))
	//			), 0)...};
	//		return result;
	//	},
	//	std::forward<Tuple>(tup)
	//);

    return std::apply
	(
		[](auto&&... elems) 
		{
			std::vector<T, Alloc> result;
			result.reserve(sizeof...(elems));
			(
				result.push_back(std::forward<decltype(elems)>(elems)),
				...
			);
			return result;
		},
		std::forward<Tuple>(tup)
	);
}

//template<typename T, typename Alloc, std::size_t... Indices>
//auto _vec_to_tup_backend(const std::vector<T, Alloc>& v,
//	std::index_sequence<Indices...>)
//{
//	return std::make_tuple(v[Indices]...);
//}
//
//template<std::size_t N, typename T, typename Alloc=std::allocator<T>>
//auto vec_to_tup(const std::vector<T, Alloc>& v)
//{
//	assert(v.size() >= N);
//	return _vec_to_tup_backend(v, std::make_index_sequence<N>());
//}
//--------
} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_std_container_misc_funcs_hpp
