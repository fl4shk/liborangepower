#ifndef cstm_ss_helper_classes_hpp
#define cstm_ss_helper_classes_hpp

#include "liborangepower_src/str_split_helper_classes.hpp"

using namespace liborangepower::strings;

#include <experimental/string_view>
typedef std::experimental::string_view string_view;


class CstmSSHelperNE : public StrSplitHelperNoEscapes<string_view>
{
public:		// typedefs
	typedef StrSplitHelperNoEscapes<string_view> base;


protected:		// functions

	virtual bool to_split_at_is_indiv_word(size_t i) const
	{
		return (this->to_split().at(i) == ',');
	}

public:		// functions
	inline CstmSSHelperNE(const string_view& s_to_split)
		: base(s_to_split)
	{
	}
	inline CstmSSHelperNE(string_view&& s_to_split)
		: base(std::move(s_to_split))
	{
	}

	inline CstmSSHelperNE(const CstmSSHelperNE& to_copy)
		: base(to_copy)
	{
	}
	inline CstmSSHelperNE(CstmSSHelperNE&& to_move)
		: base(std::move(to_move))
	{
	}

	inline CstmSSHelperNE& operator = 
		(const CstmSSHelperNE& to_copy)
	{
		base::operator = (to_copy);
		return *this;
	}
	inline CstmSSHelperNE& operator = 
		(CstmSSHelperNE&& to_move)
	{
		base::operator = (std::move(to_move));
		return *this;
	}



};

class CstmSSHelperWE : public StrSplitHelperWithEscapes<string_view>
{
public:		// typedefs
	typedef StrSplitHelperWithEscapes<string_view> base;


protected:		// functions

	virtual bool to_split_at_is_indiv_word(size_t i) const
	{
		return (base::to_split().at(i) == ',');
	}

public:		// functions
	inline CstmSSHelperWE(const string_view& s_to_split)
		: base(s_to_split)
	{
	}
	inline CstmSSHelperWE(string_view&& s_to_split)
		: base(std::move(s_to_split))
	{
	}

	inline CstmSSHelperWE(const CstmSSHelperWE& to_copy)
		: base(to_copy)
	{
	}
	inline CstmSSHelperWE(CstmSSHelperWE&& to_move)
		: base(std::move(to_move))
	{
	}

	inline CstmSSHelperWE& operator = 
		(const CstmSSHelperWE& to_copy)
	{
		base::operator = (to_copy);
		return *this;
	}
	inline CstmSSHelperWE& operator = 
		(CstmSSHelperWE&& to_move)
	{
		base::operator = (std::move(to_move));
		return *this;
	}



};


#endif		// cstm_ss_helper_classes_hpp
