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

template<typename FirstArgType>
inline std::string strjoin(const std::string& sep,
	const FirstArgType& first_arg)
{
	return sconcat(first_arg, sep);
}

template<typename FirstArgType, typename... RemArgTypes>
inline std::string strjoin(const std::string& sep,
	const FirstArgType& first_arg, RemArgTypes&&... rem_args)
{
	auto ret = strjoin(sep, first_arg);

	if constexpr (sizeof...(rem_args) > 0)
	{
		ret = sconcat(ret, strjoin(sep, rem_args...));
	}
	return ret;
}
template<typename ArgTypes...>
inline std::string strjoin2(const std::string& sep, ArgTypes&&... args)
{
	auto temp = strjoin(sep, args...);

	std::string ret;

	if (temp.size() > 0)
	{
		for (size_t i=0; i<temp.size() - sep.size(); ++i)
		{
			ret += temp.at(i);
		}
	}

	return ret;
}

template<typename... ArgTypes>
inline std::string strappcom(ArgTypes&&... args)
{
	return strjoin(", ", args...);
}

template<typename... ArgTypes>
inline std::string strappcom2(ArgTypes&&... args)
{
	return strjoin2(", ", args...);
}


} // namespace strings

} // namespace liborangepower

#endif		// liborangepower_strings_sconcat_etc_hpp
