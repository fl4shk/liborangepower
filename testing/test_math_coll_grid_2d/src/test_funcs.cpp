//--------
#include "test_funcs.hpp"
//--------
using GridIndT = i32;
using GridIndVec2 = Vec2<GridIndT>;
using GridIndRect2 = Rect2<GridIndT>;
//--------
//void test_to_grid_ind() {
//	//--------
//	printout("test_to_grid_ind()\n");
//	//--------
//	using PhysElT = double;
//	using PhysElVec2 = Vec2<PhysElT>;
//	//using PhysElRect2 = Rect2<PhysElT>;
//	//--------
//	static constexpr PhysElVec2
//		//GRID_ELEM_SIZE_2D{0.5, 0.5};
//		GRID_ELEM_SIZE_2D{1.5, 1.0};
//	static constexpr GridIndVec2
//		NUM_GRID_ELEMS_2D{3, 3};
//
//	using CollGridT
//		= CollGridCsz2d<PhysElT, MyHasRect2<PhysElT>, GRID_ELEM_SIZE_2D,
//			NUM_GRID_ELEMS_2D>;
//	//--------
//	static constexpr PhysElVec2
//		//INC_AMOUNT = {1.0, 1.0};
//		INC_AMOUNT = {0.5, 0.5};
//
//	//CollGridT coll_grid;
//	printout("j: ");
//	for (PhysElT j=CollGridT::ENC_PHYS_EL_RECT2.top_y();
//		j<=CollGridT::ENC_PHYS_EL_RECT2.bottom_y();
//		j+=INC_AMOUNT.y) {
//		printout("{",
//			j, " ", CollGridT::to_grid_ind(j, 1),
//			"}");
//		if (j + INC_AMOUNT.y <= CollGridT::ENC_PHYS_EL_RECT2.bottom_y())
//		{
//			printout(" ");
//		}
//		//printout("}\n");
//	}
//	printout("\n"
//		"i: ");
//	for (PhysElT i=CollGridT::ENC_PHYS_EL_RECT2.left_x();
//		i<=CollGridT::ENC_PHYS_EL_RECT2.right_x();
//		i+=INC_AMOUNT.x) {
//		//const GridIndVec2 CollGridT::to_grid_ind_vec2({i, j}, " ");
//		printout("{",
//			i, " ", CollGridT::to_grid_ind(i, 0),
//			"}");
//		if (i + INC_AMOUNT.x <= CollGridT::ENC_PHYS_EL_RECT2.right_x())
//		{
//			printout(" ");
//		}
//	}
//	printout("\n");
//}
//--------
//template<typename T, typename PhysElTarg>
//concept TestHasRect2
//= requires (T& obj) {
//	{ obj.rect } -> std::same_as<Rect2<PhysElTarg>&>;
//};
//template<TestHasRect2<double> T>
//class Testificate {
//};

void test_enc_rect2s_and_coord_conv() {
	//--------
	printout("test_enc_rect2s_and_coord_conv():\n");
	//--------
	using PhysElT = double;
	using PhysElVec2 = Vec2<PhysElT>;
	//using PhysElRect2 = Rect2<PhysElT>;
	//static constexpr PhysElVec2
	//	//INC_AMOUNT = {1.0, 1.0};
	//	INC_AMOUNT = {0.5, 0.5};

	static constexpr PhysElVec2
		//GRID_ELEM_SIZE_2D{0.5, 0.5};
		//GRID_ELEM_SIZE_2D{1.5, 1.25},
		GRID_ELEM_SIZE_2D{1.5, 1.5},
		//ENC_PHYS_EL_RECT2_POS{1.5, 1.5};
		ENC_PHYS_EL_RECT2_POS{1.0, 1.0};
	static constexpr GridIndVec2
		NUM_GRID_ELEMS_2D{2, 2};

	using CollGridT
		= CollGridCsz2d<PhysElT, MyHasRect2<PhysElT>, GRID_ELEM_SIZE_2D,
			NUM_GRID_ELEMS_2D, ENC_PHYS_EL_RECT2_POS>;
		//= CollGridCsz2d<MyHasRect2<double>>;
		//= CollGridCsz2d<MyHasRect2>;

	CollGridT temp;
	printout
		("ENC_PHYS_EL_RECT2{", temp.ENC_PHYS_EL_RECT2.tl_corner(), " ",
			temp.ENC_PHYS_EL_RECT2.br_corner(), "; ",
			temp.ENC_PHYS_EL_RECT2.size_2d, "}\n",
		"ENC_GRID_IND_RECT2{", temp.ENC_GRID_IND_RECT2.tl_corner(), " ",
			temp.ENC_GRID_IND_RECT2.br_corner(), "; ",
			temp.ENC_GRID_IND_RECT2.size_2d, "}\n");
	for (
		double i=temp.ENC_PHYS_EL_RECT2.left_x();
		i<=temp.ENC_PHYS_EL_RECT2.right_x() + 0.1;
		i+=0.1
	) {
		const auto grid_ind = temp.to_grid_ind(i, 0);
		printout(i, ": ",
			grid_ind, " ",
			temp.to_phys_el(grid_ind, 0), "\n");
	}
	//using MyTestificate
	//	= Testificate<MyHasRect2<double>>;
	//--------
}
//--------
//void test_to_grid_ind_rect2() {
//	//--------
//	printout("test_to_grid_ind_rect2():\n");
//	//--------
//	using PhysElT = double;
//	using PhysElVec2 = Vec2<PhysElT>;
//	using PhysElRect2 = Rect2<PhysElT>;
//	//static constexpr PhysElVec2
//	//	//INC_AMOUNT = {1.0, 1.0};
//	//	INC_AMOUNT = {0.5, 0.5};
//
//	static constexpr PhysElVec2
//		//GRID_ELEM_SIZE_2D{0.5, 0.5};
//		GRID_ELEM_SIZE_2D{1.5, 1.0};
//	static constexpr GridIndVec2
//		NUM_GRID_ELEMS_2D{3, 3};
//
//	using CollGridT
//		= CollGridCsz2d<PhysElT, MyHasRect2<PhysElT>, GRID_ELEM_SIZE_2D,
//			NUM_GRID_ELEMS_2D>;
//
//	const auto
//		prt0 = PhysElRect2::build_in_grid<PhysElT>
//			({0.5, 0.5}, {1.0, 1.5}, {0.5, 0.5});
//	printout(prt0, " ",
//		//prt1,
//		"\n");
//	//--------
//}
////--------
void test_main() {
	//--------
	printout("test_main():\n");
	//--------
	using PhysElT = double;
	using PhysElVec2 = Vec2<PhysElT>;
	using PhysElRect2 = Rect2<PhysElT>;

	static constexpr PhysElVec2
		GRID_ELEM_SIZE_2D{2.0, 2.0};
	static constexpr GridIndVec2
		NUM_GRID_ELEMS_2D{16, 16};
	using CollGridT
		= CollGridCsz2d<PhysElT, MyHasRect2<PhysElT>, GRID_ELEM_SIZE_2D,
			NUM_GRID_ELEMS_2D>;
	//--------
	//const auto
	//	prt0 = PhysElRect2::build_in_grid<PhysElT>
	//		({0.5, 0.5}, {1.0, 1.5}, {0.5, 0.5});
	//const auto
	//	grt0 = CollGridT::ENC_GRID_IND_RECT2;
	//printout
	//	("grt0{", grt0.tl_corner(GRID_ELEM_SIZE_2D), " ",
	//		grt0.br_corner(GRID_ELEM_SIZE_2D), "}",

	//	//prt1,
	//	"\n");
	//--------
	CollGridT temp;

	std::vector<MyHasRect2<PhysElT>> temp_vec;

	auto append = [&](
		const PhysElVec2& tl_corner, const PhysElVec2& br_corner
	) -> auto& {
		temp_vec.push_back({PhysElRect2::build_in_grid_lim<PhysElT>
			(tl_corner, br_corner, temp.ENC_PHYS_EL_RECT2)});
		return temp_vec.back();
	};

	append({0, 0}, {1, 1});
	append({1, 2}, {3, 3});
	append({1, 1}, {6, 6});
	append({5, 5}, {6, 6});

	//std::vector<std::set<size_t>>
	//	grid_check_vec(temp_vec.size(), std::set<size_t>()),
	//	raw_check_vec(temp_vec.size(), std::set<size_t>());

	for (size_t i=0; i<temp_vec.size(); ++i) {
		temp.insert(&temp_vec.at(i));
	}
	for (size_t i=0; i<temp_vec.size(); ++i) {
		auto& temp_item = temp_vec.at(i);
		const auto& uset = temp.find_others(&temp_item); 

		printout(i, ": ",
			"{", temp_item.rect.tl_corner(), " ",
				temp_item.rect.br_corner(), "}:\n");
		for (auto* uset_item: uset) {
			if (&temp_item != uset_item) {
				if (uset_item->rect.intersect(temp_item.rect)) {
					printout("\t", size_t(uset_item - temp_vec.data()),
						": ",
						"{", uset_item->rect.tl_corner(), " ",
							uset_item->rect.br_corner(), "}\n");
					//grid_check_vec.at(i).insert
					//	(size_t(uset_item - temp_vec.data()));
				}
			}
		}
	}
	printout("\n");
	for (size_t i=0; i<temp_vec.size(); ++i) {
		auto& temp_item = temp_vec.at(i);
		const auto& uset = temp.find_others(&temp_item); 

		printout(i, ": ",
			"{", temp_item.rect.tl_corner(), " ",
				temp_item.rect.br_corner(), "}:\n");
		for (size_t j=0; j<temp_vec.size(); ++j) {
			if (i != j) {
				auto& inner_item = temp_vec.at(j);
				if (inner_item.rect.intersect(temp_item.rect)) {
					printout("\t", j,
						": ",
						"{", inner_item.rect.tl_corner(), " ",
							inner_item.rect.br_corner(), "}\n");
				}
			}
		}
	}
	//--------
}
//--------
