#include "test_rect2_func.hpp"

void test_rect2()
{
	const std::vector<TestPair<Rect2, double>> test_vec_rect2
	({
		{.rect{.pos{0, 0}, .size_2d{2, 2}},
			.arg{.pos{-1, -1}, .size_2d{1, 1}}, .arg_padding{0.01, 0.01}}
	});
	test_intersect(test_vec_rect2);
}
