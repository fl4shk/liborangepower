#ifndef liborangepower_lexer_classes_hpp
#define liborangepower_lexer_classes_hpp

#include "str_split_helper_classes.hpp"


namespace liborangepower
{

//class lex_std_str_append_functor
//{
//public:		// functions
//	const std::string& operator () (std::string& s, 
//		const std::string& to_append) const
//	{
//		s += to_append;
//		return s;
//	}
//};
//
//// ssplit_helper_type is a str_split_helper of some sort
//// 
//// out_str_type is, for example, std::string (must be some kind of string
//// that supports appending to the end of it, which is specified by
//// providing a functor of type out_str_append_functor_type).
//// 
//// out_str_append_functor_type is a functor of some sort that permits
//// appending one out_str_type to another out_str_type
//template<typename ssplit_helper_type, typename out_str_type = std::string, 
//	typename out_str_append_functor_type = lex_std_str_append_functor>
//class lexer
//{
//public:		// typedefs
//	typedef typename ssplit_helper_type::str_type internal_str_type;
//	
//	
//protected:		// variables
//	ssplit_helper_type internal_ssplit_helper;
//	out_str_append_functor_type internal_append_functor;
//	
//public:		// functions
//	inline lexer()
//	{
//	}
//	inline lexer(const internal_str_type& s_to_split)
//	{
//		init(s_to_split);
//	}
//	inline lexer(internal_str_type&& s_to_split)
//	{
//		init(std::move(s_to_split));
//	}
//	
//	inline lexer& operator = (const lexer& to_copy)
//	{
//		internal_ssplit_helper = to_copy.internal_ssplit_helper;
//		return *this;
//	}
//	inline lexer& operator = (lexer&& to_move)
//	{
//		internal_ssplit_helper = std::move(to_move.internal_ssplit_helper);
//		return *this;
//	}
//	
//	
//	inline void init(const internal_str_type& s_to_split)
//	{
//		internal_ssplit_helper = s_to_split;
//	}
//	inline void init(internal_str_type&& s_to_split)
//	{
//		internal_ssplit_helper = std::move(s_to_split);
//	}
//	inline const ssplit_helper_type& ssplit_helper() const
//	{
//		return internal_ssplit_helper;
//	}
//	
//	
//};


}


#endif		// liborangepower_lexer_classes_hpp
