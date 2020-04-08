#ifndef liborangepower_misc_misc_input_classes_hpp
#define liborangepower_misc_misc_input_classes_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"
#include <fstream>

namespace liborangepower
{

namespace misc_input
{

inline std::string get_istream_as_str(std::istream& to_get_from)
{
	std::string ret;

	int c;
	for (;;)
	{
		c = to_get_from.get();
		if (!to_get_from.eof())
		{
			ret += c;
		}
		else // if (to_get_from.eof())
		{
			break;
		}
	}

	return ret;
}
//inline std::string get_istream_as_str(std::ifstream& to_get_from)
//{
//	std::string ret;
//
//	int c;
//	for (;;)
//	{
//		c = to_get_from.get();
//		if (!to_get_from.eof())
//		{
//			ret += c;
//		}
//		else // if (to_get_from.eof())
//		{
//			break;
//		}
//	}
//
//	return ret;
//}
inline auto get_istream_as_str(std::istream&& to_get_from)
{
	return get_istream_as_str(to_get_from);
}
//inline auto get_istream_as_str(std::ifstream&& to_get_from)
//{
//	return get_istream_as_str(to_get_from);
//}

inline std::string get_stdin_as_str()
{
	return get_istream_as_str(cin);
}


} // namespace misc_input

} // namespace liborangepower



#endif		// liborangepower_misc_miscinput_classes_hpp
