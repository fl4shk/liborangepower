#include "cstm_ss_helper_testing.hpp"

int real_main( const std::vector<std::string>& args_vec );

int main( int argc, char** argv )
{
	std::vector<std::string> args_vec;
	
	for ( int i=0; i<argc; ++i )
	{
		args_vec.push_back(argv[i]);
	}
	
	return real_main(args_vec);
}



// This tests the str_split_helper stuff
int real_main( const std::vector<std::string>& args_vec )
{
	if ( args_vec.size() != 2 )
	{
		show_misc_error( "Usage:  ", args_vec.front(), " <some_str>\n" );
		return 1;
	}
	
	//test_cstm_ss_helper_ne(string_view(args_vec.back()));
	test_cstm_ss_helper_we(string_view(args_vec.back()));
	
	
	return 0;
}
