#ifndef liborangepower_strings_string_extra_stuff_hpp
#define liborangepower_strings_string_extra_stuff_hpp


#include "../misc/misc_includes.hpp"
#include <cctype>
#include <cstring>
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

inline std::vector<std::string> split_str_by_whitespace
	(const std::string& to_split)
{
	std::vector<std::string> ret;

	for (size_t i=0; i<to_split.size(); ++i)
	{
		auto c = to_split.at(i);

		// Eat whitespace
		while (std::isspace(c) && (i < to_split.size()))
		{
			++i;
			c = to_split.at(i);
		}

		bool did_first_push_back = false;

		while ((!std::isspace(c)) && (i < to_split.size()))
		{
			if (!did_first_push_back)
			{
				did_first_push_back = true;
				ret.push_back(std::string());
			}

			ret.back() += c;

			++i;
			c = to_split.at(i);
		}
	}

	return ret;
}

} // namespace strings

} // namespace liborangepower

#endif		// liborangepower_strings_string_extra_stuff_hpp
