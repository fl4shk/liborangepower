#ifndef liborangepower_strings_sconcat_etc_hpp
#define liborangepower_strings_sconcat_etc_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../misc/misc_utility_funcs.hpp"
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
//--------
inline std::stringstream inv_sconcat(const std::string& str,
	auto&... args)
{
	std::stringstream sstm;

	sstm << str;
	(sstm >> ... >> args);

	return sstm;
}
//--------
inline std::string strjoin(const std::string& sep)
{
	return std::string();
}
inline std::string strjoin(const std::string& sep, const auto& first_arg)
{
	return sconcat(first_arg, sep);
}

//inline std::string strjoin_ign_blank_str(const std::string& sep)
//{
//	return std::string();
//}
//inline std::string strjoin_ign_blank_str(const std::string& sep,
//	const auto& first_arg)
//{
//	const std::string first_arg_str = sconcat(first_arg);
//
//	if (first_arg_str.size() == 0)
//	{
//		return std::string();
//	}
//	else
//	{
//		return sconcat(first_arg_str, sep);
//	}
//}
//--------
template<size_t index, typename... ArgTs>
inline std::string _strjoin_backend(const std::string& sep,
	const std::tuple<ArgTs...>& args)
{
	constexpr auto
		args_cnt = std::tuple_size<std::remove_cvref_t<decltype(args)>>{};
	std::string ret;

	if constexpr (index < args_cnt)
	{
		ret = strjoin(sep, std::get<index>(args));

		if constexpr (index + size_t(1) < args_cnt)
		{
			ret = sconcat(ret, strjoin<index + size_t(1)>(sep, args));
		}
	}

	return ret;
}
template<typename... ArgTs>
inline std::string strjoin(const std::string& sep,
	const std::tuple<ArgTs...>& args)
{
	return _strjoin_backend<0, ArgTs...>(sep, args);
}
template<typename... ArgTs>
inline std::string strjoin2(const std::string& sep,
	const std::tuple<ArgTs...>& args)
{
	auto temp = strjoin(sep, args);

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
template<typename FirstArgT, typename... RemArgTs>
inline std::string strjoin2_rm_last(const std::string& sep,
	const std::tuple<FirstArgT, RemArgTs...>& args)
{
	//auto temp = strjoin(sep, args);

	//std::string ret;

	//if (temp.size() > 0)
	//{
	//	constexpr auto
	//		args_cnt
	//			= std::tuple_size<std::remove_cvref_t<decltype(args)>>{};

	//	for (size_t i=0;
	//		i<temp.size()
	//			- (sep.size()
	//				+ std::get<args_cnt - size_t(1)>(args).size());
	//		++i)
	//	{
	//		ret += temp.at(i);
	//	}
	//}

	//return ret;
	return strjoin2(sep, misc_util::tuple_rm_last(args));
}
//--------
inline std::string strjoin(const std::string& sep,
	const auto& first_arg, const auto&... rem_args)
{
	//auto ret = strjoin(sep, first_arg);

	//if constexpr (sizeof...(rem_args) > 0)
	//{
	//	ret = sconcat(ret, strjoin(sep, rem_args...));
	//}
	//return ret;
	return strjoin(sep, std::make_tuple(first_arg, rem_args...));
}
inline std::string strjoin2(const std::string& sep, const auto& first_arg,
	const auto&... rem_args);
{
	//auto temp = strjoin(sep, args...);

	//std::string ret;

	//if (temp.size() > 0)
	//{
	//	for (size_t i=0; i<temp.size() - sep.size(); ++i)
	//	{
	//		ret += temp.at(i);
	//	}
	//}

	//return ret;
	return strjoin2(sep, std::make_tuple(first_arg, rem_args...));
}
//--------
template<typename FirstArgT, typename... RemArgTs>
inline std::string strappcom
	(const std::tuple<FirstArgT, RemArgTs...>& args)
{
	return strjoin(", ", args);
}
template<typename FirstArgT, typename... RemArgTs>
inline std::string strappcom2
	(const std::tuple<FirstArgT, RemArgTs...>& args)
{
	return strjoin2(", ", args);
}
template<typename FirstArgT, typename... RemArgTs>
inline std::string strappcom2_rm_last
	(const std::tuple<FirstArgT, RemArgTs...>& args)
{
	return strjoin2_rm_last(", ", args);
}

inline std::string strappcom(const auto&... args)
{
	return strjoin(", ", args...);
}
inline std::string strappcom2(const auto&... args)
{
	return strjoin2(", ", args...);
}
inline std::string strappcom2_rm_last(const auto&... args)
{
	return strjoin2_rm_last(", ", args...);
}
//--------
} // namespace strings
} // namespace liborangepower

#endif		// liborangepower_strings_sconcat_etc_hpp
