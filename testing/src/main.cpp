#include "../liborangepower_src/misc_includes.hpp"
#include "../liborangepower_src/misc_output_classes.hpp"

#include "../liborangepower_src/range_funcs.hpp"
#include "../liborangepower_src/str_split_helper_no_escapes_class.hpp"

#include "cstm_str_split_helper_classes.hpp"


int real_main( const std::vector<std::string>& args_vec );

int main( int argc, char** argv )
{
	//return ( 9000 / 9000 ) - ( 9000 / 9000 );
	
	std::vector<std::string> args_vec;
	
	for ( int i=0; i<argc; ++i )
	{
		args_vec.push_back(argv[i]);
	}
	
	return real_main(args_vec);
}

void test_cstm_ss_helper_ne( const string_view& to_test )
{
	cstm_ss_helper_ne ss_helper(to_test);
	
	for ( size_t i=0; i<to_test.size(); ++i )
	{
		const size_t start = ss_helper.find_start_of_word(i);
		if ( i < to_test.size() )
		{
			const size_t pos_after_end 
				= ss_helper.find_pos_after_end_of_word(i);
			
			show_misc_output( to_test.substr( start, 
				ss_helper.get_substr_size( start, pos_after_end ) ),
				"\t\t" );
		}
	}
	
	show_misc_output("\n");
	
}


// This tests the str_split_helper stuff
int real_main( const std::vector<std::string>& args_vec )
{
	if ( args_vec.size() != 2 )
	{
		show_misc_error( "Usage:  ", args_vec.front(), " <some_str>\n" );
		return 1;
	}
	
	test_cstm_ss_helper_ne(string_view(args_vec.back()));
	
	
	return 0;
}
