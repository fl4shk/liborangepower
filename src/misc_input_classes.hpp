#ifndef liborangepower_misc_input_classes_hpp
#define liborangepower_misc_input_classes_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"

namespace liborangepower
{

namespace misc_input
{

inline std::string get_stdin_as_str()
{
	std::string ret;

	int c;
	do
	{
		c = cin.get();
		if (!cin.eof())
		{
			ret += c;
		}
	} while (!cin.eof());

	return ret;
}


}

}



#endif		// liborangepower_misc_input_classes_hpp
