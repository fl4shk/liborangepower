#include "misc_includes.hpp"

template<template<typename> typename UnconShapeT, typename T>
class TestPair
{
public:		// types
	using ElemT = T;
	using ShapeT = UnconShapeT<T>;
public:		// variables
	Rect2<T> rect={.pos=Vec2<T>(), .size_2d=Vec2<T>()};
	ShapeT arg;
	bool exclusive=false;
	Vec2<T> arg_padding={T(0), T(0)};
};

template<template<typename> typename UnconShapeT, typename T>
void test_intersect(const std::vector<TestPair<UnconShapeT, T>>& test_vec)
{
	for (size_t i=0; i<test_vec.size(); ++i)
	{
		const auto& item = test_vec.at(i);
		printout(i, ": ");

		const auto& hit = item.rect.intersect
		(
			item.arg,
			item.exclusive, 
			item.arg_padding
		);

		if (!hit)
		{
			printout("!hit\n");
		}
		else // if (hit)
		{
			//printout("hit: ", *hit);
			//printout("hit:\n",
			//	"\tpos: ", hit->pos, "\n",
			//	"\tnormal: ", hit->normal, "\n",
			//	"\tdelta: ", hit->delta, "\n",
			//	"\ttm: ", hit->tm, "\n");

			#define X(memb, dummy_arg) \
				"\t" #memb ": ", sconcat(hit-> memb ), "\n",
			printout("hit:\n",
				strjoin("",
					std::vector<std::string>
					({
						MEMB_LIST_SHAPE_HIT2(X)
					})));
			#undef X
		}

		//if (i + 1 < test_vec.size())
		//{
		//	printout("\n");
		//}
	}
}


int main(int argc, char** argv)
{
	//--------
	//const std::vector<TestPair<Vec2, double>> test_vec_pt
	//({
	//	{
	//		.rect{.pos{0, 0}, .size_2d{2, 2}},
	//		.arg{0, 0}, .exclusive=false,
	//		//.arg_padding{0.001, 0.001}
	//	},
	//	{.rect{.pos{-0.1, -0.1}, .size_2d{0.1, 0.1}}, .arg{0.1, 0.1}},
	//	{.rect{.pos{-0.1, -0.1}, .size_2d{0.1, 0.1}}, .arg{0, 0}},
	//	{.rect{.pos{-0.1, -0.1}, .size_2d{0.1, 0.1}}, .arg{0, 0},
	//		.exclusive=true},
	//	{.rect{.pos{0, 0}, .size_2d{1, 1}}, .arg{0.1, 0.1}},
	//	{.rect{.pos{0.0, 0.0}, .size_2d{1, 1}}, .arg{0.1, 0.1}},
	//});

	//constexpr double
	//	DIM = 3;
	//constexpr Rect2<double>
	//	RECT2_FOR_LSEG2{.pos{0.0, 0.0}, .size_2d{DIM, DIM}};
	//constexpr Vec2<double>
	//	ARG_PADDING_LSEG2
	//		//{0.1, 0.1};
	//		{0.0, 0.0};
	//const std::vector<TestPair<LineSeg2, double>> test_vec_lseg
	//({
	//	//--------
	//	{.rect=RECT2_FOR_LSEG2, .arg{.p0{0, 0}, .p1{0, DIM}},
	//		.exclusive=true},
	//	//--------
	//	{.rect=RECT2_FOR_LSEG2,
	//		//.arg{{1, 1}, {1, 0}},
	//		//.arg{{0, 0.1}, {3, 0.1}},
	//		.arg{.p0{0, 0}, .p1{DIM, 0}},
	//		.arg_padding=ARG_PADDING_LSEG2},
	//	{.rect=RECT2_FOR_LSEG2, .arg{.p0{0, 0}, .p1{0, DIM}},
	//		.arg_padding=ARG_PADDING_LSEG2},
	//	{.rect=RECT2_FOR_LSEG2, .arg{.p0{DIM, 0}, .p1{0, 0}},
	//		.arg_padding=ARG_PADDING_LSEG2},
	//	{.rect=RECT2_FOR_LSEG2, .arg{.p0{0, DIM}, .p1{0, 0}},
	//		.arg_padding=ARG_PADDING_LSEG2},
	//	////--------
	//	//{.rect=RECT2_FOR_LSEG2,
	//	//	.arg{.p0{0, DIM}, .p1{DIM, DIM}},
	//	//	.arg_padding=ARG_PADDING_LSEG2 },
	//	//{.rect=RECT2_FOR_LSEG2,
	//	//	.arg{.p0{DIM, 0}, .p1{DIM, DIM}},
	//	//	.arg_padding=ARG_PADDING_LSEG2},
	//	//{.rect=RECT2_FOR_LSEG2,
	//	//	.arg{.p0{DIM, DIM}, .p1{0, DIM}},
	//	//	.arg_padding=ARG_PADDING_LSEG2},
	//	//{.rect=RECT2_FOR_LSEG2,
	//	//	.arg{.p0{DIM, DIM}, .p1{DIM, 0}},
	//	//	.arg_padding=ARG_PADDING_LSEG2},
	//	////--------
	//	//{.rect=RECT2_FOR_LSEG2,
	//	//	.arg{.p0{DIM / 2.0, DIM / 2.0},
	//	//		.p1{DIM / 2.0, DIM / 3.0}},
	//	//	.arg_padding=ARG_PADDING_LSEG2},
	//	//{.rect=RECT2_FOR_LSEG2,
	//	//	.arg{.p0{DIM / 2.0, DIM / 2.0},
	//	//		.p1{DIM / 3.0, DIM / 2.0}},
	//	//	.arg_padding=ARG_PADDING_LSEG2},
	//	//{.rect=RECT2_FOR_LSEG2,
	//	//	.arg{.p0{DIM / 2.0, DIM / 3.0},
	//	//		.p1{DIM / 2.0, DIM / 2.0}},
	//	//	.arg_padding=ARG_PADDING_LSEG2},
	//	//{.rect=RECT2_FOR_LSEG2,
	//	//	.arg{.p0{DIM / 3.0, DIM / 2.0},
	//	//		.p1{DIM / 2.0, DIM / 2.0}},
	//	//	.arg_padding=ARG_PADDING_LSEG2},
	//	////--------
	//});

	////const std::vector<TestPair<LineSeg2, int>> test_vec_lseg
	////({
	////	{
	////		.arg{.p0{0, 0}, .p1{1, 1}},
	////		.rect{.pos{-2, -2}, .size_2d{4, 4}}
	////	},
	////});
	////--------
	////printout("Vec2:\n");
	////test_intersect(test_vec_pt);
	////printout("\n\n");

	//printout("LineSeg2:\n");
	//test_intersect(test_vec_lseg);
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

	IndCircLinkList<int> test_cll;
	//PtrCircLinkList<int> test_cll;
	test_cll.push_front(3);
	test_cll.push_back(5);
	test_cll.push_front(6);
	//const auto& test_cll
	//	//= make_ind_cll<int>(6, 3, 5);
	//	= make_ind_cll(6, 3, 5);

	printout(test_cll, "\n");
	//for (const auto& item: test_cll)
	//{
	//	printout(item, " ");
	//}

	return 0;
	//--------
}
