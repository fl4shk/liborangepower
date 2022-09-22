#ifndef liborangepower_strings_sconcat_etc_hpp
#define liborangepower_strings_sconcat_etc_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../misc/misc_utility_funcs.hpp"
#include "../misc/misc_output_funcs.hpp"
#include "../concepts/std_container_concepts.hpp"

namespace liborangepower
{
//--------
template<typename CharT=char, typename Traits=std::char_traits<CharT>,
	typename Alloc=std::allocator<CharT>>
using BasStr = std::basic_string<CharT, Traits, Alloc>;

template<typename Alloc=std::allocator<char>>
using StrWA = BasStr<char, std::char_traits<char>, Alloc>;

template<typename CharT=char, typename Traits=std::char_traits<CharT>,
	typename Alloc=std::allocator<CharT>>
using BasSstm = std::basic_stringstream<CharT, Traits, Alloc>;

template<typename Alloc=std::allocator<char>>
using SstmWA = BasSstm<char, std::char_traits<char>, Alloc>;
//--------
namespace strings
{
//--------
template<typename Alloc=std::allocator<char>>
constexpr inline StrWA<Alloc> sconcat
	(const concepts::HasStdOstmOpLshift auto&... args)
{
	//StrWA<Alloc> ret;
	SstmWA<Alloc> sstm;
	
	//misc_output::osprintout(sstm, args...);

	//while (!sstm.eof())
	//{
	//	char c = sstm.get();

	//	if (!sstm.eof())
	//	{
	//		ret += c;
	//	}
	//}

	//return ret;

	misc_output::osprintout(sstm, args...);
	//(sstm << ... << args);
	return sstm.str();
}

template
<
	typename CharAlloc=std::allocator<char>,
	typename StrAlloc=std::allocator<StrWA<CharAlloc>>
>
constexpr inline void append_sconcat
	(std::vector<StrWA<CharAlloc>, StrAlloc>& ret,
	const concepts::HasStdOstmOpLshift auto&... args)
{
	( ret.push_back(sconcat<CharAlloc>(args)), ...);

	//if constexpr (sizeof...(rem_args) > 0)
	//{
	//	append_sconcat<ContnrEtcT, CharT, Traits, Alloc>
	//		(ret, rem_args...);
	//}
}

//template<typename T>
//inline T inv_sconcat(const StrWA<Alloc>& str)
//{
//	T ret;
//
//	//if (!sstm)
//	//{
//	//	SstmWA<Alloc> temp_sstm;
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
//	//static void func(SstmWA<Alloc>& sstm, auto& first_arg,
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
//	static void func(SstmWA<Alloc>& sstm, auto&... args)
//	{
//		(sstm << ... << args);
//	}
//
//	friend SstmWA<Alloc> inv_sconcat(const StrWA<Alloc>& str,
//		auto& first_arg, auto&... rem_args);
//};
//--------
template
<
	typename Alloc=std::allocator<char>
>
constexpr inline SstmWA<Alloc> inv_sconcat(const StrWA<Alloc>& str,
	concepts::HasStdIstmOpRshift auto&... args)
{
	SstmWA<Alloc> sstm;

	sstm << str;
	(sstm >> ... >> args);

	return sstm;
}
//--------
//template
//<
//	typename Alloc=std::allocator<CharT>
//>
//constexpr inline StrWA<Alloc> strjoin(const StrWA<Alloc>& sep)
//{
//	return StrWA<Alloc>();
//}
//template
//<
//	typename Alloc=std::allocator<CharT>
//>
//constexpr inline StrWA<Alloc> strjoin(const StrWA<Alloc>& sep,
//	const concepts::HasStdOstmOpLshift auto& first_arg)
//{
//	return sconcat<Alloc>(first_arg, sep);
//}

//constexpr inline StrWA<Alloc> strjoin_ign_blank_str(const StrWA<Alloc>& sep)
//{
//	return StrWA<Alloc>();
//}
//inline StrWA<Alloc> strjoin_ign_blank_str(const StrWA<Alloc>& sep,
//	const auto& first_arg)
//{
//	const StrWA<Alloc> first_arg_str = sconcat(first_arg);
//
//	if (first_arg_str.size() == 0)
//	{
//		return StrWA<Alloc>();
//	}
//	else
//	{
//		return sconcat(first_arg_str, sep);
//	}
//}
//--------
//template
//<
//	size_t index,
//	typename Alloc=std::allocator<char>
//>
//constexpr inline StrWA<Alloc> _strjoin2_backend_tup
//	(const StrWA<Alloc>& sep,
//	const std::tuple<concepts::HasStdOstmOpLshift auto...>& args)
//{
//	constexpr auto
//		args_cnt = std::tuple_size<std::remove_cvref_t<decltype(args)>>{};
//	StrWA<Alloc> ret;
//
//	//if constexpr (index < args_cnt)
//	//{
//	//	//ret = strjoin<Alloc>(sep, std::get<index>(args));
//	//	ret = sconcat<Alloc>(sep, std::get<index>(args));
//
//	//	if constexpr (index + size_t(1) < args_cnt)
//	//	{
//	//		ret = sconcat<Alloc>
//	//		(
//	//			ret,
//	//			_strjoin2_backend_tup<index + size_t(1), Alloc>(sep, args)
//	//		);
//	//	}
//	//}
//
//	return ret;
//}
//--------
template<typename Alloc=std::allocator<char>>
constexpr inline StrWA<Alloc> strjoin(const StrWA<Alloc>& sep,
	const concepts::HasStdOstmOpLshift auto&... args)
{
	//return sconcat<Alloc>((sconcat<Alloc>(sep, args), ...));
	StrWA<Alloc> temp;

	auto append = [&temp, &sep](const auto& test_arg) -> void
	{
		temp += sconcat<Alloc>(test_arg, sep);
	};
	( append(args), ... );
	return temp;
}
template<typename Alloc=std::allocator<char>>
constexpr inline StrWA<Alloc> strjoin(const char* sep,
	const concepts::HasStdOstmOpLshift auto&... args)
{
	return strjoin<Alloc>(StrWA<Alloc>(sep), args...);
}

template<typename Alloc=std::allocator<char>>
constexpr inline StrWA<Alloc> _strjoin2_backend(const StrWA<Alloc>& sep,
	const concepts::HasStdOstmOpLshift auto& first_arg,
	const concepts::HasStdOstmOpLshift auto&... rem_args)
{
	StrWA<Alloc> ret = sconcat<Alloc>(first_arg);

	if constexpr (sizeof...(rem_args) > 0)
	{
		ret += sconcat<Alloc>(sep,
			_strjoin2_backend<Alloc>(sep, rem_args...));
	}

	return ret;
}

template<typename Alloc=std::allocator<char>>
constexpr inline StrWA<Alloc> strjoin2(const StrWA<Alloc>& sep,
	const concepts::HasStdOstmOpLshift auto&... args)
{
	if constexpr (sizeof...(args) > 0)
	{
		return _strjoin2_backend<Alloc>(sep, args...);
	}
	else
	{
		return StrWA<Alloc>();
	}
}
template<typename Alloc=std::allocator<char>>
constexpr inline StrWA<Alloc> strjoin2(const char* sep,
	const concepts::HasStdOstmOpLshift auto&... args)
{
	return strjoin2<Alloc>(StrWA<Alloc>(sep), args...);
}
//--------
template<typename Alloc,
	concepts::HasStdOstmOpLshift... ArgTs>
constexpr inline StrWA<Alloc> strjoin(const StrWA<Alloc>& sep,
	const std::tuple<ArgTs...>& args)
{
	return std::apply
	(
		[&sep](const ArgTs&... lambda_args) -> StrWA<Alloc>
		{
			return strjoin<Alloc>(sep, lambda_args...);
		},
		args
	);
}
template<concepts::HasStdOstmOpLshift... ArgTs>
constexpr inline std::string strjoin(const char* sep,
	const std::tuple<ArgTs...>& args)
{
	return strjoin(std::string(sep), args);
}

template<typename Alloc,
	concepts::HasStdOstmOpLshift... ArgTs>
constexpr inline StrWA<Alloc> strjoin2(const StrWA<Alloc>& sep,
	const std::tuple<ArgTs...>& args)
{
	return std::apply
	(
		[&sep](const ArgTs&... lambda_args) -> StrWA<Alloc>
		{
			return strjoin2<Alloc>(sep, lambda_args...);
		},
		args
	);
}
template<concepts::HasStdOstmOpLshift... ArgTs>
constexpr inline std::string strjoin2(const char* sep,
	const std::tuple<ArgTs...>& args)
{
	return strjoin2(std::string(sep), args);
}
//--------
template<typename CharAlloc=std::allocator<char>,
	typename StrAlloc=std::allocator<StrWA<CharAlloc>>>
constexpr inline StrWA<CharAlloc> strjoin(const StrWA<CharAlloc>& sep,
	const std::vector<StrWA<CharAlloc>, StrAlloc>& args)
{
	StrWA<CharAlloc> ret;

	for (const auto& item: args)
	{
		ret += sconcat<CharAlloc>(item, sep);
	}

	return ret;
}
template<typename CharAlloc=std::allocator<char>,
	typename StrAlloc=std::allocator<StrWA<CharAlloc>>>
constexpr inline StrWA<CharAlloc> strjoin(const char* sep,
	const std::vector<StrWA<CharAlloc>, StrAlloc>& args)
{
	return strjoin<CharAlloc, StrAlloc>(StrWA<CharAlloc>(sep), args);
}

template<typename CharAlloc=std::allocator<char>,
	typename StrAlloc=std::allocator<StrWA<CharAlloc>>>
constexpr inline StrWA<CharAlloc> strjoin2(const StrWA<CharAlloc>& sep,
	const std::vector<StrWA<CharAlloc>, StrAlloc>& args)
{
	using vec_size_type
		= typename std::remove_cvref_t<decltype(args)>::size_type;
	const vec_size_type& args_cnt = args.size();

	StrWA<CharAlloc> ret;

	for (vec_size_type i=0; i<args_cnt; ++i)
	{
		ret += sconcat<CharAlloc>(args.at(i));

		if (i + vec_size_type(1) < args_cnt)
		{
			ret += sep;
		}
	}

	return ret;
}
template<typename CharAlloc=std::allocator<char>,
	typename StrAlloc=std::allocator<StrWA<CharAlloc>>>
constexpr inline StrWA<CharAlloc> strjoin2(const char* sep,
	const std::vector<StrWA<CharAlloc>, StrAlloc>& args)
{
	return strjoin2<CharAlloc, StrAlloc>(StrWA<CharAlloc>(sep), args);
}
//--------
//constexpr inline std::string strappcom
//	(const concepts::HasStdOstmOpLshift auto&... args)
//{
//	return strjoin(", ", args...);
//}
//constexpr inline std::string strappcom2
//	(const concepts::HasStdOstmOpLshift auto&... args)
//{
//	return strjoin2(", ", args...);
//}

template<typename Alloc=std::allocator<char>>
constexpr inline StrWA<Alloc> strappcom
	(const concepts::HasStdOstmOpLshift auto&... args)
{
	return strjoin<Alloc>(", ", args...);
}
template<typename Alloc=std::allocator<char>>
constexpr inline StrWA<Alloc> strappcom2
	(const concepts::HasStdOstmOpLshift auto&... args)
{
	return strjoin2<Alloc>(", ", args...);
}
//--------
} // namespace strings
} // namespace liborangepower

#endif		// liborangepower_strings_sconcat_etc_hpp
