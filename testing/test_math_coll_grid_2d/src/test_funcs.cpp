//--------
#include "test_funcs.hpp"
//--------
using GridIndT = size_t;
using GridIndPt2 = Vec2<GridIndT>;
using GridIndRect2 = Rect2<GridIndT>;
//--------
void test_to_grid_ind() {
	//--------
	printout("test_to_grid_ind()\n");
	//--------
	using PhysElemT = double;
	using PhysPt2 = Vec2<PhysElemT>;
	//using PhysRect2 = Rect2<PhysElemT>;
	//--------
	static constexpr PhysPt2
		//GRID_ELEM_SIZE_2D{0.5, 0.5};
		GRID_ELEM_SIZE_2D{1.5, 1.0};
	static constexpr GridIndPt2
		NUM_GRID_ELEMS_2D{3, 3};

	using CollGridT
		= CollGridCsz2d<PhysElemT, GRID_ELEM_SIZE_2D, NUM_GRID_ELEMS_2D>;
	//--------
	static constexpr PhysPt2
		//INC_AMOUNT = {1.0, 1.0};
		INC_AMOUNT = {0.5, 0.5};

	//CollGridT coll_grid;
	printout("j: ");
	for (PhysElemT j=CollGridT::ENCLOSING_PHYS_RECT2.top_y();
		j<=CollGridT::ENCLOSING_PHYS_RECT2.bottom_y();
		j+=INC_AMOUNT.y) {
		printout("{",
			j, " ", CollGridT::to_grid_ind<true>(j),
			"}");
		if (j + INC_AMOUNT.y <= CollGridT::ENCLOSING_PHYS_RECT2.bottom_y())
		{
			printout(" ");
		}
		//printout("}\n");
	}
	printout("\n"
		"i: ");
	for (PhysElemT i=CollGridT::ENCLOSING_PHYS_RECT2.left_x();
		i<=CollGridT::ENCLOSING_PHYS_RECT2.right_x();
		i+=INC_AMOUNT.x) {
		//const GridIndPt2 CollGridT::to_grid_ind_pt2({i, j}, " ");
		printout("{",
			i, " ", CollGridT::to_grid_ind<false>(i),
			"}");
		if (i + INC_AMOUNT.x <= CollGridT::ENCLOSING_PHYS_RECT2.right_x())
		{
			printout(" ");
		}
	}
	printout("\n");
}
//--------
void test_to_phys_elem() {
	//--------
	printout("test_to_phys_elem():\n");
	//--------
	using PhysElemT = double;
	using PhysPt2 = Vec2<PhysElemT>;
	//using PhysRect2 = Rect2<PhysElemT>;
	//static constexpr PhysPt2
	//	//INC_AMOUNT = {1.0, 1.0};
	//	INC_AMOUNT = {0.5, 0.5};

	static constexpr PhysPt2
		//GRID_ELEM_SIZE_2D{0.5, 0.5};
		GRID_ELEM_SIZE_2D{1.5, 1.0};
	static constexpr GridIndPt2
		NUM_GRID_ELEMS_2D{3, 3};

	using CollGridT
		= CollGridCsz2d<PhysElemT, GRID_ELEM_SIZE_2D, NUM_GRID_ELEMS_2D>;

	CollGridT temp;
	printout(temp.ENCLOSING_PHYS_RECT2, "\n");
	//--------
}
//--------
void test_to_grid_ind_rect2() {
	//--------
	printout("test_to_grid_ind_rect2():\n");
	//--------
	using PhysElemT = double;
	using PhysPt2 = Vec2<PhysElemT>;
	using PhysRect2 = Rect2<PhysElemT>;
	//static constexpr PhysPt2
	//	//INC_AMOUNT = {1.0, 1.0};
	//	INC_AMOUNT = {0.5, 0.5};

	static constexpr PhysPt2
		//GRID_ELEM_SIZE_2D{0.5, 0.5};
		GRID_ELEM_SIZE_2D{1.5, 1.0};
	static constexpr GridIndPt2
		NUM_GRID_ELEMS_2D{3, 3};

	using CollGridT
		= CollGridCsz2d<PhysElemT, GRID_ELEM_SIZE_2D, NUM_GRID_ELEMS_2D>;

	const auto
		prt0 = PhysRect2::build_in_grid<PhysElemT>
			({0.5, 0.5}, {1.0, 1.5}, {0.5, 0.5});
	printout(prt0, " ",
		//prt1,
		"\n");
	//--------
}
//--------
