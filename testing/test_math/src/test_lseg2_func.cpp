#include "test_lseg2_func.hpp"

void test_lseg2()
{
	constexpr double
		DIM = 3;
	constexpr Rect2<double>
		RECT2_FOR_LSEG2{.pos{0.0, 0.0}, .size_2d{DIM, DIM}};
	constexpr Vec2<double>
		ARG_PADDING_LSEG2
			//{0.1, 0.1};
			{0.0, 0.0};
	const std::vector<TestTuple<LineSeg2, double>> test_vec_lseg2
	({
		//--------
		{.rect=RECT2_FOR_LSEG2, .arg{.p0{0, 0}, .p1{0, DIM}}},
		//--------
		{.rect=RECT2_FOR_LSEG2,
			//.arg{{1, 1}, {1, 0}},
			//.arg{{0, 0.1}, {3, 0.1}},
			.arg{.p0{0, 0}, .p1{DIM, 0}},
			.arg_padding=ARG_PADDING_LSEG2},
		{.rect=RECT2_FOR_LSEG2, .arg{.p0{0, 0}, .p1{0, DIM}},
			.arg_padding=ARG_PADDING_LSEG2},
		{.rect=RECT2_FOR_LSEG2, .arg{.p0{DIM, 0}, .p1{0, 0}},
			.arg_padding=ARG_PADDING_LSEG2},
		{.rect=RECT2_FOR_LSEG2, .arg{.p0{0, DIM}, .p1{0, 0}},
			.arg_padding=ARG_PADDING_LSEG2},
		////--------
		//{.rect=RECT2_FOR_LSEG2,
		//	.arg{.p0{0, DIM}, .p1{DIM, DIM}},
		//	.arg_padding=ARG_PADDING_LSEG2 },
		//{.rect=RECT2_FOR_LSEG2,
		//	.arg{.p0{DIM, 0}, .p1{DIM, DIM}},
		//	.arg_padding=ARG_PADDING_LSEG2},
		//{.rect=RECT2_FOR_LSEG2,
		//	.arg{.p0{DIM, DIM}, .p1{0, DIM}},
		//	.arg_padding=ARG_PADDING_LSEG2},
		//{.rect=RECT2_FOR_LSEG2,
		//	.arg{.p0{DIM, DIM}, .p1{DIM, 0}},
		//	.arg_padding=ARG_PADDING_LSEG2},
		////--------
		//{.rect=RECT2_FOR_LSEG2,
		//	.arg{.p0{DIM / 2.0, DIM / 2.0},
		//		.p1{DIM / 2.0, DIM / 3.0}},
		//	.arg_padding=ARG_PADDING_LSEG2},
		//{.rect=RECT2_FOR_LSEG2,
		//	.arg{.p0{DIM / 2.0, DIM / 2.0},
		//		.p1{DIM / 3.0, DIM / 2.0}},
		//	.arg_padding=ARG_PADDING_LSEG2},
		//{.rect=RECT2_FOR_LSEG2,
		//	.arg{.p0{DIM / 2.0, DIM / 3.0},
		//		.p1{DIM / 2.0, DIM / 2.0}},
		//	.arg_padding=ARG_PADDING_LSEG2},
		//{.rect=RECT2_FOR_LSEG2,
		//	.arg{.p0{DIM / 3.0, DIM / 2.0},
		//		.p1{DIM / 2.0, DIM / 2.0}},
		//	.arg_padding=ARG_PADDING_LSEG2},
		////--------
	});

	//const std::vector<TestTuple<LineSeg2, int>> test_vec_lseg2
	//({
	//	{
	//		.arg{.p0{0, 0}, .p1{1, 1}},
	//		.rect{.pos{-2, -2}, .size_2d{4, 4}}
	//	},
	//});
	test_intersect(test_vec_lseg2);
}
