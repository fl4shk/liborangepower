#include "cstm_ss_helper_testing.hpp"

void test_cstm_ss_helper_ne(const string_view& to_test)
{
	CstmSSHelperNE ss_helper(to_test);
	
	for (size_t i=0; i<to_test.size();)
	{
		const size_t start = ss_helper.find_start_of_word(i);
		if (i < to_test.size())
		{
			const size_t pos_after_end 
				= ss_helper.find_pos_after_end_of_word(i);
			
			//printout(to_test.substr(start, 
			//	ss_helper.get_substr_size(start, pos_after_end)),
			//	"\t\t");
			printout(start, " ", pos_after_end, "\t\t", 
				to_test.substr(start, ss_helper.get_substr_size(start, 
				pos_after_end)), "\n");
			//printout(to_test.substr(start, 
			//	ss_helper.get_substr_size(start, pos_after_end)), 
			//	"\n");
		}
	}
	
	printout("\n");
	
}


void test_cstm_ss_helper_we(const string_view& to_test)
{
	CstmSSHelperWE ss_helper(to_test);
	
	for (size_t i=0; i<to_test.size();)
	{
		const size_t start = ss_helper.find_start_of_word(i);
		if (i < to_test.size())
		{
			const size_t pos_after_end 
				= ss_helper.find_pos_after_end_of_word(i);
			
			//printout(to_test.substr(start, 
			//	ss_helper.get_substr_size(start, pos_after_end)),
			//	"\t\t");
			printout(start, " ", pos_after_end, "\t\t", 
				to_test.substr(start, ss_helper.get_substr_size(start, 
				pos_after_end)), "\n");
			//printout(to_test.substr(start, 
			//	ss_helper.get_substr_size(start, pos_after_end)), 
			//	"\n");
		}
	}
	
	printout("\n");
	
}
