#ifndef src_test_funcs_hpp
#define src_test_funcs_hpp

// src/test_funcs.hpp

#include "misc_includes.hpp"
//--------
using IntVec2 = math::Vec2<i32>;
using IntLineSeg2 = math::LineSeg2<i32>;
using IntTri2 = math::Tri2<i32>;
using IntRect2 = math::Rect2<i32>;

static constexpr IntRect2
	PFIELD_R2{.pos={0, 0}, .size_2d={20, 10}};

using PfieldT = std::vector<std::vector<char>>;
inline PfieldT build_pfield() {
	return PfieldT(PFIELD_R2.size_2d.y,
		std::vector<char>(PFIELD_R2.size_2d.x, '.'));
}

void print_pfield(const PfieldT& pfield);
bool plot_in_pfield(PfieldT& pfield, const IntVec2& pos);

IntVec2 rand_pt(pcg32& rng);
IntLineSeg2 rand_line_seg2(pcg32& rng);
IntTri2 rand_tri2(pcg32& rng);
void test_line(pcg32& rng);
void test_tri2(pcg32& rng);



#endif		// src_test_funcs_hpp
