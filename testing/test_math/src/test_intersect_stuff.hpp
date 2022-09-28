#ifndef src_test_intersect_stuff_hpp
#define src_test_intersect_stuff_hpp
//--------
#include "misc_includes.hpp"

template<template<typename> typename UnconShapeT, typename T>
class TestTuple
{
public:		// types
	using ElemT = T;
	using ShapeT = UnconShapeT<T>;
public:		// variables
	Rect2<T> rect={.pos=Vec2<T>(), .size_2d=Vec2<T>()};
	ShapeT arg;
	//bool exclusive=false;
	Vec2<T> arg_padding=Vec2<T>(T(0), T(0));
};

template<template<typename> typename UnconShapeT, typename T>
void test_intersect(const std::vector<TestTuple<UnconShapeT, T>>& test_vec)
{
	for (size_t i=0; i<test_vec.size(); ++i)
	{
		const auto& item = test_vec.at(i);
		printout(i, ": ");

		const auto& hit = item.rect.intersect
			(item.arg
			//item.exclusive, 
			);

		if (!hit)
		{
			printout("!hit\n");
		}
		else // if (hit)
		{
			printout("hit\n");
		}
	}
}
template<template<typename> typename UnconShapeT, typename T>
void test_intersect_fancy
	(const std::vector<TestTuple<UnconShapeT, T>>& test_vec)
{
	for (size_t i=0; i<test_vec.size(); ++i)
	{
		const auto& item = test_vec.at(i);
		printout(i, ": ");

		const auto& hit = item.rect.intersect_fancy
			(item.arg,
			//item.exclusive, 
			item.arg_padding);

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
//--------
#endif		// src_test_intersect_stuff_hpp
