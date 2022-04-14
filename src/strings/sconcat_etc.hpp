#ifndef liborangepower_strings_sconcat_etc_hpp
#define liborangepower_strings_sconcat_etc_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../misc/misc_output_classes.hpp"

namespace liborangepower
{
namespace strings
{
//--------
inline std::string sconcat(const auto& first_arg, const auto&... rem_args)
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

//template<typename T>
//inline T inv_sconcat(const std::string& str)
//{
//	T ret;
//
//	//if (!sstm)
//	//{
//	//	std::stringstream temp_sstm;
//	//	temp_sstm << str;
//	//	temp_sstm >> ret;
//	//}
//	//else
//	//{
//	//	(*sstm) << str;
//	//	(*sstm) >> ret;
//	//}
//
//	return ret;
//}

//class InvSconcatBackend final
//{
//private:		// functions
//	//static void func(std::stringstream& sstm, auto& first_arg,
//	//	auto&... rem_args)
//	//{
//	//	sstm >> first_arg;
//
//	//	if constexpr (sizeof...(rem_args) > 0)
//	//	{
//	//		func(sstm, rem_args...);
//	//	}
//	//}
//
//	static void func(std::stringstream& sstm, auto&... args)
//	{
//		(sstm << ... << args);
//	}
//
//	friend std::stringstream inv_sconcat(const std::string& str,
//		auto& first_arg, auto&... rem_args);
//};

inline std::stringstream inv_sconcat(const std::string& str,
	auto&... args)
{
	std::stringstream sstm;

	sstm << str;
	(sstm >> ... >> args);

	return sstm;
}

inline std::string strjoin(const std::string& sep)
{
	return std::string();
}

inline std::string strjoin(const std::string& sep, const auto& first_arg)
{
	return sconcat(first_arg, sep);
}

inline std::string strjoin(const std::string& sep,
	const auto& first_arg, const auto&... rem_args)
{
	auto ret = strjoin(sep, first_arg);

	if constexpr (sizeof...(rem_args) > 0)
	{
		ret = sconcat(ret, strjoin(sep, rem_args...));
	}
	return ret;
}
inline std::string strjoin2(const std::string& sep, const auto&... args)
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

inline std::string strappcom(const auto&... args)
{
	return strjoin(", ", args...);
}

inline std::string strappcom2(const auto&... args)
{
	return strjoin2(", ", args...);
}
//--------
} // namespace strings
} // namespace liborangepower

#endif		// liborangepower_strings_sconcat_etc_hpp
