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
		GRID_ELEM_SIZE_2D{2.0, 2.0},
		ENC_PHYS_EL_RECT2_POS{-1.0, -1.0};
		//ENC_PHYS_EL_RECT2_POS{0.0, 0.0};
	static constexpr GridIndVec2
		NUM_GRID_ELEMS_2D{16, 16};
	using CollGridT
		= CollGridCsz2d<PhysElT, MyHasRect2<PhysElT>, GRID_ELEM_SIZE_2D,
			NUM_GRID_ELEMS_2D, ENC_PHYS_EL_RECT2_POS>;
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

	//std::vector<MyHasRect2<PhysElT>> temp_vec;

	//auto append = [&](
	//	const PhysElVec2& tl_corner, const PhysElVec2& br_corner
	//) -> auto& {
	//	temp_vec.push_back({PhysElRect2::build_in_grid_lim<PhysElT>
	//		(tl_corner, br_corner, temp.ENC_PHYS_EL_RECT2)});
	//	return temp_vec.back();
	//};
	auto build_temp = [&temp](
		const PhysElVec2& tl_corner, const PhysElVec2& br_corner
	) -> std::shared_ptr<MyHasRect2<PhysElT>> {
		auto ret_ptr = new MyHasRect2<PhysElT>
			(PhysElRect2::build_in_grid_lim<PhysElT>
				(tl_corner, br_corner, temp.ENC_PHYS_EL_RECT2));
		return std::shared_ptr<MyHasRect2<PhysElT>>(ret_ptr);
	};

	//std::vector<MyHasRect2<PhysElT>> temp_vec({
	//});
	std::vector<std::shared_ptr<MyHasRect2<PhysElT>>> temp_vec({
		build_temp({0, 0}, {1, 1}),
		build_temp({1, 2}, {3, 3}),
		build_temp({1, 1}, {6, 6}),
		build_temp({5, 5}, {6.1, 6.1}),
		//build_temp({6, 6}, {6, 6}),
	});
	//temp_vec.push_back(build_temp({0, 0}, {2, 2}));

	for (size_t i=0; i<temp_vec.size(); ++i) {
		temp.insert(temp_vec.at(i).get());
	}
	//--------
	auto find_index = [&temp_vec](auto* some_item, size_t i)
	-> std::optional<size_t> {
		for (size_t j=0; j<temp_vec.size(); ++j) {
			if (i != j && some_item == temp_vec.at(j).get()) {
				return j;
			}
		}
		return std::nullopt;
	};
	using TestResultSet = std::set<size_t>;
	using TestResultSetVec = std::vector<TestResultSet>;
	class CmpRet final {
	public:		// variables
		TestResultSetVec
			grid_vec,
			basic_vec;
		std::set<size_t> fail_set;
	public:		// functions
		inline bool any_fail() const {
			return (fail_set.size() > 0);
		}
	};
	auto show_all = [&temp, &temp_vec, &find_index]() -> void {
		for (size_t i=0; i<temp_vec.size(); ++i) {
			auto& temp_item = temp_vec.at(i);
			const auto& uset = temp.neighbors(temp_item.get()); 

			printout(i, ": ",
				"{", temp_item->bbox().tl_corner(), " ",
					temp_item->bbox().br_corner(), "}:\n");
			for (auto* uset_item: uset) {
				if (uset_item->bbox().intersect(temp_item->bbox())) {
					if (auto j=find_index(uset_item, i); j) {
						printout("\t", *j, ": ",
							"{", uset_item->bbox().tl_corner(), " ",
								uset_item->bbox().br_corner(), "}\n");
					}
				}
			}
		}
		printout("\n");
		for (size_t i=0; i<temp_vec.size(); ++i) {
			auto& temp_item = temp_vec.at(i);
			const auto& uset = temp.neighbors(temp_item.get()); 

			printout(i, ": ",
				"{", temp_item->bbox().tl_corner(), " ",
					temp_item->bbox().br_corner(), "}:\n");
			for (size_t j=0; j<temp_vec.size(); ++j) {
				if (i != j) {
					auto& inner_item = temp_vec.at(j);
					if (inner_item->bbox().intersect(temp_item->bbox())) {
						printout("\t", j, ": ",
							"{", inner_item->bbox().tl_corner(), " ",
								inner_item->bbox().br_corner(), "}\n");
					}
				}
			}
		}
	};

	auto compare = [&]() -> CmpRet {
		CmpRet ret
			{.grid_vec=TestResultSetVec(temp_vec.size(), TestResultSet()),
			.basic_vec=TestResultSetVec(temp_vec.size(), TestResultSet())};

		for (size_t i=0; i<temp_vec.size(); ++i) {
			auto& temp_item = temp_vec.at(i);
			const auto& uset = temp.neighbors(temp_item.get()); 
			for (size_t j=0; j<temp_vec.size(); ++j) {
				if (i != j) {
					auto& inner_item = temp_vec.at(j);
					if (inner_item->bbox().intersect(temp_item->bbox())) {
						if (uset.contains(inner_item.get())) {
							ret.grid_vec.at(i).insert(j);
						}
						ret.basic_vec.at(i).insert(j);
					}
				}
			}
			if (ret.grid_vec.at(i) != ret.basic_vec.at(i)) {
				ret.fail_set.insert(i);
			}
		}

		return ret;
	};
	auto show_if_fail = [&](const CmpRet& cmp_ret) -> bool {
		if (cmp_ret.any_fail()) {
			printout("Compare failure found!\n");
			for (const auto& fail: cmp_ret.fail_set) {
				auto& temp_item = temp_vec.at(fail);
				printout("fail:", fail, ": ",
					"{", temp_item->bbox().tl_corner(), " ",
						temp_item->bbox().br_corner(), "}:\n");

				printout("\tgrid_vec:\n");
				for (const auto& grid_ind: cmp_ret.grid_vec.at(fail)) {
					printout("\t\tgrid_ind etc: ",
						grid_ind, " ", temp_vec.size(),
						"\n");
					//auto* grid_item = &temp_vec.at(grid_ind);
					//printout("\t\t", grid_item - temp_vec.data(), ": ",
					//	"{", grid_item->bbox().tl_corner(), " ",
					//		grid_item->bbox().br_corner(), "}\n");
				}
				printout("\tbasic_vec:\n");
				for (const auto& basic_ind: cmp_ret.basic_vec.at(fail)) {
					printout("\t\tbasic_ind etc: ",
						basic_ind, " ", temp_vec.size(),
						"\n");
					//auto* basic_item = &temp_vec.at(basic_ind);
					//printout("\t\t", basic_item - temp_vec.data(), ": ",
					//	"{", basic_item->bbox().tl_corner(), " ",
					//		basic_item->bbox().br_corner(), "}\n");
				}
			}
			return true;
		} else {
			return false;
		}
	};
	auto show_fail_or_all = [&](const CmpRet& cmp_ret) -> bool {
		if (show_if_fail(cmp_ret)) {
			return true;
		} else {
			printout("No compare failure found!\n");
			show_all();
			return false;
		}
	};

	//show_all();

	//if (auto iter=temp_vec.begin() + 1; true) {
	//	//temp.erase(&(*(temp_vec.begin() + 1)));
	//	//temp_vec.erase(temp_vec.begin() + 1);
	//	temp.erase(&(*iter), std::nullopt);
	//	temp_vec.erase(iter);
	//}
	printout("Testing before `erase()`\n");
	if (auto cmp_ret=compare(); true) {
		show_fail_or_all(cmp_ret);
	}
	if (auto iter=temp_vec.begin(); true) {
		//temp.erase(&(*(temp_vec.begin() + 1)));
		//temp_vec.erase(temp_vec.begin() + 1);
		temp.erase(iter->get(), std::nullopt);
		temp_vec.erase(iter);
	}
	//printout("sizes etc: ",
	//	temp_vec.size(), " ",
	//	temp.data().size(),
	//	"\n");
	//printout("temp_vec.size(): ", temp_vec.size(), "\n");

	printout("Testing after `erase()`\n");
	if (auto cmp_ret=compare(); true) {
		show_fail_or_all(cmp_ret);
	}
	//--------
}
//--------
