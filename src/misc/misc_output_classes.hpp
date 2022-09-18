#ifndef liborangepower_misc_misc_output_classes_hpp
#define liborangepower_misc_misc_output_classes_hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "../containers/std_container_id_funcs.hpp"

namespace liborangepower
{

template<typename CharT, typename Traits=std::char_traits<CharT>>
using BasOstm = std::basic_ostream<CharT, Traits>;

namespace misc_output
{

template<typename CharT, typename Traits, typename... ArgTs>
BasOstm<CharT, Traits>& osprintout(BasOstm<CharT, Traits>& os,
	ArgTs&&...  args);

class AnyPrintoutBackend
{
private:		// functions
	template<typename CharT, typename Traits, typename FirstArgT,
		typename... RemArgTs>
	static void func(BasOstm<CharT, Traits>& os, FirstArgT&& first_val,
		RemArgTs&&... rem_args)
	{
		//typedef typename std::remove_reference<decltype(first_val)>::type
		//	Temp0;
		//typedef typename std::remove_const<Temp0>::type Temp1;
		using Temp1 = std::remove_cvref_t<FirstArgT>;
		//static_assert(!(std::is_same<const std::string*, Temp1>()
		//	|| std::is_same<std::string*, Temp1>()),
		//	"Please dereference the std::string.");

		//static_assert
		//(
		//	(!concepts::IsSpecialization<Temp2, const std::basic_string*>)
		//	&& (!concepts::IsSpecialization<Temp1, std::basic_string*>),
		//	"Please dereference the `std::basic_string`."
		//);
		if constexpr (std::is_pointer<Temp1>())
		{
			using Temp2
				= std::remove_cvref_t<decltype(*std::declval<Temp1>())>;
			static_assert
			(
				!concepts::IsSpecialization<Temp2, std::basic_string>,
				"Please dereference the `std::basic_string`."
			);
			static_assert
			(
				!concepts::IsSpecialization<Temp2, std::optional>,
				"Please dereference the `std::optional`."
			);
		}

		// Decided not to use this special behavior for `std::optional`
		//if constexpr (containers::is_std_optional<Temp1>())
		//{
		//	if (first_val)
		//	{
		//		os << *first_val;
		//	}
		//	else
		//	{
		//		os << "(nullopt)";
		//	}
		//}
		//else
		{
			os << first_val;
		}

		if constexpr (sizeof...(rem_args) > 0)
		{
			func(os, rem_args...);
		}
	}

	template<typename CharT, typename Traits, typename... ArgTs>
	friend BasOstm<CharT, Traits>& osprintout(BasOstm<CharT, Traits>& os,
		ArgTs&&... args);
};

template<typename CharT, typename Traits, typename... ArgTs>
inline BasOstm<CharT, Traits>& osprintout(BasOstm<CharT, Traits>& os,
	ArgTs&&... args)
{
	AnyPrintoutBackend::func(os, args...);
	return os;
}

template<typename... ArgTs>
inline auto& printout(ArgTs&&... args)
{
	return osprintout(cout, args...);
}

template<typename... ArgTs>
inline auto& printerr(ArgTs&&... args)
{
	return osprintout(cerr, args...);
}

// Alternate name for osprintout
template<typename CharT, typename Traits, typename... ArgTs>
inline BasOstm<CharT, Traits>& fprintout(BasOstm<CharT, Traits>& out_file,
	ArgTs&&... args)
{
	return osprintout(out_file, args...);
}


template<typename CharT, typename Traits>
inline BasOstm<CharT, Traits>& osprint_hexdump(BasOstm<CharT, Traits>& os,
	const std::vector<char>& to_print, size_t line_break=8)
{
	static constexpr char BLANK_TEXT_C = '.';

	//for (const auto& c: ser_vec)
	std::vector<char> text;
	size_t i;

	auto show_text
		= [&os, &line_break, &text, &i]() -> void
	{
		osprintout(os, "  ||  ");
		for (const auto& c: text)
		{
			if (std::isprint(c))
			{
				osprintout(os, c);
			}
			else
			{
				osprintout(os, BLANK_TEXT_C);
			}
		}
		osprintout(os, "\n");
		text.resize(0);
	};

	for (i=0; i<to_print.size(); ++i)
	{
		//text += to_print.at(i);
		text.push_back(to_print.at(i));
		const uint c = to_print.at(i);
		//file.put(c);

		if (c < 0x10)
		{
			osprintout(os, 0x0);
		}
		osprintout(os, std::hex, c & 0xff, " ", std::dec);

		if (((i + 1) % line_break == 0) && (i > 0))
		{
			//osprintout(os, " ");
			show_text();
		}
	}
	if ((to_print.size() % line_break) > 0)
	{
		for (i%=line_break; i<line_break; ++i)
		{
			text.push_back(BLANK_TEXT_C);
			osprintout(os, BLANK_TEXT_C, BLANK_TEXT_C, " ");
		}
		show_text();
	}


	//if ((to_print.size() > 0) && (to_print.size() % line_break != 0))
	//{
	//	osprintout(std::cerr, "\ntestificate\n");
	//	show_text();
	//}
	//else
	//{
	//	osprintout(std::cerr, "\ntestificate\n");
	//}
	//osprintout(os, "\n");

	return os;
}

template<typename CharT, typename Traits, typename ArrT>
BasOstm<CharT, Traits>& osprint_arr(BasOstm<CharT, Traits>& os,
	ArrT* to_print, size_t size)
{
	for (size_t i=0; i<size; ++i)
	{
		osprintout(os, to_print[i]);
		if ((i + 1) < size)
		{
			osprintout(os, ", ");
		}
	}

	return os;
}
template<typename CharT, typename Traits, typename ElemT, size_t size>
BasOstm<CharT, Traits>& osprint_arr(BasOstm<CharT, Traits>& os,
	const std::array<ElemT, size>& to_print)
{
	return osprint_arr(os, to_print.data(), size);
}

} // namespace misc_output
} // namespace liborangepower


#endif		// liborangepower_misc_misc_output_classes_hpp
