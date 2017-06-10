#ifndef liborangepower_misc_utility_funcs_hpp
#define liborangepower_misc_utility_funcs_hpp

namespace liborangepower
{

template< typename type >
inline const type& max2(const type& arg_0, const type& arg_1)
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

template< typename type >
inline const type& max3(const type& arg_0, const type& arg_1, 
	const type& arg_2)
{
	if (arg_0 >= arg_1 && arg_0 >= arg_2)
	{
		return arg_0;
	}
	else if (arg_1 >= arg_2)
	{
		return arg_1;
	}
	else
	{
		return arg_2;
	}
}


// Don't use weird things with this.
template< typename first_type, typename second_type >
first_type max_va(const first_type& arg_0, const second_type& arg_1)
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

template< typename first_type, typename second_type, 
	typename... remaining_types >
inline first_type max_va(const first_type& arg_0, 
	const second_type& arg_1, remaining_types... remaining_args )
{
	return max_va(max_va(arg_0, arg_1), remaining_args...);
}


template< typename first_type, typename second_type >
inline first_type min_va(const first_type& arg_0, 
	const second_type& arg_1)
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

template< typename first_type, typename second_type, 
	typename... remaining_types >
inline first_type min_va(const first_type& arg_0, 
	const second_type& arg_1, remaining_types... remaining_args )
{
	return min_va(min_va(arg_0, arg_1), remaining_args...);
}


template< typename type >
inline type custom_abs(const type& val)
{
	if (val < static_cast<type>(0))
	{
		return -val;
	}
	else
	{
		return val;
	}
}


template< typename type, size_t index >
inline void copy_to_array_backend(type* all_values_arr, 
	const type& to_copy)
{
	//asm_comment("copy_to_array_backend() single value");
	all_values_arr[index] = to_copy;
}

template< typename type, size_t index, typename... remaining_types >
inline void copy_to_array_backend(type* all_values_arr, 
	const type& first_value, const remaining_types&... remaining_values)
{
	copy_to_array_backend< type, index >(all_values_arr, first_value);
	
	copy_to_array_backend< type, index + 1 >(all_values_arr, 
		remaining_values...);
}

template< typename type, typename... all_the_types >
inline void copy_to_array(type* all_values_arr, 
	const all_the_types&...  all_the_values)
{
	copy_to_array_backend< type, 0 >(all_values_arr,
		all_the_values...);
}


// This has no real reason to exist
template< typename type >
constexpr inline bool type_is_signed()
{
	return ((type)(-1) < (type)(0));
}

}

#endif		// liborangepower_misc_utility_funcs_hpp
