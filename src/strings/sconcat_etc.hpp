#ifndef liborangepower_strings_sconcat_etc_hpp
#define liborangepower_strings_sconcat_etc_hpp

#include "../misc/misc_types.hpp"
#include "../misc/misc_includes.hpp"
#include "../misc/misc_output_classes.hpp"

namespace liborangepower
{

namespace strings
{

template<typename FirstArgType, typename... RemArgTypes>
std::string sconcat(const FirstArgType& first_arg, 
	RemArgTypes&&... rem_args)
{
	std::string ret;
	std::stringstream sstm;
	
	misc_output::osprintout(sstm, first_arg, rem_args...);

	while (!sstm.eof())
	{
		char c = sstm.get();

		if (!sstm.eof())
		{
			ret += c;
		}
	}

	return ret;
}

inline std::string strjoin(const std::string& sep)
{
	return std::string();
}

template<typename FirstArgType, typename... RemArgTypes>
inline std::string strjoin(const std::string& sep,
	const FirstArgType& first_arg, RemArgTypes&&... rem_args)
{
	std::string ret = sconcat(first_arg, sep);

	if constexpr (sizeof...(rem_args) > 0)
	{
		return sconcat(ret, strjoin(sep, rem_args...));
	}
}

template<typename... ArgTypes>
inline std::string strappcom(ArgTypes&&... args)
{
	return sconcat(strjoin(", ", args...), ", ");
}

template<typename... ArgTypes>
inline std::string strappcom2(ArgTypes&&... args)
{
	return sconcat(strjoin(", ", args...));
}


} // namespace strings

} // namespace liborangepower

#endif		// liborangepower_strings_sconcat_etc_hpp
