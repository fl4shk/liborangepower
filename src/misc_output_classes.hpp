#ifndef liborangepower_misc_output_classes_hpp
#define liborangepower_misc_output_classes_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"

namespace liborangepower
{

template< typename... arg_types >
inline void printout(arg_types&&... args);

class PrintoutBackend
{
private:		// functions
	static inline void func()
	{
	}
	template< typename first_type, typename... rem_types >
	static void func
		(const first_type& first_val, rem_types&&... rem_args)
	{
		cout << first_val;
		func(rem_args...);
	}
	
	template< typename... arg_types >
	friend void printout(arg_types&&... args);
};


template< typename... arg_types >
void printout(arg_types&&... args)
{
	PrintoutBackend::func(args...);
}



template< typename... arg_types >
void printerr(arg_types&&... args);

class PrinterrBackend
{
private:		// functions
	static inline void func()
	{
	}
	template< typename first_type, typename... rem_types >
	static void func
		(const first_type& first_val, rem_types&&... rem_args)
	{
		cerr << first_val;
		func(rem_args...);
	}
	
	template< typename... arg_types >
	friend void printerr(arg_types&&... args);
};


template< typename... arg_types >
void printerr(arg_types&&... args)
{
	PrinterrBackend::func(args...);
}

}


#endif		// liborangepower_misc_output_classes_hpp
