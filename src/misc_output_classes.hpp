#ifndef liborangepower_misc_output_classes_hpp
#define liborangepower_misc_output_classes_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"

template< typename... arg_types >
inline void prntout( arg_types&&... args );

class misc_output
{
protected:		// functions
	static inline void prntout_backend()
	{
	}
	template< typename first_type, typename... rem_types >
	static void prntout_backend
		( const first_type& first_val, rem_types&&... rem_args )
	{
		cout << first_val;
		prntout_backend(rem_args...);
	}
	
	template< typename... arg_types >
	friend void prntout( arg_types&&... args );
};


template< typename... arg_types >
void prntout( arg_types&&... args )
{
	misc_output::prntout_backend(args...);
}



template< typename... arg_types >
void prnterr( arg_types&&... args );

class misc_error
{
protected:		// functions
	static inline void prnterr_backend()
	{
	}
	template< typename first_type, typename... rem_types >
	static void prnterr_backend
		( const first_type& first_val, rem_types&&... rem_args )
	{
		cerr << first_val;
		prnterr_backend(rem_args...);
	}
	
	template< typename... arg_types >
	friend void prnterr( arg_types&&... args );
};


template< typename... arg_types >
void prnterr( arg_types&&... args )
{
	misc_error::prnterr_backend(args...);
}


#endif		// liborangepower_misc_output_classes_hpp
