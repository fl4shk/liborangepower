#ifndef liborangepower_strings_string_conversion_stuff_hpp
#define liborangepower_strings_string_conversion_stuff_hpp


#include "../misc/misc_includes.hpp"

namespace liborangepower
{

namespace strings
{

template<typename Type>
inline Type convert_str_to(const std::string& to_convert)
{
	Type ret;

	std::stringstream sstm;
	sstm << to_convert;
	sstm >> ret;

	return ret;
}


} // namespace strings

} // namespace liborangepower



#endif		// liborangepower_strings_string_conversion_stuff_hpp
