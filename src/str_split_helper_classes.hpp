#ifndef liborangepower_str_split_helper_classes_hpp
#define liborangepower_str_split_helper_classes_hpp

#include "misc_types.hpp"
#include "misc_defines.hpp"
#include "misc_includes.hpp"

namespace liborangepower
{

namespace strings
{

// str_type might be an std::string, an std::string_view, etc.  It just
// needs to support the at() and size() member functions, and the
// value_type, in the same way that std::string and std::string_view do.
template<typename SomeStrType>
class StrSplitHelperBase
{
public:		// typedefs
	typedef SomeStrType StrType;
	typedef typename StrType::value_type value_type;
	typedef std::pair<value_type, value_type> val_typ_pair;
	//using decay_t = typename std::decay<value_type&&>::type;

protected:		// variables
	StrType internal_to_split;
	size_t internal_line_num = 1;
	size_t internal_num_consec_backslashes = 0;

	size_t internal_prev_i;

protected:		// functions
	static inline auto make_vt_pair(const value_type& t, 
		const value_type& u)
	{
		return std::make_pair<value_type, value_type>(t, u);
	}
	static inline  auto make_vt_pair(value_type&& t, value_type&& u)
	{
		return std::make_pair<value_type, value_type>(std::move(t), 
			std::move(u));
	}

	// This function should be overrided by derived classes
	// 
	// Special characters are those that are NOT pairs, but just individual
	// characters that should become their own words.
	virtual bool to_split_at_is_indiv_word(size_t i) const = 0;
	//{
	//	//return (to_split().at(i) == ',');
	//	return false;
	//}


	// This function CAN be overrided by derived classes, but it doesn't
	// have to be
	virtual const std::vector<val_typ_pair>&
		list_of_special_endpoint_pairs() const
	{
		static const std::vector<val_typ_pair> ret
			({ make_vt_pair('"', '"') });

		//// Example of something that might be helpful for derived
		////classes:
		//ret.push_back(make_vt_pair('[', ']'));

		return ret;
	}



	bool vt_is_special_first_endpoint(const value_type& vt,
		val_typ_pair& which) const
	{
		const auto& temp = list_of_special_endpoint_pairs();

		for (auto iter : temp)
		{
			if (vt == iter.first)
			{
				which = iter;
				return true;
			}
		}

		return false;
	}
	inline bool vt_is_special_first_endpoint(const value_type& vt) const
	{
		val_typ_pair which;

		return vt_is_special_first_endpoint(vt, which);
	}

	bool vt_is_special_second_endpoint(const value_type& vt,
		val_typ_pair& which) const
	{
		const auto& temp = list_of_special_endpoint_pairs();

		for (auto iter : temp)
		{
			if (vt == iter.second)
			{
				which = iter;
				return true;
			}
		}

		return false;
	}
	inline bool vt_is_special_second_endpoint(const value_type& vt) const
	{
		val_typ_pair which;

		return vt_is_special_second_endpoint(vt, which);
	}

	bool vt_is_any_special_endpoint(const value_type& vt) const
	{
		const auto& temp = list_of_special_endpoint_pairs();

		for (auto iter : temp)
		{
			if ((vt == iter.first) || (vt == iter.second))
			{
				return true;
			}
		}

		return false;
	}

	inline bool to_split_at_is_special_first_endpoint(size_t i, 
		val_typ_pair& which) const
	{
		return vt_is_special_first_endpoint(to_split().at(i), which);
	}
	inline bool to_split_at_is_special_first_endpoint(size_t i) const
	{
		return vt_is_special_first_endpoint(to_split().at(i));
	}


	inline bool to_split_at_is_special_second_endpoint(size_t i, 
		val_typ_pair& which) const
	{
		return vt_is_special_second_endpoint(to_split().at(i), which);
	}
	inline bool to_split_at_is_special_second_endpoint(size_t i) const
	{
		return vt_is_special_second_endpoint(to_split().at(i));
	}

	inline bool to_split_at_is_any_special_endpoint(size_t i) const
	{
		return vt_is_any_special_endpoint(to_split().at(i));
	}

//public:		// functions
	inline StrSplitHelperBase()
	{
	}
	inline StrSplitHelperBase(const StrType& s_to_split)
		//: internal_to_split(s_to_split)
	{
		init(s_to_split);
	}
	inline StrSplitHelperBase(StrType&& s_to_split)
		//: internal_to_split(std::move(s_to_split))
	{
		init(std::move(s_to_split));
	}

	inline StrSplitHelperBase
		(const StrSplitHelperBase& to_copy)
	{
		*this = to_copy;
	}
	inline StrSplitHelperBase
		(StrSplitHelperBase&& to_move)
	{
		*this = std::move(to_move);
	}

	inline StrSplitHelperBase& operator = 
		(const StrSplitHelperBase& to_copy)
	{
		internal_to_split = to_copy.internal_to_split;
		internal_line_num = to_copy.internal_line_num;
		internal_num_consec_backslashes 
			= to_copy.internal_num_consec_backslashes;
		internal_prev_i = to_copy.internal_prev_i;

		return *this;
	}
	inline StrSplitHelperBase& operator = 
		(StrSplitHelperBase&& to_move)
	{
		internal_to_split = std::move(to_move.internal_to_split);
		internal_line_num = std::move(to_move.internal_line_num);
		internal_num_consec_backslashes 
			= std::move(to_move.internal_num_consec_backslashes);
		internal_prev_i = std::move(to_move.internal_prev_i);

		return *this;
	}

public:		// functions

	inline void init(const StrType& n_to_split)
	{
		internal_to_split = n_to_split;
		internal_line_num = 1;
		internal_num_consec_backslashes = 0;
	}
	inline void init(StrType&& n_to_split)
	{
		internal_to_split = std::move(n_to_split);
		internal_line_num = 1;
		internal_num_consec_backslashes = 0;
	}
	inline const StrType& to_split() const
	{
		return internal_to_split;
	}

	inline bool index_in_to_split(size_t i) const
	{
		return (i < to_split().size());
	}

	inline size_t line_num() const
	{
		return internal_line_num;
	}

	inline size_t num_consec_backslashes() const
	{
		return internal_num_consec_backslashes;
	}

	inline size_t prev_prev_i() const
	{
		return prev_i() - 1;
	}
	inline size_t prev_i() const
	{
		return internal_prev_i;
	}
	inline const value_type* prev_prev_to_split_at_ptr() const
	{
		if (prev_prev_i() == static_cast<size_t>(-1))
		{
			return NULL;
		}
		return &to_split().at(prev_prev_i());
	}
	inline const value_type& prev_prev_to_split_at() const
	{
		return *prev_prev_to_split_at_ptr();
	}
	inline const value_type* prev_to_split_at_ptr() const
	{
		if (prev_i() == static_cast<size_t>(-1))
		{
			return NULL;
		}
		return &to_split().at(prev_i());
	}
	inline const value_type& prev_to_split_at() const
	{
		return *prev_to_split_at_ptr();
	}


	inline void increment_i(size_t& i)
	{
		internal_prev_i = i;
		++i;

		if (prev_to_split_at() == '\\')
		{
			if (!prev_prev_to_split_at_ptr() 
				|| (prev_prev_to_split_at() != '\\'))
			{
				internal_num_consec_backslashes = 1;
			}
			else if (prev_prev_to_split_at_ptr()
				&& (prev_prev_to_split_at() == '\\'))
			{
				++internal_num_consec_backslashes;
			}
		}
		else
		{
			internal_num_consec_backslashes = 0;

			//if (to_split().at(i++) == '\n')
			if (prev_to_split_at() == '\n')
			{
				++internal_line_num;
			}
		}

	}

	// This function is NOT meant to be overrided by derived classes
	bool to_split_at_is_end_of_word(size_t i) const
	{
		//return (to_split_at_is_indiv_word(i)
		//	|| (to_split().at(i) == '"'));
		//return (to_split_at_is_indiv_word(i)
		//	|| to_split_at_is_any_special_endpoint(i));
		return (to_split_at_is_indiv_word(i)
			|| to_split_at_is_special_first_endpoint(i));
	}

	static inline size_t get_substr_size(const size_t start, 
		const size_t pos_after_end)
	{
		return (pos_after_end - start);
	}

	// A "word" is either a sequence of non-quote (") characters, or a
	// sequence of any non-quote (") characters enclosed within two quote
	// characters, INCLUDING the two quote characters.
	// 
	// example A, with four words:  asdf nice tutorial "asdf nice tutorial"
	// 
	// example B, with one word:  "asdf nice tutorial"
	size_t find_start_of_word(size_t& i)
	{
		internal_prev_i = -1;

		// Eat white space (nom)
		while (index_in_to_split(i) && isspace(to_split().at(i)))
		{
			increment_i(i);
		}

		return i;
	}

	virtual size_t find_pos_after_end_of_word(size_t& i)
	{
		if (index_in_to_split(i))
		{
			//show_misc_output("i:  ", i, "\n");

			val_typ_pair which;

			if (to_split_at_is_indiv_word(i))
			{
				increment_i(i);
			}
			//else if (to_split().at(i) == '"')
			//{
			//	increment_i(i);
			//	while (index_in_to_split(i) && to_split().at(i) != '"')
			//	{
			//		increment_i(i);
			//	}
			//	
			//	// The pos after end needs to be after the quote character
			//	// because both the starting and ending quote characters
			//	// are considered part of the so-called "word"
			//	if (index_in_to_split(i))
			//	{
			//		increment_i(i);
			//	}
			//}
			else if (to_split_at_is_special_first_endpoint(i, which))
			{
				increment_i(i);

				while (index_in_to_split(i) 
					&& (to_split().at(i) != which.second))
				{
					increment_i(i);
				}

				// The pos after end needs to be after the quote character
				// because both the starting and ending quote characters
				// are considered part of the so-called "word"
				if (index_in_to_split(i))
				{
					increment_i(i);
				}
			}
			else
			{
				increment_i(i);


				while (index_in_to_split(i) && !isspace(to_split().at(i))
					&& !to_split_at_is_end_of_word(i))
				{
					increment_i(i);
				}
			}
		}

		return i;
	}

};


template<typename StrType>
class StrSplitHelperNoEscapes : public StrSplitHelperBase<StrType>
{
public:		// typedefs
	typedef StrSplitHelperBase<StrType> Base;
	typedef typename Base::value_type value_type;

public:		// functions
	inline StrSplitHelperNoEscapes()
	{
	}
	inline StrSplitHelperNoEscapes(const StrType& s_to_split)
		: Base(s_to_split)
	{
	}
	inline StrSplitHelperNoEscapes(StrType&& s_to_split)
		: Base(std::move(s_to_split))
	{
	}

	inline StrSplitHelperNoEscapes
		(const StrSplitHelperNoEscapes& to_copy)
		: Base(to_copy)
	{
	}
	inline StrSplitHelperNoEscapes
		(StrSplitHelperNoEscapes&& to_move)
		: Base(std::move(to_move))
	{
	}

	inline StrSplitHelperNoEscapes& operator = 
		(const StrSplitHelperNoEscapes& to_copy)
	{
		Base::operator = (static_cast<const Base&>(to_copy));
		return *this;
	}
	inline StrSplitHelperNoEscapes& operator = 
		(StrSplitHelperNoEscapes&& to_move)
	{
		Base::operator = (std::move(static_cast<Base&&>(to_move)));
		return *this;
	}

};



template<typename StrType>
class StrSplitHelperWithEscapes : public StrSplitHelperBase<StrType>
{
public:		// typedefs
	typedef StrSplitHelperBase<StrType> Base;
	typedef typename Base::value_type value_type;
	typedef typename Base::val_typ_pair val_typ_pair;

public:		// functions
	inline StrSplitHelperWithEscapes()
	{
	}
	inline StrSplitHelperWithEscapes(const StrType& s_to_split)
		: Base(s_to_split)
	{
	}
	inline StrSplitHelperWithEscapes(StrType&& s_to_split)
		: Base(std::move(s_to_split))
	{
	}

	inline StrSplitHelperWithEscapes
		(const StrSplitHelperWithEscapes& to_copy)
		: Base(to_copy)
	{
	}
	inline StrSplitHelperWithEscapes
		(StrSplitHelperWithEscapes&& to_move)
		: Base(std::move(to_move))
	{
	}

	inline StrSplitHelperWithEscapes& operator = 
		(const StrSplitHelperWithEscapes& to_copy)
	{
		Base::operator = (static_cast<const Base&>(to_copy));
		return *this;
	}
	inline StrSplitHelperWithEscapes& operator = 
		(StrSplitHelperWithEscapes&& to_move)
	{
		Base::operator = (std::move(static_cast<Base&&>(to_move)));
		return *this;
	}


	virtual size_t find_pos_after_end_of_word(size_t& i)
	{
		if (this->index_in_to_split(i))
		{
			val_typ_pair which;

			if (this->to_split_at_is_indiv_word(i))
			{
				this->increment_i(i);
			}
			else if (this->to_split_at_is_special_first_endpoint(i, 
				which))
			{
				this->increment_i(i);


				//if ((which.first != '"') || (which.second != '"'))
				//{
				//	while (this->index_in_to_split(i) 
				//		&& (this->to_split().at(i) != which.second))
				//	{
				//		this->increment_i(i);
				//	}
				//}
				//else // if ((which.first == '"') 
				//	// && (which.second == '"'))
				{
					while (this->index_in_to_split(i))
					{
						if ((this->to_split().at(i) == which.second)
							&& ((this->num_consec_backslashes() % 2) 
							== 0))
						{
							break;
						}

						this->increment_i(i);
					}
				}

				// The pos after end needs to be after the quote character
				// because both the starting and ending quote characters
				// are considered part of the so-called "word"
				if (this->index_in_to_split(i))
				{
					this->increment_i(i);
				}
			}
			else
			{
				this->increment_i(i);


				while (this->index_in_to_split(i) 
					&& !isspace(this->to_split().at(i))
					&& !this->to_split_at_is_end_of_word(i))
				{
					this->increment_i(i);
				}
			}
		}

		return i;
	}
};

} // namespace strings

} // namespace liborangepower

#endif		// liborangepower_str_split_helper_classes_hpp
