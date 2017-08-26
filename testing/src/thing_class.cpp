#include "thing_class.hpp"




Thing::Thing()
{
	printout("I have a strange need for cheese.\n");
}

void Thing::set_x(s32 n_x)
{
	x = n_x;
}

//extern "C"
//{
//	Thing* thing;
//}
