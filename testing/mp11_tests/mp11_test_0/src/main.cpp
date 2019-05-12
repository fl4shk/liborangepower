#include "misc_includes.hpp"
#include "base_class.hpp"


typedef volatile size_t VolIdentNum;
typedef volatile const char* VolIdentName;

//VolIdentNum vol_ident_num_arr[Base::hierarchy_size];
//VolIdentName vol_ident_name_arr[Base::hierarchy_size];
VolIdentNum vol_ident_num_arr[mp_size<HierarchyList>::value];
VolIdentName vol_ident_name_arr[mp_size<HierarchyList>::value];


extern "C"
{
	void __sync_synchronize()
	{
	}
}

int main(int argc, char** argv)
{
	ASM_COMMENT("all_ident_num_arr");
	auto all_ident_num_arr = Base::all_ident_num_arr();

	ASM_COMMENT("all_ident_name_arr");
	auto all_ident_name_arr = Base::all_ident_name_arr();

	ASM_COMMENT("for");
	for (size_t i=0; i<Base::hierarchy_size; ++i)
	{
		ASM_COMMENT("Set vol_ident_num_arr");
		//vol_ident_num_arr[i] = Base::all_ident_num_arr()[i];
		vol_ident_num_arr[i] = all_ident_num_arr[i];

		ASM_COMMENT("Set vol_ident_name_arr");
		//vol_ident_name_arr[i] = Base::all_ident_name_arr()[i];
		vol_ident_name_arr[i] = all_ident_name_arr[i];
	}

	return 0;
}
