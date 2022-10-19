#include "test_funcs.hpp"
//--------
void print_pfield(const PfieldT& pfield) {
	for (size_t j=0; j<pfield.size(); ++j) {
		for (size_t i=0; i<pfield.at(j).size(); ++i) {
			printout(pfield.at(j).at(i));
			if (i + size_t(1) >= pfield.at(j).size()) {
				printout("\n");
			}
		}
	}
}
bool plot_in_pfield(PfieldT& pfield, const IntVec2& pos) {
	//printout("main(): ", pos, "\n");

	if (
		pos.x < PFIELD_R2.left_x()
		|| pos.x > PFIELD_R2.right_x()
		|| pos.y < PFIELD_R2.top_y()
		|| pos.y > PFIELD_R2.bottom_y()
	) {
		return false;
	} else {
		pfield.at(pos.y).at(pos.x) = '#';
		return true;
	}
}
//--------
IntVec2 rand_pt(pcg32& rng) {
	return
		{.x=rng_run<i32>(rng, PFIELD_R2.left_x(), PFIELD_R2.right_x()),
		.y=rng_run<i32>(rng, PFIELD_R2.top_y(), PFIELD_R2.bottom_y())};
}
IntLineSeg2 rand_line_seg2(pcg32& rng) {
	const IntLineSeg2 ret{.p0=rand_pt(rng), .p1=rand_pt(rng)};
	printout("rand_line_seg2(): ", ret, "\n");
	return ret;
}
IntTri2 rand_tri2(pcg32& rng) {
	//IntTri2 ret{.p0{0, 0}, .p1{0, 0}, .p2{0, 0}};
	//while (ret.p0 == ret.p1 || ret.p1 == ret.p2 || ret.p2 == ret.p0) {
	const IntTri2 ret
		{.p0=rand_pt(rng), .p1=rand_pt(rng), .p2=rand_pt(rng)};
	//}
	//ret.p0 = {3, 3};
	//ret.p1 = {0, 3};
	//ret.p2 = {0, 0};
	//return ret;
	printout("rand_tri2(): ", ret, "\n");
	return ret;
}
//--------
void test_line(pcg32& rng) {
	PfieldT pfield(build_pfield());
	bresenham_line(rand_line_seg2(rng),
		PlotFunc<i32>([&pfield](const IntVec2& pos) -> bool {
			return plot_in_pfield(pfield, pos);
		}));
	print_pfield(pfield);
}
void test_tri2(pcg32& rng) {
	PfieldT pfield(build_pfield());
	flood_fill(rand_tri2(rng),
		PlotFunc<i32>([&pfield](const IntVec2& pos) -> bool {
			return plot_in_pfield(pfield, pos);
		}));
	print_pfield(pfield);
}
//--------
