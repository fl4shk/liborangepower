#include "misc_includes.hpp"

template<typename T>
class TestTuple final
{
public:		// variables
	std::string name;
	Vec2<T> p0, p1, tlc, brc;
};

int main(int argc, char** argv)
{
	const std::vector<TestTuple<int>> test_vec
	({
		{.name="a", .p0{0, 0}, .p1{2, 2}, .tlc{0, 0}, .brc{2, 2}},
		{.name="b", .p0{0, 1}, .p1{3, 3}, .tlc{0, 1}, .brc{3, 3}},
		{.name="c", .p0{0, 1}, .p1{1, 0}, .tlc{0, 0}, .brc{1, 1}},
		{.name="d", .p0{-1, -2}, .p1{-1, -2}, .tlc{-1, -2}, .brc{-1, -2}},
	});

	for (const auto& item: test_vec)
	{
		const Rect2<int> uut
			= Rect2<int>::build_in_grid_w_end_pos(item.p0, item.p1);

		const bool
			tlc_eq = uut.tl_corner() == item.tlc,
			brc_eq = uut.br_corner() == item.brc;

		printout
			(item.name, uut, " "
			"(", "uut.tlc", uut.tl_corner(), " ",
				"item.tlc", item.tlc, ": ",
				(tlc_eq ? "==" : "!="), ") "
			"(", "uut.brc", uut.br_corner(), " ",
				"item.brc", item.brc, ": ",
				(brc_eq ? "==" : "!="), ") ",
			((tlc_eq && brc_eq) ? "SUCCESS" : "FAILURE"),
			"\n");
	}

	return 0;
}
