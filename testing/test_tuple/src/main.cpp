#include "misc_includes.hpp"
#include "tuple_class.hpp"

template<typename CharT, typename Traits=std::char_traits<CharT>>
inline auto& test_osprintout(std::basic_ostream<CharT, Traits>& os,
	const auto&... args)
{
	(os << ... << args);

	return os;
}

int main(int argc, char** argv)
{
	//Tuple<int, int> tup(3, 5);

	Tuple<std::vector<int>, std::string> tup({3, 5}, "asdf");
	//Tuple<std::vector<int>, std::string> tup;
	//tup.mbr = {3, 5};
	//tup.mbr = 3;
	//tup.base().mbr = 5;
	//std::cout << tup.mbr << " " << tup.base().mbr << "\n";
	//printout(tup.mbr, " ", tup.base().mbr, "\n");

	for (size_t i=0; i<tup.mbr.size(); ++i)
	{
		//printout(tup.mbr.at(i), " ");

		printout(tup.mbr.at(i));
		if (i + 1 < tup.mbr.size())
		{
			printout(" ");
		}
	}
	printout("\n");

	test_osprintout(std::cout, "ghdl ", tup.base().mbr, "\n");

	return 0;
}
