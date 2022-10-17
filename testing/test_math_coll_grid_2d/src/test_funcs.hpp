#ifndef src_test_funcs_hpp
#define src_test_funcs_hpp
//--------
#include "misc_includes.hpp"
//--------
template<typename PhysElTarg>
class MyHasRect2 final {
public:		// types
	using PhysElT = PhysElTarg;
	using PhysElVec2 = Vec2<PhysElT>;
	using PhysElRect2 = Rect2<PhysElT>;
public:		// variables
	PhysElRect2
		rect{.pos=PhysElVec2(), .size_2d=PhysElVec2()};
	//int rect;
public:		// functions
	constexpr inline PhysElRect2& bbox() {
		return rect;
	}
	constexpr inline const PhysElRect2& bbox() const {
		return rect;
	}
};

//void test_to_grid_ind();
void test_enc_rect2s_and_coord_conv();
void test_to_grid_ind_rect2();
void test_main();
//--------
#endif		// src_test_funcs_hpp
