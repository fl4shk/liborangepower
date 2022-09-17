#include "misc_includes.hpp"

template
<
	template<typename> typename UnconShapeT,
	typename T
>
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

template
<
	template<typename> typename UnconShapeT,
	typename T
>
void test_intersect(const std::vector<TestPair<UnconShapeT, T>>& test_vec)
{
	for (size_t i=0; i<test_vec.size(); ++i)
	{
		const auto& item = test_vec.at(i);
		printout(i, ": ");

		const auto& hit = item.rect.intersect(item.arg, item.exclusive, 
			item.arg_padding);

		if (!hit)
		{
			printout("!hit\n");
		}
		else // if (hit)
		{
			//printout("hit: ", *hit);
			printout("hit:\n",
				"\tpos: ", hit->pos, "\n",
				"\tnormal: ", hit->normal, "\n",
				"\tdelta: ", hit->delta, "\n",
				"\ttm: ", hit->tm, "\n");
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
	const std::vector<TestPair<Vec2, double>> test_vec_pt
	({
		{
			.rect{.pos{0, 0}, .size_2d{2, 2}},
			.arg{0, 0},
			.exclusive=false,
			//.arg_padding{0.001, 0.001}
		},
		{
			.rect{.pos{-0.1, -0.1}, .size_2d{0.1, 0.1}},
			.arg{0.1, 0.1},
		},
		{
			.rect{.pos{-0.1, -0.1}, .size_2d{0.1, 0.1}},
			.arg{0, 0},
		},
		{
			.rect{.pos{-0.1, -0.1}, .size_2d{0.1, 0.1}},
			.arg{0, 0},
			.exclusive=true,
		},
		{
			.rect{.pos{0, 0}, .size_2d{1, 1}},
			.arg{0.1, 0.1},
		},
		{
			.rect{.pos{0.0, 0.0}, .size_2d{1, 1}},
			.arg{0.1, 0.1},
		},
	});

	const double
		test_dim = 3;
	const Rect2<double>
		test_rect2_for_lseg
		{
			.pos{0, 0},
			.size_2d{test_dim, test_dim},
		};
	const Vec2<double>
		test_arg_padding_for_lseg(0.1, 0.1);
	const std::vector<TestPair<LineSeg2, double>> test_vec_lseg
	({
		//--------
		{
			.rect=test_rect2_for_lseg,
			.arg{{0, 0}, {0, test_dim}},
			.exclusive=true,
		},
		//--------
		////--------
		//{
		//	.rect=test_rect2_for_lseg,
		//	//.arg{{1, 1}, {1, 0}},
		//	//.arg{{0, 0.1}, {3, 0.1}},
		//	.arg{{0, 0}, {test_dim, 0}},
		//	.arg_padding=test_arg_padding_for_lseg,
		//},
		//{
		//	.rect=test_rect2_for_lseg,
		//	.arg{{0, 0}, {0, test_dim}},
		//	.arg_padding=test_arg_padding_for_lseg,
		//},
		//{
		//	.rect=test_rect2_for_lseg,
		//	.arg{{test_dim, 0}, {0, 0}},
		//	.arg_padding=test_arg_padding_for_lseg,
		//},
		//{
		//	.rect=test_rect2_for_lseg,
		//	.arg{{0, test_dim}, {0, 0}},
		//	.arg_padding=test_arg_padding_for_lseg,
		//},
		////--------
		//{
		//	.rect=test_rect2_for_lseg,
		//	.arg{{0, test_dim}, {test_dim, test_dim}},
		//	.arg_padding=test_arg_padding_for_lseg,
		//},
		//{
		//	.rect=test_rect2_for_lseg,
		//	.arg{{test_dim, 0}, {test_dim, test_dim}},
		//	.arg_padding=test_arg_padding_for_lseg,
		//},
		//{
		//	.rect=test_rect2_for_lseg,
		//	.arg{{test_dim, test_dim}, {0, test_dim}},
		//	.arg_padding=test_arg_padding_for_lseg,
		//},
		//{
		//	.rect=test_rect2_for_lseg,
		//	.arg{{test_dim, test_dim}, {test_dim, 0}},
		//	.arg_padding=test_arg_padding_for_lseg,
		//},
		////--------
		//{
		//	.rect=test_rect2_for_lseg,
		//	.arg
		//	{
		//		{test_dim / 2.0, test_dim / 2.0},
		//		{test_dim / 2.0, test_dim / 3.0},
		//	},
		//	.arg_padding=test_arg_padding_for_lseg,
		//},
		//{
		//	.rect=test_rect2_for_lseg,
		//	.arg
		//	{
		//		{test_dim / 2.0, test_dim / 2.0},
		//		{test_dim / 3.0, test_dim / 2.0},
		//	},
		//	.arg_padding=test_arg_padding_for_lseg,
		//},
		//{
		//	.rect=test_rect2_for_lseg,
		//	.arg
		//	{
		//		{test_dim / 2.0, test_dim / 3.0},
		//		{test_dim / 2.0, test_dim / 2.0},
		//	},
		//	.arg_padding=test_arg_padding_for_lseg,
		//},
		//{
		//	.rect=test_rect2_for_lseg,
		//	.arg
		//	{
		//		{test_dim / 3.0, test_dim / 2.0},
		//		{test_dim / 2.0, test_dim / 2.0},
		//	},
		//	.arg_padding=test_arg_padding_for_lseg,
		//},
		////--------
	});

	//const std::vector<TestPair<LineSeg2, int>> test_vec_lseg
	//({
	//	{
	//		.arg{{0, 0}, {1, 1}},
	//		.rect{.pos{-2, -2}, .size_2d{4, 4}}
	//	},
	//});
	//--------
	//printout("Vec2:\n");
	//test_intersect(test_vec_pt);
	//printout("\n\n");

	printout("LineSeg2:\n");
	test_intersect(test_vec_lseg);
	//--------
	return 0;
	//--------
}
