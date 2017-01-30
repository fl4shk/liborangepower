// This file is part of Lib Orange Power.
// 
// Copyright (C) 2017 Andrew Clark (FL4SHK)
// 
// Lib Orange Power is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Lib Orange Power is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
// General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with Lib Orange Power.  If not, see
// <http://www.gnu.org/licenses/>.


#ifndef misc_output_classes_hpp
#define misc_output_classes_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"

template< typename... arg_types >
inline void show_misc_output( arg_types&&... args );

class misc_output
{
protected:		// functions
	static inline void show_misc_output_backend()
	{
	}
	template< typename first_type, typename... rem_types >
	static inline void show_misc_output_backend
		( const first_type& first_val, rem_types&&... rem_args )
	{
		cout << first_val;
		show_misc_output_backend(rem_args...);
	}
	
	template< typename... arg_types >
	friend void show_misc_output( arg_types&&... args );
};


template< typename... arg_types >
inline void show_misc_output( arg_types&&... args )
{
	misc_output::show_misc_output_backend(args...);
}



template< typename... arg_types >
inline void show_misc_error( arg_types&&... args );

class misc_error
{
protected:		// functions
	static inline void show_misc_error_backend()
	{
	}
	template< typename first_type, typename... rem_types >
	static inline void show_misc_error_backend
		( const first_type& first_val, rem_types&&... rem_args )
	{
		cerr << first_val;
		show_misc_error_backend(rem_args...);
	}
	
	template< typename... arg_types >
	friend void show_misc_error( arg_types&&... args );
};


template< typename... arg_types >
inline void show_misc_error( arg_types&&... args )
{
	misc_error::show_misc_error_backend(args...);
}


#endif		// misc_output_classes_hpp
