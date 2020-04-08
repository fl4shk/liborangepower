#ifndef liborangepower_misc_misc_utility_funcs_hpp
#define liborangepower_misc_misc_utility_funcs_hpp

namespace liborangepower
{

namespace misc_util
{

// Don't use weird things with this.
template<typename FirstArgType, typename SecondArgType>
FirstArgType max_va(const FirstArgType& arg_0, const SecondArgType& arg_1)
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

template<typename FirstArgType, typename SecondArgType, 
	typename... RemainingTypes>
inline FirstArgType max_va(const FirstArgType& arg_0, 
	const SecondArgType& arg_1, RemainingTypes... remaining_args )
{
	return max_va(max_va(arg_0, arg_1), remaining_args...);
}


template<typename FirstArgType, typename SecondArgType>
inline FirstArgType min_va(const FirstArgType& arg_0, 
	const SecondArgType& arg_1)
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

template<typename FirstArgType, typename SecondArgType, 
	typename... RemainingTypes>
inline FirstArgType min_va(const FirstArgType& arg_0, 
	const SecondArgType& arg_1, RemainingTypes... remaining_args )
{
	return min_va(min_va(arg_0, arg_1), remaining_args...);
}


template<typename Type>
inline Type custom_abs(const Type& val)
{
	if (val < static_cast<Type>(0))
	{
		return -val;
	}
	else
	{
		return val;
	}
}


template<typename Type, size_t index>
inline void _init_array_backend(Type* all_values_arr, 
	const Type& to_copy)
{
	//asm_comment("_init_array_backend() single value");
	all_values_arr[index] = to_copy;
}

template<typename Type, size_t index, typename... RemainingTypes>
inline void _init_array_backend(Type* all_values_arr, 
	const Type& first_value, const RemainingTypes&... remaining_values)
{
	_init_array_backend<Type, index>(all_values_arr, first_value);

	_init_array_backend<Type, index + 1>(all_values_arr, 
		remaining_values...);
}

template<typename Type, typename... AllTheTypes>
inline void init_array(Type* all_values_arr, 
	const AllTheTypes&...  all_the_values)
{
	_init_array_backend<Type, 0>(all_values_arr,
		all_the_values...);
}


// This has no real reason to exist
template<typename Type>
constexpr inline bool type_is_signed()
{
	return ((Type)(-1) < (Type)(0));
}


//template<typename FirstArgType, typename SecondArgType>
//bool cmpeq_array(FirstArgType* first_arr, SecondArgType* second_arr,
//	size_t size)
//	_attribute_((noinline));
template<typename FirstArgType, typename SecondArgType>
bool cmpeq_array(FirstArgType* first_arr, SecondArgType* second_arr,
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


template<typename FirstArgType>
bool anything_matches(const FirstArgType& first_val)
{
	return false;
}

template<typename FirstArgType, typename SecondArgType,
	typename... RemArgTypes>
bool anything_matches(const FirstArgType& first_val,
	const SecondArgType& next, RemArgTypes&&... rem_args)
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
