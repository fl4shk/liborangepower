#ifndef liborangepower_misc_misc_output_classes_hpp
#define liborangepower_misc_misc_output_classes_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"

namespace liborangepower
{

namespace misc_output
{


template<typename... ArgTs>
std::ostream& osprintout(std::ostream& os, ArgTs&&... args);

class AnyPrintoutBackend
{
private:		// functions
	template<typename FirstArgT, typename... RemArgTs>
	static void func(std::ostream& os, FirstArgT&& first_val, 
		RemArgTs&&... rem_args)
	{
		typedef typename std::remove_reference<decltype(first_val)>::type
			Temp0;
		typedef typename std::remove_const<Temp0>::type Temp1;
		static_assert(!(std::is_same<const std::string*, Temp1>()
			|| std::is_same<std::string*, Temp1>()),
			"Please dereference the std::string.");
		os << first_val;

		if constexpr (sizeof...(rem_args) > 0)
		{
			func(os, rem_args...);
		}
	}

	template<typename... ArgTs>
	friend std::ostream& osprintout(std::ostream& os, 
		ArgTs&&... args);
};

template<typename... ArgTs>
inline std::ostream& osprintout(std::ostream& os, ArgTs&&... args)
{
	AnyPrintoutBackend::func(os, args...);
	return os;
}

template<typename... ArgTs>
inline std::ostream& printout(ArgTs&&... args)
{
	return osprintout(cout, args...);
}

template<typename... ArgTs>
inline std::ostream& printerr(ArgTs&&... args)
{
	return osprintout(cerr, args...);
}

// Alternate name for osprintout
template<typename... ArgTs>
inline std::ostream& fprintout(std::ostream& out_file, ArgTs&&... args)
{
	return osprintout(out_file, args...);
}





template<typename ArrT>
std::ostream& osprint_arr(std::ostream& os, ArrT* to_print, size_t size)
{
	for (size_t i=0; i<size; ++i)
	{
		osprintout(os, to_print[i]);
		if ((i + 1) < size)
		{
			osprintout(os, ", ");
		}
	}

	return os;
}

} // namespace misc_output

} // namespace liborangepower


#endif		// liborangepower_misc_misc_output_classes_hpp
