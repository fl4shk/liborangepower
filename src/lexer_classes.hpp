#ifndef liborangepower_lexer_classes_hpp
#define liborangepower_lexer_classes_hpp

#include "str_split_helper_classes.hpp"

// ssplit_helper_type is 
template< typename ssplit_helper_type, typename out_str_type >
class lexer_base
{
public:		// typedefs
	typedef typename ssplit_helper_type::str_type internal_str_type;
	
	
protected:		// variables
	ssplit_helper_type internal_ssplit_helper;
	
protected:		// functions
	inline lexer_base()
	{
	}
	inline lexer_base( const internal_str_type& s_to_split )
	{
		init(s_to_split);
	}
	inline lexer_base( internal_str_type&& s_to_split )
	{
		init(std::move(s_to_split));
	}
	
	inline lexer_base& operator = ( const lexer_base& to_copy )
	{
		internal_ssplit_helper = to_copy.internal_ssplit_helper;
		return *this;
	}
	inline lexer_base& operator = ( lexer_base&& to_move )
	{
		internal_ssplit_helper = std::move(to_move.internal_ssplit_helper);
		return *this;
	}
	
	
public:		// functions
	inline void init( const internal_str_type& s_to_split )
	{
		internal_ssplit_helper = s_to_split;
	}
	inline void init( internal_str_type&& s_to_split )
	{
		internal_ssplit_helper = std::move(s_to_split);
	}
	inline const ssplit_helper_type& ssplit_helper() const
	{
		return internal_ssplit_helper;
	}
	
	
};

#endif		// liborangepower_lexer_classes_hpp
