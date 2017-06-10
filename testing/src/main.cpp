#include "cstm_ss_helper_testing.hpp"




int main(int argc, char** argv)
{
	std::vector<std::string> args_vec;
	
	for (int i=0; i<argc; ++i)
	{
		args_vec.push_back(argv[i]);
	}
	
	
	//// This tests the str_split_helper stuff
	//return [&args_vec]() -> int
	//{
	//	if (args_vec.size() != 2)
	//	{
	//		printerr("Usage:  ", args_vec.front(), " <some_str>\n");
	//		return 1;
	//	}
	//	
	//	//test_cstm_ss_helper_ne(string_view(args_vec.back()));
	//	test_cstm_ss_helper_we(string_view(args_vec.back()));
	//	
	//	
	//	return 0;
	//}();
	
	return [&args_vec]() -> int
	{
		static constexpr size_t max_num_args = 5;
		return 0;
	}();
	
}
