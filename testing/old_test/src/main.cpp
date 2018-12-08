#include "misc_includes.hpp"

#include "cstm_ss_helper_testing.hpp"
#include "thing_class.hpp"



extern "C"
{

static constexpr size_t some_width = 5, some_height = 6;
static constexpr size_t max_alloc_size = 1024;

u8 alloc_arr[max_alloc_size];

int test_0(int argc, char** argv);
int test_1(int argc, char** argv);
int test_2(int argc, char** argv);
int test_3(int argc, char** argv);
int test_4(int argc, char** argv);


}


int main(int argc, char** argv)
{

	//Thing* thing;

	////thing = new (&(alloc_arr[1])) Thing();
	//thing = new (alloc_arr) Thing();
	//thing->set_x(3);

	//s32 arr[some_height][some_width];
	
	//ArrayCsz2dHelper<s32, some_width, some_height> helper;

	//ArrayCsz2dHelper<s32, some_width

	//int arr[2] = {2, 7};
	//osprintout(osprint_arr(cout, arr, 2), "\n");





	//int arr0[2] = {2, 7};
	//int arr1[2] = {6, 8};

	//int arr2[2] = {9, 20};
	//int arr3[2] = {9, 20};

	//printout(cmpeq_array(arr0, arr1, 2), "\n");
	//printout(cmpeq_array(arr2, arr3, 2), "\n");
	//printout(cmpeq_array(arr2, arr2, 2), "\n");


	printout(strappcom("aaaa", 5, 6, 9, "9000"), "\n");
	printout(strappcom2("aaaa", 5, 6, 9, "9000"), "\n");

}



extern "C"
{

//int test_0(int argc, char** argv)
//{
//	//printout(liborangepower::time::now_as_ctime());
//	//printout(*std::localtime(&liborangepower::time::now_as_time_t()));
//	//printout(std::put_time(liborangepower::time::now_as_gmtime(), "%c"),
//	//	"\n");
//
//	//printout(liborangepower::time::put_now_as_localtime(), "\n");
//	//printout(liborangepower::time::put_now_as_gmtime(), "\n");
//
//	std::string temp;
//	//sconcat(temp, "aaaa", " ", "\n", "eggs", "\n", 3, "\n");
//	temp = std::move(sconcat("aaaa", " ", 3, 9, 6, 7));
//	printout(temp, "\n\n");
//
//	return 0;
//}


int test_1(int argc, char** argv)
{
	return 0;
}


int test_2(int argc, char** argv)
{
	return 0;
}

int test_3(int argc, char** argv)
{
	return 0;
}

int test_4(int argc, char** argv)
{
	return 0;
}

void __sync_synchronize()
{
}

}
