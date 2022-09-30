#include "test_vec2_func.hpp"

void test_vec2()
{
	//--------
	const std::vector<TestTuple<Vec2, double>> test_vec_pt
	({
		{
			.rect{.pos{0, 0}, .size_2d{2, 2}},
			.arg{0, 0},
			//.exclusive=false,
			//.arg_padding{0.001, 0.001}
		},
		{.rect{.pos{-0.1, -0.1}, .size_2d{0.1, 0.1}}, .arg{0.1, 0.1}},
		{.rect{.pos{-0.1, -0.1}, .size_2d{0.1, 0.1}}, .arg{0, 0}},
		//{.rect{.pos{-0.1, -0.1}, .size_2d{0.1, 0.1}}, .arg{0, 0},
		//	.exclusive=true},
		{.rect{.pos{0, 0}, .size_2d{1, 1}}, .arg{0.1, 0.1}},
		{.rect{.pos{0.0, 0.0}, .size_2d{1, 1}}, .arg{0.1, 0.1}},
	});
	test_intersect(test_vec_pt);
}
