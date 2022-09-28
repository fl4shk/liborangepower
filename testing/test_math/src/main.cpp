#include "misc_includes.hpp"
#include "test_intersect_stuff.hpp"
#include "test_vec2_func.hpp"
#include "test_lseg2_func.hpp"
#include "test_rect2_func.hpp"

int main(int argc, char** argv)
{
	//--------
	//printout("Vec2:\n");
	//test_vec2();
	//printout("\n\n");
	//--------
	//printout("LineSeg2:\n");
	//test_lseg2();
	//printout("\n\n");
	//--------
	printout("Rect2:\n");
	test_rect2();
	//--------
	//printout(Rect2<int>::build_in_grid_r2_w_end_pos
	//	(Vec2{1, 1}, Vec2{-1, -1}),
	//	"\n");
	//printout(Rect2<int>{.pos{1, 1},
	//	.size_2d{cstm_abs(Vec2<int>(-1, -1) - Vec2<int>(1, 1))}}, "\n");
	//printout(Rect2<int>{.pos{1, 1},
	//	.size_2d=(Vec2<int>(3, 3) - Vec2<int>(1, 1) + Vec2<int>(1, 1))},
	//	"\n");
	//static_assert(concepts::HasCmpLtBinop<Vec2<int>>);

	return 0;
	//--------
}
