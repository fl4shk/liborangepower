#ifndef liborangepower_math_coll_grid_2d_classes_hpp
#define liborangepower_math_coll_grid_2d_classes_hpp

#include "shape_2d_classes.hpp"

namespace liborangepower {
namespace math {
//enum class Dim2d: bool {
//	DimX = false,
//	DimY = true,
//};
//--------
// A grid for doing cheaper collision checking in 2D, with constant sizes
template<typename _PhysElemT, Vec2<_PhysElemT> _GRID_ELEM_SIZE_2D,
	Vec2<size_t> _NUM_GRID_ELEMS_2D,
	Vec2<_PhysElemT> _ENCLOSING_PHYS_RECT2_POS
		= Vec2<_PhysElemT>(_PhysElemT(0), _PhysElemT(0)),
	template<typename> typename _Alloc=std::allocator>
class CollGridCsz2d {
public:		// types
	// named after physics
	using PhysElemT = _PhysElemT;
	using PhysPt2 = Vec2<PhysElemT>;
	using PhysRect2 = Rect2<PhysElemT>;

	// An index into the grid
	using GridIndT = size_t;
	using GridIndPt2 = Vec2<GridIndT>;
	using GridIndRect2 = Rect2<GridIndT>;

	template<typename OtherT>
	using Alloc = _Alloc<OtherT>;


	//using GridIndVec = std::vector<GridIndPt2, Alloc<GridIndPt2>>;
	//using GridIndV2d = std::vector<GridIndVec, Alloc<GridIndVec>>;

	//using R2Vec = std::vector<Rect2<T>, Alloc<Rect<T>>>;
	//using R2V2d = std::vector<R2Vec, Alloc>;

	//template<CanRect2Intersect<T> ShapeT>
	//using IntersectShapeVec = std::vector<ShapeT, Alloc<ShapeT>>;
	//template<CanRect2IntersectFancy<T> ShapeT>
	//using IntersectFancyShapeVec = std::vector<ShapeT, Alloc<ShapeT>>;

public:		// constants
	static constexpr PhysPt2
		GRID_ELEM_SIZE_2D = _GRID_ELEM_SIZE_2D;
	static constexpr GridIndPt2
		NUM_GRID_ELEMS_2D = _NUM_GRID_ELEMS_2D;
	static constexpr PhysPt2
		ENCLOSING_PHYS_RECT2_POS = _ENCLOSING_PHYS_RECT2_POS;
	static constexpr size_t
		TOTAL_NUM_ELEMS = NUM_GRID_ELEMS_2D.x * NUM_GRID_ELEMS_2D.y;

	//template<bool index>
	//static constexpr PhysElemT
	//	GRID_ELEM_SIZE_1DIM = GRID_ELEM_SIZE_2D.at(index);
	// This isn't allowed at class scope
	//template<>
	//static constexpr PhysElemT
	//	GRID_ELEM_SIZE_1DIM<VERT> = GRID_ELEM_SIZE_2D.y;

	//template<bool index>
	//static constexpr GridIndT
	//	NUM_GRID_ELEMS_1DIM
	//		= NUM_GRID_ELEMS_2D.at(index);
	// This isn't allowed at class scope
	//template<>
	//static constexpr GridIndT
	//	NUM_GRID_ELEMS_1DIM<VERT> = NUM_GRID_ELEMS_2D.y;

public:		// functions
	//--------
	//template<Dim2d _DIM>
	static constexpr inline PhysElemT to_phys_elem(
		const GridIndT& to_conv, bool index
	) {
		// For power-of-two grid element sizes, this multiply should be
		// converted into a left shift (at least when optimization is
		// enabled).
		return PhysElemT(to_conv) * GRID_ELEM_SIZE_2D.at(index);
	}
	static constexpr inline PhysPt2 to_phys_pt2(
		const GridIndPt2& to_conv
	) {
		//return PhysPt2(
		//	to_phys_elem(to_conv.at(0), 0),
		//	to_phys_elem(to_conv.at(1), 1)
		//);
		PhysPt2 ret;
		for (size_t i=0; i<to_conv.size(); ++i) {
			ret.at(i) = to_phys_elem(to_conv.at(i), i);
		}
		return ret;
	}
	//--------
	//template<Dim2d _DIM>
	static constexpr inline GridIndT to_grid_ind(
		const PhysElemT& to_conv, bool index
	) {
		// For power-of-two grid element sizes, this divide should be
		// converted into a right shift (at least when optimization is
		// enabled).
		//return GridIndT(to_conv / GRID_ELEM_SIZE_1DIM<_DIM>);
		return GridIndT(to_conv / GRID_ELEM_SIZE_2D.at(index));
	}
	static constexpr inline GridIndPt2 to_grid_ind_pt2(
		const PhysPt2& to_conv
	) {
		//return GridIndPt2(
		//	to_grid_ind<Dim2d::HORIZ>(to_conv.x),
		//	to_grid_ind<Dim2d::VERT>(to_conv.y)
		//);
		GridIndPt2 ret;
		for (size_t i=0; i<to_conv.size(); ++i) {
			ret.at(i) = to_grid_ind(to_conv.at(i), i);
		}
		return ret;
	}
	//--------
public:		// constants
	static constexpr PhysRect2
		ENCLOSING_PHYS_RECT2{
			.pos=ENCLOSING_PHYS_RECT2_POS,
			.size_2d=to_phys_pt2(NUM_GRID_ELEMS_2D)
		};
	static constexpr GridIndRect2
		ENCLOSING_GRID_IND_RECT2
		= PhysRect2::build_in_grid(
			to_grid_ind(ENCLOSING_PHYS_RECT2.tl_corner()),
			to_grid_ind(ENCLOSING_PHYS_RECT2.br_corner()),
			GRID_ELEM_SIZE_2D
		);
protected:		// variables
	//Vec2<PhysElemT>
	//	elem_size_2d = {PhysElemT(0), PhysElemT(0)};
	//GridIndPt2
	//	grid_size_2d = GridIndPt2(0, 0);
	//R2PtrVecA2d _data;
public:		// functions
	//--------
	//template<CanRect2Intersect<PhysElemT> ShapeT>
	//static GridIndV2d grid_indices(
	//	const std::vector<ShapeT, Alloc<ShapeT>>& arg_vec
	//) {
	//}

	static constexpr inline GridIndRect2 to_grid_ind_rect2(
		const PhysRect2& phys_rect2
	) {
		return GridIndRect2::build_in_grid(
			to_grid_ind_pt2(phys_rect2.tl_corner()),
			to_grid_ind_pt2(phys_rect2.br_corner())
		);
	}
	static constexpr inline GridIndRect2 to_grid_ind_rect2_lim(
		const PhysRect2& phys_rect2
	) {
		//GridIndRect2 ret;

		//ret = GridIndRect2::build_in_grid_lim
		//	(arg.tl_corner(), arg.br_corner(), ENCLOSING_PHYS_RECT2);

		//return ret;
		//return GridIndRect2::build_in_grid_lim
		//	(arg.tl_corner(), arg.br_corner(), ENCLOSING_PHYS_RECT2);

		//return GridIndRect2::build_in_grid_lim
		//	(to_grid_ind_pt2(phys_rect2.tl_corner()),
		//	to_grid_ind_pt2(phys_rect2.br_corner()),
		//	GridIndRect2(ENCLOSING_PHYS_RECT2));
		return GridIndRect2::build_in_grid_lim(
			to_grid_ind_pt2(phys_rect2.tl_corner()),
			to_grid_ind_pt2(phys_rect2.br_corner()),
			ENCLOSING_GRID_IND_RECT2
		);
	}

	//template<CanRect2IntersectFancy<PhysElemT> ShapeT>
	//static GridIndV2d grid_indices_fancy(
	//	const IntersectFancyShapeVec<ShapeT>& shape_vec,
	//	const Vec2<PhysElemT>& arg_padding=Vec2<PhysElemT>()
	//);

	//static GridIndRect2 grid_indices_fancy(
	//	const Rect2<PhysElemT>& arg,
	//	const Vec2<PhysElemT>& arg_padding=Vec2<PhysElemT>()
	//) {
	//	GridIndVec ret;

	//	if (ENCLOSING_PHYS_RECT2.intersect_fancy(arg, arg_padding)) {
	//	}

	//	return ret;
	//}
	//--------
};

//template<typename T, Vec2<size_t> NUM_GRID_ELEMS_2D,
//	template<typename> typename ContnrEtcT=std::vector>
//inline ContnrEtcT<Vec2<T>> grid_intersect
//--------
} // namespace math
} // namespace liborangepower

#endif		// liborangepower_math_coll_grid_2d_classes_hpp
