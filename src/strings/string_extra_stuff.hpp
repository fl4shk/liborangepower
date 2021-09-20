#ifndef liborangepower_strings_string_extra_stuff_hpp
#define liborangepower_strings_string_extra_stuff_hpp


#include "../misc/misc_includes.hpp"
#include <cctype>
#include <libgen.h>

namespace liborangepower
{

namespace strings
{

inline std::unique_ptr<char[]> get_temp_path(const std::string& path)
{
	std::unique_ptr<char[]> temp_path(new char[path.size() + 1]);
	temp_path[path.size()] = '\0';

	for (size_t i=0; i<path.size(); ++i)
	{
		temp_path[i] = path.at(i);
	}

	return temp_path;
}

// Once I hit C++20, I should probably use std::filesystem... unless that
// exists in C++17?
inline std::string dirname(const std::string& path)
{
	std::string ret;

	auto&& temp_path = std::move(get_temp_path(path));
	auto modded_path = dirname(temp_path.get());

	for (char c=modded_path[0]; c!='\0'; ++c)
	{
		ret += c;
	}

	return ret;
}
inline std::string basename(const std::string& path)
{
	std::string ret;
	auto&& temp_path = std::move(get_temp_path(path));
	auto modded_path = basename(temp_path.get());

	for (char c=modded_path[0]; c!='\0'; ++c)
	{
		ret += c;
	}

	return ret;
}
inline std::string strip_file_ext(const std::string& path,
	size_t how_many=1)
{
	// Hopefully this won't include the ".".
	std::string ret = path.substr(0, path.rfind("."));

	if (how_many > 1)
	{
		return strip_file_ext(ret, how_many - 1);
	}

	return ret;
}

inline std::vector<std::string> split_str
	(const std::string& to_split, const std::function<int(int)>& sep_func,
	bool keep_sep=false)
{
	std::vector<std::string> ret;

	for (size_t i=0; i<to_split.size(); ++i)
	{
		auto c = to_split.at(i);

		bool did_first_push_back = false;

		std::string ret_back;

		//while (std::isspace(c) && (i < to_split.size()))
		while (sep_func(c) && (i < to_split.size()))
		{
			if (keep_sep)
			{
				if (!did_first_push_back)
				{
					did_first_push_back = true;
					ret.push_back(std::string());
				}

				ret_back += c;
			}

			++i;

			if (i < to_split.size())
			{
				c = to_split.at(i);
			}
		}

		bool do_add_to_ret_back = false;

		//while ((!std::isspace(c)) && (i < to_split.size()))
		while ((!sep_func(c)) && (i < to_split.size()))
		{
			do_add_to_ret_back = true;

			if (!did_first_push_back)
			{
				did_first_push_back = true;
				ret.push_back(std::string());
			}

			ret_back += c;

			++i;

			if (i < to_split.size())
			{
				c = to_split.at(i);
			}
		}

		if (do_add_to_ret_back)
		{
			ret.back() += ret_back;
		}
	}

	return ret;
}
inline std::vector<std::string> split_str_by_whitespace
	(const std::string& to_split, bool keep_sep=false)
{
	return split_str(to_split, static_cast<int(*)(int)>(&std::isspace),
		keep_sep);
}

inline std::vector<std::vector<std::string>> wrap_str
	(const std::string& to_wrap, const std::function<int(int)>& sep_func,
	size_t row_length, bool keep_sep=false)
{
	std::vector<std::vector<std::string>> ret;

	if (to_wrap.size() == 0)
	{
		return ret;
	}

	std::vector<std::string> split_string(split_str(to_wrap, sep_func,
		keep_sep));

	if (split_string.size() == 0)
	{
		return ret;
	}

	ret.push_back(std::vector<std::string>());

	size_t col = 0;

	bool added_str = false;

	for (size_t i=0; i<split_string.size(); ++i)
	{
		auto& s = split_string.at(i);

		col += s.size();

		if ((!added_str) && (col > row_length))
		{
			ret.push_back(std::vector<std::string>());
			col = 0;
		}

		added_str = false;

		ret.back().push_back(std::move(s));

		if (((i + 1) < split_string.size())
			&& ((col + split_string.at(i + 1).size()) > row_length))
		{
			ret.push_back(std::vector<std::string>());
			col = 0;
			added_str = true;
		}

		if ((!keep_sep) && (col > 0))
		{
			++col;
		}
	}

	return ret;
}
inline std::vector<std::vector<std::string>> wrap_str_by_whitespace
	(const std::string& to_wrap, bool keep_sep=false)
{
	return wrap_str(to_wrap, static_cast<int(*)(int)>(&std::isspace),
		keep_sep);
}

inline std::string spaces_str(size_t length)
{
	std::string ret;

	for (size_t i=0; i<length; ++i)
	{
		ret += " ";
	}

	return ret;
}

} // namespace strings

} // namespace liborangepower

#endif		// liborangepower_strings_string_extra_stuff_hpp
