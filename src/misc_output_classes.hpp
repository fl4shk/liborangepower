#ifndef liborangepower_misc_output_classes_hpp
#define liborangepower_misc_output_classes_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"

namespace liborangepower
{

namespace printout_etc
{


template<typename... ArgTypes>
void osprintout(std::ostream& os, ArgTypes&&... args);

class AnyPrintoutBackend
{
private:		// functions
	static inline void func(std::ostream& os)
	{
	}
	template<typename FirstType, typename... RemArgTypes>
	static void func(std::ostream& os, const FirstType& first_val, 
		RemArgTypes&&... rem_args)
	{
		os << first_val;
		func(os, rem_args...);
	}
	
	template<typename... ArgTypes>
	friend void osprintout(std::ostream& os, ArgTypes&&... args);
};

template<typename... ArgTypes>
inline void osprintout(std::ostream& os, ArgTypes&&... args)
{
	AnyPrintoutBackend::func(os, args...);
}

template<typename... ArgTypes>
inline void printout(ArgTypes&&... args)
{
	osprintout(cout, args...);
}

template<typename... ArgTypes>
inline void printerr(ArgTypes&&... args)
{
	osprintout(cerr, args...);
}

// Alternate name for osprintout
template<typename... ArgTypes>
inline void fprintout(std::ostream& out_file, ArgTypes&&... args)
{
	osprintout(out_file, args...);
}



template<typename FirstType, typename... RemArgTypes>
std::string sconcat(const FirstType& first_val, 
	RemArgTypes&&... rem_args)
{
	std::string ret;
	std::stringstream sstm;
	
	osprintout(sstm, first_val, rem_args...);

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



}

}


#endif		// liborangepower_misc_output_classes_hpp
