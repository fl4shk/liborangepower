#ifndef liborangepower_str_split_helper_class_hpp
#define liborangepower_str_split_helper_class_hpp

#include "misc_types.hpp"
#include "misc_defines.hpp"
#include "misc_includes.hpp"

// str_type might be an std::string, an std::string_view, etc.  It just
// needs to support the at() and size() member functions in the same way
// that std::string and std::string_view do.
template< typename str_type >
class str_split_helper
{
protected:		// variables
	str_type internal_to_split;
	size_t internal_line_num = 0;
	
protected:		// functions
	// This function should be overrided by derived classes
	virtual bool to_split_at_is_special_char( size_t i ) const
	{
		//return ( to_split().at(i) == ',' );
		return false;
	}
	
public:		// functions
	inline str_split_helper( const str_type& s_to_split )
		: internal_to_split(s_to_split)
	{
	}
	inline str_split_helper( str_type&& s_to_split )
		: internal_to_split(std::move(s_to_split))
	{
	}
	
	inline str_split_helper( const str_split_helper& to_copy )
	{
		*this = to_copy;
	}
	inline str_split_helper( str_split_helper&& to_move )
	{
		*this = std::move(to_move);
	}
	
	inline str_split_helper& operator = ( const str_split_helper& to_copy )
	{
		internal_to_split = to_copy.internal_to_split;
		internal_line_num = to_copy.internal_line_num;
		
		return *this;
	}
	inline str_split_helper& operator = ( str_split_helper&& to_move )
	{
		internal_to_split = std::move(to_move.internal_to_split);
		internal_line_num = std::move(to_move.internal_line_num);
		
		return *this;
	}
	
	inline bool index_in_to_split( size_t i ) const
	{
		return ( i < to_split().size() );
	}
	
	inline const str_type& to_split() const
	{
		return internal_to_split;
	}
	
	inline size_t line_num() const
	{
		return internal_line_num;
	}
	
	inline void increment_i( size_t& i )
	{
		if ( to_split().at(i++) == '\n' )
		{
			++internal_line_num;
		}
	}
	
	// This function is NOT meant to be overrided by derived classes
	bool to_split_at_is_end_of_word( size_t i ) const
	{
		return ( to_split_at_is_special_char(i)
			|| ( to_split().at(i) == '"' ) );
	}
	
	// A "word" is either a sequence of non-quote (") characters, or a
	// sequence of any non-quote (") characters enclosed within two quote
	// characters, INCLUDING the two quote characters.
	// 
	// example A, with four words:  asdf nice tutorial "asdf nice tutorial"
	// 
	// example B, with one word:  "asdf nice tutorial"
	// 
	// There is no escape character.
	size_t find_start_of_word( size_t& i )
	{
		// Eat white space (nom)
		while ( index_in_to_split(i) && isspace(to_split().at(i)) )
		{
			//++i;
			increment_i(i);
		}
		return i;
	}
	
	size_t find_pos_after_end_of_word( size_t& i )
	{
		if ( index_in_to_split(i) )
		{
			// Handle special characters
			if ( to_split_at_is_special_char(i) )
			{
				//++i;
				increment_i(i);
			}
			else if ( to_split().at(i) == '"' )
			{
				//++i;
				increment_i(i);
				while ( index_in_to_split(i) && to_split().at(i) != '"' )
				{
					//++i;
					increment_i(i);
				}
				
				// The pos after end needs to be after the quote character
				// because both the starting and ending quote characters
				// are considered part of the so-called "word"
				if ( index_in_to_split(i) )
				{
					//++i;
					increment_i(i);
				}
			}
			else
			{
				//++i;
				increment_i(i);
				
				
				while ( index_in_to_split(i) && !isspace(to_split().at(i))
					&& !to_split_at_is_end_of_word(i) )
				{
					//++i;
					increment_i(i);
				}
			}
		}
		
		return i;
	}
	
};


#endif		// liborangepower_str_split_helper_class_hpp
