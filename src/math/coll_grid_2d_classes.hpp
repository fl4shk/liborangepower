#ifndef liborangepower_math_coll_grid_2d_classes_hpp
#define liborangepower_math_coll_grid_2d_classes_hpp

#include "shape_2d_classes.hpp"

namespace liborangepower
{
namespace math
{
//--------
// A grid for doing cheaper collision checking in 2D, with constant sizes

template<typename T, Vec2<T> _GRID_ELEM_SIZE_2D,
	Vec2<size_t> _NUM_GRID_ELEMS_2D,
	template<typename> typename _Alloc=std::allocator>
class CollGridCsz2d
{
public:		// types
	using ElemT = T;

	template<typename OtherT>
	using Alloc = _Alloc<OtherT>;

	// An index into the grid
	using GridInd = size_t;
	using GridIndPt2 = Vec2<GridInd>;
	using GridIndRect2 = Rect2<GridInd>;
	//using GridIndVec = std::vector<GridIndPt2, Alloc<GridIndPt2>>;
	//using GridIndV2d = std::vector<GridIndVec, Alloc<GridIndVec>>;

	//using R2Vec = std::vector<Rect2<T>, Alloc<Rect<T>>>;
	//using R2V2d = std::vector<R2Vec, Alloc>;

	//template<CanRect2Intersect<T> ShapeT>
	//using IntersectShapeVec = std::vector<ShapeT, Alloc<ShapeT>>;
	//template<CanRect2IntersectFancy<T> ShapeT>
	//using IntersectFancyShapeVec = std::vector<ShapeT, Alloc<ShapeT>>;

public:		// constants
	static constexpr Vec2<T>
		GRID_ELEM_SIZE_2D = _GRID_ELEM_SIZE_2D;
	static constexpr GridIndPt2
		NUM_GRID_ELEMS_2D = _NUM_GRID_ELEMS_2D;
	static constexpr size_t
		TOTAL_NUM_ELEMS = NUM_GRID_ELEMS_2D.x * NUM_GRID_ELEMS_2D.y;
public:		// functions
	static constexpr Vec2<T> grid_ind_to_phys_ind
		(const GridIndPt2& some_grid_index)
	{
		return Vec2<T>(T(GRID_ELEM_SIZE_2D.x * some_grid_index.x),
			T(GRID_ELEM_SIZE_2D.y * some_grid_index.y));
	}
	//static constexpr Vec2<T> phys_index_to_grid_index
	//	(const Vec2<T>& some_phys_index)
public:		// constants
	static constexpr Rect2<T>
		ENCLOSING_PHYS_RECT2{.pos{.x=T(0), .y=T(0)},
			.size_2d=grid_ind_to_phys_ind(NUM_GRID_ELEMS_2D)};
protected:		// variables
	//Vec2<T>
	//	elem_size_2d = {T(0), T(0)};
	//GridIndPt2
	//	grid_size_2d = GridIndPt2(0, 0);
	//R2PtrVecA2d _data;
public:		// functions
	//--------
	//template<CanRect2Intersect<T> ShapeT>
	//static GridIndV2d grid_indices
	//	(const std::vector<ShapeT, Alloc<ShapeT>>& arg_vec)
	//{
	//}

	static constexpr inline GridIndPt2 grid_ind_pt2(const Vec2<T>& arg)
	{
		return GridIndPt2(arg.x / GRID_ELEM_SIZE_2D.x,
			arg.y / GRID_ELEM_SIZE_2D.y);
	}

	static constexpr inline GridIndRect2 grid_ind_rect2
		(const Rect2<T>& arg)
	{
		GridIndRect2 ret;

		//if (ENCLOSING_PHYS_RECT2.intersect(arg))
		//{
		//	//for (GridInd i=0;)
		//}
		ret = GridIndRect2::build_in_grid_w_end_pos_lim
			(arg.tl_corner(), arg.br_corner(), ENCLOSING_PHYS_RECT2);

		return ret;
		//return GridIndRect2::build_in_grid_w_end_pos_lim
		//	();
	}

	//template<CanRect2IntersectFancy<T> ShapeT>
	//static GridIndV2d grid_indices_fancy
	//	(const IntersectFancyShapeVec<ShapeT>& shape_vec,
	//	const Vec2<T>& arg_padding=Vec2<T>());

	//static GridIndRect2 grid_indices_fancy(const Rect2<T>& arg,
	//	const Vec2<T>& arg_padding=Vec2<T>())
	//{
	//	GridIndVec ret;

	//	if (ENCLOSING_PHYS_RECT2.intersect_fancy(arg, arg_padding))
	//	{
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
