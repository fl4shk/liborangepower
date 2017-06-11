#ifndef liborangepower_misc_output_classes_hpp
#define liborangepower_misc_output_classes_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"

namespace liborangepower
{


template<typename... arg_types>
void osprintout(std::ostream& os, arg_types&&... args);

class AnyPrintoutBackend
{
private:		// functions
	static inline void func(std::ostream& os)
	{
	}
	template<typename first_type, typename... rem_types>
	static void func(std::ostream& os, const first_type& first_val, 
		rem_types&&... rem_args)
	{
		os << first_val;
		func(os, rem_args...);
	}
	
	template<typename... arg_types>
	friend void osprintout(std::ostream& os, arg_types&&... args);
};

template<typename... arg_types>
void osprintout(std::ostream& os, arg_types&&... args)
{
	AnyPrintoutBackend::func(os, args...);
}

template<typename... arg_types>
void printout(arg_types&&... args)
{
	osprintout(cout, args...);
}

template<typename... arg_types>
void printerr(arg_types&&... args)
{
	osprintout(cerr, args...);
}

}


#endif		// liborangepower_misc_output_classes_hpp
