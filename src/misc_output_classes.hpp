#ifndef liborangepower_misc_output_classes_hpp
#define liborangepower_misc_output_classes_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"

template< typename... arg_types >
inline void printout( arg_types&&... args );

class misc_output
{
protected:		// functions
	static inline void printout_backend()
	{
	}
	template< typename first_type, typename... rem_types >
	static void printout_backend
		( const first_type& first_val, rem_types&&... rem_args )
	{
		cout << first_val;
		printout_backend(rem_args...);
	}
	
	template< typename... arg_types >
	friend void printout( arg_types&&... args );
};


template< typename... arg_types >
void printout( arg_types&&... args )
{
	misc_output::printout_backend(args...);
}



template< typename... arg_types >
void printerr( arg_types&&... args );

class misc_error
{
protected:		// functions
	static inline void printerr_backend()
	{
	}
	template< typename first_type, typename... rem_types >
	static void printerr_backend
		( const first_type& first_val, rem_types&&... rem_args )
	{
		cerr << first_val;
		printerr_backend(rem_args...);
	}
	
	template< typename... arg_types >
	friend void printerr( arg_types&&... args );
};


template< typename... arg_types >
void printerr( arg_types&&... args )
{
	misc_error::printerr_backend(args...);
}


#endif		// liborangepower_misc_output_classes_hpp
