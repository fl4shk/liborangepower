#ifndef cstm_ss_helper_classes_hpp
#define cstm_ss_helper_classes_hpp

#include "liborangepower_src/str_split_helper_classes.hpp"

#include <experimental/string_view>
typedef std::experimental::string_view string_view;


class cstm_ss_helper_ne : public str_split_helper_no_escapes<string_view>
{
public:		// typedefs
	typedef str_split_helper_no_escapes<string_view> base;
	
	
protected:		// functions
	
	virtual bool to_split_at_is_indiv_word( size_t i ) const
	{
		return ( this->to_split().at(i) == ',' );
	}
	
public:		// functions
	inline cstm_ss_helper_ne( const string_view& s_to_split )
		: base(s_to_split)
	{
	}
	inline cstm_ss_helper_ne( string_view&& s_to_split )
		: base(std::move(s_to_split))
	{
	}
	
	inline cstm_ss_helper_ne( const cstm_ss_helper_ne& to_copy )
		: base(to_copy)
	{
	}
	inline cstm_ss_helper_ne( cstm_ss_helper_ne&& to_move )
		: base(std::move(to_move))
	{
	}
	
	inline cstm_ss_helper_ne& operator = 
		( const cstm_ss_helper_ne& to_copy )
	{
		base::operator = (to_copy);
		return *this;
	}
	inline cstm_ss_helper_ne& operator = 
		( cstm_ss_helper_ne&& to_move )
	{
		base::operator = (std::move(to_move));
		return *this;
	}
	
	
	
};

class cstm_ss_helper_we : public str_split_helper_with_escapes<string_view>
{
public:		// typedefs
	typedef str_split_helper_with_escapes<string_view> base;
	
	
protected:		// functions
	
	virtual bool to_split_at_is_indiv_word( size_t i ) const
	{
		return ( base::to_split().at(i) == ',' );
	}
	
public:		// functions
	inline cstm_ss_helper_we( const string_view& s_to_split )
		: base(s_to_split)
	{
	}
	inline cstm_ss_helper_we( string_view&& s_to_split )
		: base(std::move(s_to_split))
	{
	}
	
	inline cstm_ss_helper_we( const cstm_ss_helper_we& to_copy )
		: base(to_copy)
	{
	}
	inline cstm_ss_helper_we( cstm_ss_helper_we&& to_move )
		: base(std::move(to_move))
	{
	}
	
	inline cstm_ss_helper_we& operator = 
		( const cstm_ss_helper_we& to_copy )
	{
		base::operator = (to_copy);
		return *this;
	}
	inline cstm_ss_helper_we& operator = 
		( cstm_ss_helper_we&& to_move )
	{
		base::operator = (std::move(to_move));
		return *this;
	}
	
	
	
};


#endif		// cstm_ss_helper_classes_hpp
