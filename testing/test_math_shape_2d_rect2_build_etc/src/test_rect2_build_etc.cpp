#include "test_rect2_build_etc.hpp"
//--------
void test_r2_fit_into_grid_lim()
{
	printout("test_r2_fit_into_grid_lim():\n");

	const std::vector<TestTupleAndRect2<int>> test_darr
	({
		{{.name="a", .p0{2, 2}, .p1{3, 3}},
			Rect2<int>{.pos{0, 0}, .size_2d{1, 1}}},
		{{.name="b", .p0{-1, -1}, .p1{1, 1}},
			Rect2<int>{.pos{0, 0}, .size_2d{1, 1}}},
		{{.name="c", .p0{-1, -1}, .p1{2, 5}},
			Rect2<int>{.pos{2, 2}, .size_2d{3, 3}}},
		{{.name="d", .p0{-1, -1}, .p1{2, 5}},
			Rect2<int>::build_in_grid(Vec2{2, 2}, Vec2{3, -3})},
	});

	for (const auto& item: test_darr)
	{
		const Rect2<int>
			uut = Rect2<int>::build_in_grid(item.first.p0, item.first.p1)
			.fit_into_grid_lim(item.second);

		printout
			(item.first.name, uut, " ", item.second, "\n",
			"\tleft_x(", uut.left_x(), ")\n",
			"\ttop_y(", uut.top_y(), ")\n",
			"\tright_x(", uut.right_x(), ")\n",
			"\tbottom_y(", uut.bottom_y(), ")\n");
	}
	printout("\n");
}
//--------
void test_r2_build_in_grid()
{
	printout("test_r2_build_in_grid():\n");

	const std::vector<TestTuple<int>> test_darr
	({
		{.name="a", .p0{0, 0}, .p1{2, 2}, .tlc{0, 0}, .brc{2, 2}},
		{.name="b", .p0{0, 1}, .p1{3, 3}, .tlc{0, 1}, .brc{3, 3}},
		{.name="c", .p0{0, 1}, .p1{1, 0}, .tlc{0, 0}, .brc{1, 1}},
		{.name="d", .p0{-1, -2}, .p1{-1, -2}, .tlc{-1, -2}, .brc{-1, -2}},
	});

	for (const auto& item: test_darr)
	{
		const Rect2<int> uut
			= Rect2<int>::build_in_grid(item.p0, item.p1);

		item.cmp_to_oracle(uut);
	}
	printout("\n");
}
//--------
void test_r2_build_in_grid_lim()
{
	printout("test_r2_build_in_grid_lim():\n");

	//const Rect2<int>
	//	lim{.pos={-1, -1}, .size_2d={20, 20}};

	const std::vector<TestTupleAndRect2<int>> test_darr
	({
		//{{.name="a", .p0{-1, -1}, .p1{21, 21}, .tlc{-1, -1}, .brc{18, 18}},
		//	{.pos{-1, -1}, .size_2d{20, 20}}},
		//{{.name="b", .p0{-1, -1}, .p1{21, 21}, .tlc{-1, -1}, .brc{-1, -1}},
		//	Rect2<int>::build_in_grid(Vec2{-1, -1}, Vec2{-1, -1})},
		//{{.name="c", .p0{2, 2}, .p1{3, 3}, .tlc{-1, -1}, .brc{1, 1}},
		//	Rect2<int>::build_in_grid(Vec2{-1, -1}, Vec2{1, 1})},
		{{.name="d", .p0{2, 2}, .p1{3, 3}, .tlc{-1, -1}, .brc{1, 1}},
			Rect2<int>{.pos{-1, -1}, .size_2d{2, 2}}},
	});

	for (const auto& item: test_darr)
	{
		const Rect2<int>
			uut = Rect2<int>::build_in_grid_lim
				(item.first.p0, item.first.p1, item.second);

		//TestTuple<int>::cmp_to_oracle(item.first, uut);
		printout
			(item.first.name, uut, "\n",
			"\tleft_x(", uut.left_x(), " ", item.first.tlc.x, ")\n",
			"\ttop_y(", uut.top_y(), " ", item.first.tlc.y, ")\n",
			"\tright_x(", uut.right_x(), " ", item.first.brc.x, ")\n",
			"\tbottom_y(", uut.bottom_y(), " ", item.first.brc.x, ")\n");
	}
	printout("\n");
}
