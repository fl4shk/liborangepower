#ifndef liborangepower_misc_misc_utility_funcs_hpp
#define liborangepower_misc_misc_utility_funcs_hpp

namespace liborangepower
{

namespace misc_util
{

// Don't use weird things with this.
template<typename FirstArgT, typename SecondArgT>
FirstArgT max_va(const FirstArgT& arg_0, const SecondArgT& arg_1)
{
	if (arg_0 >= arg_1)
	{
		return arg_0;
	}
	else
	{
		return arg_1;
	}
}

template<typename FirstArgT, typename SecondArgT, 
	typename... RemainingTs>
inline FirstArgT max_va(const FirstArgT& arg_0, 
	const SecondArgT& arg_1, RemainingTs... remaining_args )
{
	return max_va(max_va(arg_0, arg_1), remaining_args...);
}


template<typename FirstArgT, typename SecondArgT>
inline FirstArgT min_va(const FirstArgT& arg_0, 
	const SecondArgT& arg_1)
{
	if (arg_0 <= arg_1)
	{
		return arg_0;
	}
	else
	{
		return arg_1;
	}
}

template<typename FirstArgT, typename SecondArgT, 
	typename... RemainingTs>
inline FirstArgT min_va(const FirstArgT& arg_0, 
	const SecondArgT& arg_1, RemainingTs... remaining_args )
{
	return min_va(min_va(arg_0, arg_1), remaining_args...);
}


template<typename T>
inline T custom_abs(const T& val)
{
	if (val < static_cast<T>(0))
	{
		return -val;
	}
	else
	{
		return val;
	}
}


template<typename T, size_t index>
inline void _init_array_backend(T* all_values_arr, 
	const T& to_copy)
{
	//asm_comment("_init_array_backend() single value");
	all_values_arr[index] = to_copy;
}

template<typename T, size_t index, typename... RemainingTs>
inline void _init_array_backend(T* all_values_arr, 
	const T& first_value, const RemainingTs&... remaining_values)
{
	_init_array_backend<T, index>(all_values_arr, first_value);

	_init_array_backend<T, index + 1>(all_values_arr, 
		remaining_values...);
}

template<typename T, typename... AllTheTs>
inline void init_array(T* all_values_arr, 
	const AllTheTs&...  all_the_values)
{
	_init_array_backend<T, 0>(all_values_arr,
		all_the_values...);
}


// This has no real reason to exist
template<typename T>
constexpr inline bool type_is_signed()
{
	return ((T)(-1) < (T)(0));
}


//template<typename FirstArgT, typename SecondArgT>
//bool cmpeq_array(FirstArgT* first_arr, SecondArgT* second_arr,
//	size_t size)
//	_attribute_((noinline));
template<typename FirstArgT, typename SecondArgT>
bool cmpeq_array(FirstArgT* first_arr, SecondArgT* second_arr,
	size_t size)
{
	if (size == 0)
	{
		return false;
	}

	for (size_t i=0; i<size; ++i)
	{
		if (first_arr[i] != second_arr[i])
		{
			return false;
		}
	}

	return true;
}


template<typename FirstArgT>
bool anything_matches(const FirstArgT& first_val)
{
	return false;
}

template<typename FirstArgT, typename SecondArgT,
	typename... RemArgTs>
bool anything_matches(const FirstArgT& first_val,
	const SecondArgT& next, RemArgTs&&... rem_args)
{
	if (sizeof...(rem_args) == 0)
	{
		return (first_val == next);
	}
	else if (first_val == next)
	{
		return true;
	}
	else
	{
		return anything_matches(first_val, rem_args...);
	}
}


} // namespace misc_util

} // namespace liborangepower

#endif		// liborangepower_misc_misc_utility_funcs_hpp
