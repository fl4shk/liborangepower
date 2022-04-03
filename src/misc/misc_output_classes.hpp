#ifndef liborangepower_misc_misc_output_classes_hpp
#define liborangepower_misc_misc_output_classes_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"

namespace liborangepower
{
namespace misc_output
{

template<typename... ArgTs>
std::ostream& osprintout(std::ostream& os, ArgTs&&... args);

class AnyPrintoutBackend
{
private:		// functions
	template<typename FirstArgT, typename... RemArgTs>
	static void func(std::ostream& os, FirstArgT&& first_val, 
		RemArgTs&&... rem_args)
	{
		typedef typename std::remove_reference<decltype(first_val)>::type
			Temp0;
		typedef typename std::remove_const<Temp0>::type Temp1;
		static_assert(!(std::is_same<const std::string*, Temp1>()
			|| std::is_same<std::string*, Temp1>()),
			"Please dereference the std::string.");
		os << first_val;

		if constexpr (sizeof...(rem_args) > 0)
		{
			func(os, rem_args...);
		}
	}

	template<typename... ArgTs>
	friend std::ostream& osprintout(std::ostream& os, 
		ArgTs&&... args);
};

template<typename... ArgTs>
inline std::ostream& osprintout(std::ostream& os, ArgTs&&... args)
{
	AnyPrintoutBackend::func(os, args...);
	return os;
}

template<typename... ArgTs>
inline std::ostream& printout(ArgTs&&... args)
{
	return osprintout(cout, args...);
}

template<typename... ArgTs>
inline std::ostream& printerr(ArgTs&&... args)
{
	return osprintout(cerr, args...);
}

// Alternate name for osprintout
template<typename... ArgTs>
inline std::ostream& fprintout(std::ostream& out_file, ArgTs&&... args)
{
	return osprintout(out_file, args...);
}


inline std::ostream& osprint_hexdump(std::ostream& os,
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
	osprintout(os, "\n");

	return os;
}



template<typename ArrT>
std::ostream& osprint_arr(std::ostream& os, ArrT* to_print, size_t size)
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

} // namespace misc_output
} // namespace liborangepower


#endif		// liborangepower_misc_misc_output_classes_hpp
