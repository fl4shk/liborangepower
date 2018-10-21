#ifndef liborangepower_misc_input_classes_hpp
#define liborangepower_misc_input_classes_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"

namespace liborangepower
{

namespace misc_input
{

inline std::string get_istream_as_str(std::istream& to_get_from)
{
	std::string ret;

	int c;
	do
	{
		c = to_get_from.get();
		if (!to_get_from.eof())
		{
			ret += c;
		}
	} while (!cin.to_get_from());

	return ret;
}

inline std::string get_stdin_as_str()
{
	return get_istream_as_str(cin);
}


} // namespace misc_input

} // namespace liborangepower



#endif		// liborangepower_misc_input_classes_hpp
