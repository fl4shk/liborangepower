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
protected:		// variables
	PhysElRect2
		_rect = {.pos=PhysElVec2(), .size_2d=PhysElVec2()};
	//int rect;
public:		// functions
	constexpr inline MyHasRect2() = default;
	constexpr inline MyHasRect2(const PhysElRect2& s_rect)
		: _rect(s_rect) {
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(MyHasRect2);
	constexpr inline ~MyHasRect2() = default;

	GEN_GETTER_AND_SETTER_BY_CON_REF(rect);
};
//void test_to_grid_ind();
void test_enc_rect2s_and_coord_conv();
void test_to_grid_ind_rect2();
void test_main();
//--------
#endif		// src_test_funcs_hpp
