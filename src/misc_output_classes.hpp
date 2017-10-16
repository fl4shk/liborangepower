#ifndef liborangepower_misc_output_classes_hpp
#define liborangepower_misc_output_classes_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"

namespace liborangepower
{

namespace printout_etc
{


template<typename... ArgTypes>
std::ostream& osprintout(std::ostream& os, ArgTypes&&... args);

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
	friend std::ostream& osprintout(std::ostream& os, 
		ArgTypes&&... args);
};

template<typename... ArgTypes>
inline std::ostream& osprintout(std::ostream& os, ArgTypes&&... args)
{
	AnyPrintoutBackend::func(os, args...);
	return os;
}

template<typename... ArgTypes>
inline std::ostream& printout(ArgTypes&&... args)
{
	return osprintout(cout, args...);
}

template<typename... ArgTypes>
inline std::ostream& printerr(ArgTypes&&... args)
{
	return osprintout(cerr, args...);
}

// Alternate name for osprintout
template<typename... ArgTypes>
inline std::ostream& fprintout(std::ostream& out_file, ArgTypes&&... args)
{
	return osprintout(out_file, args...);
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


template<typename ArrType>
std::ostream& osprint_arr(std::ostream& os, ArrType* to_print, size_t size)
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


inline std::string strappcom()
{
	return std::string();
}
template<typename Type>
inline std::string strappcom(const Type& to_concat)
{
	return sconcat(to_concat, ", ");
}

template<typename FirstType, typename... RemArgTypes>
inline std::string strappcom(const FirstType& first_val,
	RemArgTypes&&... rem_args)
{
	std::string ret = std::move(strappcom(first_val));
	ret += std::move(strappcom(rem_args...));
	return ret;
}

template<typename FirstType, typename... RemArgTypes>
inline std::string strappcom2(const FirstType& first_val,
	RemArgTypes&&... rem_args)
{
	std::string ret = std::move(strappcom(first_val, rem_args...));

	ret = std::move(ret.substr(0, ret.size() - std::string(", ").size()));

	return ret;
}

}

}


#endif		// liborangepower_misc_output_classes_hpp
