#ifndef src_test_funcs_hpp
#define src_test_funcs_hpp
//--------
#include "misc_includes.hpp"
//--------
template<typename PhysElTarg>
class MyHasRect2 final {
public:		// types
	using PhysElT = PhysElTarg;
public:		// variables
	Rect2<PhysElT>
		rect = {.pos=Vec2<PhysElT>(), .size_2d=Vec2<PhysElT>()};
	//int rect;
};
//void test_to_grid_ind();
void test_enc_rect2s();
void test_to_grid_ind_rect2();
void test_main();
//--------
#endif		// src_test_funcs_hpp
