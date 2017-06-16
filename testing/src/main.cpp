#include "cstm_ss_helper_testing.hpp"
#include "liborangepower_src/time_stuff.hpp"

#include <iomanip>

#include <sstream>



int main(int argc, char** argv)
{
	//printout(liborangepower::time::now_as_ctime());
	//printout(*std::localtime(&liborangepower::time::now_as_time_t()));
	//printout(std::put_time(liborangepower::time::now_as_gmtime(), "%c"),
	//	"\n");

	//printout(liborangepower::time::put_now_as_localtime(), "\n");
	//printout(liborangepower::time::put_now_as_gmtime(), "\n");

	std::string temp;
	//sconcat(temp, "aaaa", " ", "\n", "eggs", "\n", 3, "\n");
	temp = std::move(sconcat("aaaa", " ", 3, 9, 6, 7));
	printout(temp, "\n\n");
	
}
