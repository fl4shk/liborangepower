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
template<typename T, typename PhysElTarg>
concept HasRect2Mbr
= requires(T& obj) {
	{ obj.rect } -> std::same_as<Rect2<PhysElTarg>&>;
};
// A grid for doing cheaper collision checking in 2D, with constant sizes
template<typename PhysElTarg, HasRect2Mbr<PhysElTarg> DataElemTarg,
	Vec2<PhysElTarg> GRID_ELEM_SIZE_2D_TARG,
	Vec2<i32> NUM_GRID_ELEMS_2D_TARG,
	Vec2<PhysElTarg> ENC_PHYS_EL_RECT2_POS_TARG
		= Vec2<PhysElTarg>(PhysElTarg(0), PhysElTarg(0)),
	template<typename> typename AllocTarg=std::allocator>
class CollGridCsz2d {
public:		// types
	// named after physics
	using PhysElT = PhysElTarg;
	using PhysElVec2 = Vec2<PhysElT>;
	using PhysElRect2 = Rect2<PhysElT>;

	// An index into the grid
	using GridIndT = i32;
	using GridIndVec2 = Vec2<GridIndT>;
	using GridIndRect2 = Rect2<GridIndT>;

	template<typename OtherT>
	using Alloc = AllocTarg<OtherT>;

	// "Dynarr" is short for "Dynamic Array"
	//using GridIndDynarr = std::vector<GridIndVec2, Alloc<GridIndVec2>>;
	//using GridIndDyna2d
	//	= std::vector<GridIndDynarr, Alloc<GridIndDynarr>>;

	//using GridIndR2Dynarr = std::vector<GridIndRect2, Alloc<GridIndRect2>>;
	//using GridIndR2Dyna2d
	//	= std::vector<GridIndR2Dynarr, Alloc<GridIndR2Dynarr>>;

	//template<typename T>
	//using R2PtrDynarr = std::vector<Rect2<T>*, Alloc<Rect2<T>*>>;
	//template<typename T>
	//using R2PtrDyna2d = std::vector<R2PtrDynarr<T>, Alloc<R2PtrDynarr<T>>>;
	template<typename T>
	using Uset = std::unordered_set
		<T, std::hash<T>, std::equal_to<T>, Alloc<T>>;

	//using PhysR2Dynarr = std::vector<PhysElRect2, Alloc<PhysElRect2>>;
	//using PhysR2Dyna2d
	//	= std::vector<PhysR2Dynarr, Alloc<PhysR2Dynarr>>;

	//template<CanRect2Intersect<T> ShapeT>
	//using IntersectShapeVec = std::vector<ShapeT, Alloc<ShapeT>>;
	//template<CanRect2IntersectFancy<T> ShapeT>
	//using IntersectFancyShapeVec = std::vector<ShapeT, Alloc<ShapeT>>;

public:		// constants
	static constexpr PhysElVec2
		GRID_ELEM_SIZE_2D = GRID_ELEM_SIZE_2D_TARG;
	static constexpr GridIndVec2
		NUM_GRID_ELEMS_2D = NUM_GRID_ELEMS_2D_TARG;
	static constexpr PhysElVec2
		ENC_PHYS_EL_RECT2_POS = ENC_PHYS_EL_RECT2_POS_TARG;
	static constexpr size_t
		TOTAL_NUM_ELEMS = NUM_GRID_ELEMS_2D.x * NUM_GRID_ELEMS_2D.y;
protected:		// functions
	static constexpr inline PhysElT _to_phys_el_no_offset(
		const GridIndT& to_conv, bool index
	) {
		return PhysElT(to_conv) * GRID_ELEM_SIZE_2D.at(index);
	}
public:		// functions
	//--------
	//template<Dim2d DIM>
	static constexpr inline PhysElT to_phys_el(
		const GridIndT& to_conv, bool index
	) {
		// For power-of-two grid element sizes, this multiply should be
		// converted into a left shift (at least when optimization is
		// enabled).
		return _to_phys_el_no_offset(to_conv, index)
			+ ENC_PHYS_EL_RECT2_POS.at(index);
		//return PhysElT(to_conv) * GRID_ELEM_SIZE_2D.at(index);
	}
	static constexpr inline PhysElVec2 to_phys_el_vec2(
		const GridIndVec2& to_conv
	) {
		PhysElVec2 ret;
		for (size_t i=0; i<to_conv.size(); ++i) {
			ret.at(i) = to_phys_el(to_conv.at(i), i);
		}
		return ret;
	}
	//--------
	//template<Dim2d DIM>
	static constexpr inline GridIndT to_grid_ind(
		const PhysElT& to_conv, bool index
	) {
		// For power-of-two grid element sizes, this divide should be
		// converted into a right shift (at least when optimization is
		// enabled).
		//return GridIndT((to_conv - ENC_PHYS_EL_RECT2_POS.at(index))
		//	/ GRID_ELEM_SIZE_2D.at(index));
		//return GridIndT
		//	((to_conv / GRID_ELEM_SIZE_2D.at(index))
		//		- ENC_PHYS_EL_RECT2.pos.at(index));
		//return GridIndT(to_conv / GRID_ELEM_SIZE_2D.at(index));
		return GridIndT((to_conv - ENC_PHYS_EL_RECT2.pos.at(index))
			/ GRID_ELEM_SIZE_2D.at(index));
	}
	static constexpr inline GridIndVec2 to_grid_ind_vec2(
		const PhysElVec2& to_conv
	) {
		GridIndVec2 ret;
		for (size_t i=0; i<to_conv.size(); ++i) {
			ret.at(i) = to_grid_ind(to_conv.at(i), i);
		}
		return ret;
	}
	//--------
public:		// constants
	static constexpr inline PhysElRect2
		ENC_PHYS_EL_RECT2
			//{.pos=ENC_PHYS_EL_RECT2_POS,
			//.size_2d=to_phys_el_vec2(NUM_GRID_ELEMS_2D)};
			{.pos=ENC_PHYS_EL_RECT2_POS,
			.size_2d
				{.x=_to_phys_el_no_offset(NUM_GRID_ELEMS_2D.x, 0),
				.y=_to_phys_el_no_offset(NUM_GRID_ELEMS_2D.y, 1)}};
	static constexpr inline GridIndRect2
		//ENC_GRID_IND_RECT2 = (GridIndRect2::build_in_grid
		//	(to_grid_ind_vec2(ENC_PHYS_EL_RECT2.tl_corner()),
		//	to_grid_ind_vec2(ENC_PHYS_EL_RECT2.br_corner()),
		//	GRID_ELEM_SIZE_2D));
		//ENC_GRID_IND_RECT2 = GridIndRect2::build_in_grid
		//	(ENC_PHYS_EL_RECT2.tl_corner(),
		//	ENC_PHYS_EL_RECT2.br_corner(),
		//	GRID_ELEM_SIZE_2D);
		//ENC_GRID_IND_RECT2 = to_grid_ind_rect2_lim(ENC_PHYS_EL_RECT2);
		ENC_GRID_IND_RECT2 = GridIndRect2::build_in_grid
			(to_grid_ind_vec2(ENC_PHYS_EL_RECT2.tl_corner()),
			to_grid_ind_vec2(ENC_PHYS_EL_RECT2.br_corner()));
public:		// types
	using DataElemT = DataElemTarg;
	using DataMapElemT = Uset<DataElemT*>;
	//using DataRowT
	//	= std::array<Uset<DataElemT*>, ENC_GRID_IND_RECT2.size_2d.x>;
	//using DataT
	//	= std::array<DataRowT, ENC_GRID_IND_RECT2.size_2d.y>;
	using DataT = std::unordered_map
		<GridIndVec2, DataMapElemT,
		std::hash<GridIndVec2>, std::equal_to<GridIndVec2>,
		Alloc<std::pair<const GridIndVec2, DataMapElemT>>>;
protected:		// variables
	//Vec2<PhysElT>
	//	elem_size_2d = {PhysElT(0), PhysElT(0)};
	//GridIndVec2
	//	grid_size_2d = GridIndVec2(0, 0);
	//R2PtrVecA2d _data;
	DataT
		_data;
public:		// functions
	//--------
	CollGridCsz2d() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(CollGridCsz2d);
	virtual ~CollGridCsz2d() = default;
	//template<CanRect2Intersect<PhysElT> ShapeT>
	//static GridIndDyna2d grid_indices(
	//	const std::vector<ShapeT, Alloc<ShapeT>>& arg_vec
	//) {
	//}
//protected:		// functions
//	constexpr inline auto& _at(const GridIndVec2& pos) {
//		return _data.at(pos.y).at(pos.x);
//	}
//	constexpr inline const auto& _at(const GridIndVec2& pos) const {
//		return _data.at(pos.y).at(pos.x);
//	}
public:		// functions
	bool insert(DataElemT* data_elem) {
		const GridIndRect2
			grid_ind_rect2 = to_grid_ind_rect2_lim(data_elem->rect);

		bool ret = false;

		GridIndVec2 pos;
		for (
			pos.y=grid_ind_rect2.top_y();
			pos.y<=grid_ind_rect2.bottom_y();
			++pos.y
		) {
			for (
				pos.x=grid_ind_rect2.left_x();
				pos.x<=grid_ind_rect2.right_x();
				++pos.x
			) {
				ret = true;
				//_at(pos).insert(data_elem);
				_data.insert(std::pair(pos, DataMapElemT()));
				_data.at(pos).insert(data_elem);
			}
		}

		return ret;
	}
	//void insert(const Uset<PhysElRect2*>& to_insert_uset) {
	//	for (const auto& item: to_insert_uset) {
	//		insert(item);
	//	}
	//}

	bool erase(
		DataElemT* data_elem, const GridIndRect2& search_grid_ind_rect2
	) {
		bool ret = false;

		GridIndVec2 pos;
		for (
			pos.y=search_grid_ind_rect2.top_y();
			pos.y<=search_grid_ind_rect2.bottom_y();
			++pos.y
		) {
			for (
				pos.x=search_grid_ind_rect2.left_x();
				pos.x<=search_grid_ind_rect2.right_x();
				++pos.x
			) {
				if (
					_data.contains(pos)
					&& _data.at(pos).contains(data_elem)
				) {
					ret = true;
					_data.at(pos).erase(data_elem);
				}
			}
		}

		return ret;
	}

	void clear() noexcept {
		//for (auto& row: _data) {
		//	for (auto& item: row) {
		//		item.clear();
		//	}
		//}
		_data.clear();
	}
	// This finds others that are located in the same grid elements
	DataMapElemT find_others(DataElemT* data_elem) const {
		DataMapElemT ret;

		const GridIndRect2
			grid_ind_rect2 = to_grid_ind_rect2_lim(data_elem->rect);

		GridIndVec2 pos;
		for (
			pos.y=grid_ind_rect2.top_y();
			pos.y<=grid_ind_rect2.bottom_y();
			++pos.y
		) {
			for (
				pos.x=grid_ind_rect2.left_x();
				pos.x<=grid_ind_rect2.right_x();
				++pos.x
			) {
				if (
					_data.contains(pos)
					//&& _data.at(pos).contains(data_elem)
				) {
					ret.insert(_data.at(pos).cbegin(),
						_data.at(pos).cend());
				}
			}
		}
		if (ret.contains(data_elem)) {
			ret.erase(data_elem);
		}
		return ret;
	}
	//Uset<std::pair<DataElemT*, DataElemT*>> intersect() const {
	//	Uset<std::pair<DataElemT*, DataElemT*>> ret;

	//	//GridIndVec2 pos;
	//	//for (
	//	//	pos.y=ENC_GRID_IND_RECT2.top_y();
	//	//	pos.y<=ENC_GRID_IND_RECT2.bottom_y();
	//	//	++pos.y
	//	//) {
	//	//	for (
	//	//		pos.x=ENC_GRID_IND_RECT2.left_x();
	//	//		pos.x<=ENC_GRID_IND_RECT2.right_x();
	//	//		++pos.x
	//	//	) {
	//	//	}
	//	//}
	//	//for (const auto& item: _data) {
	//	//}
	//}

	//static constexpr inline GridIndRect2 to_grid_ind_rect2(
	//	const PhysElRect2& phys_el_rect2
	//) {
	//	return GridIndRect2::build_in_grid
	//		(to_grid_ind_vec2(phys_el_rect2.tl_corner()),
	//		to_grid_ind_vec2(phys_el_rect2.br_corner()));
	//}
	static constexpr inline GridIndRect2 to_grid_ind_rect2_lim(
		const PhysElVec2& phys_el_vec2
	) {
		return GridIndRect2::build_in_grid_lim
			(to_grid_ind_vec2(phys_el_vec2),
			ENC_GRID_IND_RECT2);
	}
	static constexpr inline GridIndRect2 to_grid_ind_rect2_lim(
		const PhysElRect2& phys_el_rect2
	) {
		return GridIndRect2::build_in_grid_lim
			(to_grid_ind_vec2(phys_el_rect2.tl_corner()),
			to_grid_ind_vec2(phys_el_rect2.br_corner()),
			ENC_GRID_IND_RECT2);
	}

	//template<CanRect2IntersectFancy<PhysElT> ShapeT>
	//static GridIndDyna2d grid_indices_fancy(
	//	const IntersectFancyShapeDynarr<ShapeT>& shape_vec,
	//	const Vec2<PhysElT>& arg_padding=Vec2<PhysElT>()
	//);

	//static GridIndRect2 grid_indices_fancy(
	//	const Rect2<PhysElT>& arg,
	//	const Vec2<PhysElT>& arg_padding=Vec2<PhysElT>()
	//) {
	//	GridIndDynarr ret;

	//	if (ENC_PHYS_EL_RECT2.intersect_fancy(arg, arg_padding)) {
	//	}

	//	return ret;
	//}
	//--------
	GEN_GETTER_BY_CON_REF(data);
	//--------
};

//template<typename T, Vec2<size_t> NUM_GRID_ELEMS_2D,
//	template<typename> typename ContnrEtcT=std::vector>
//inline ContnrEtcT<Vec2<T>> grid_intersect
//--------
} // namespace math
} // namespace liborangepower

#endif		// liborangepower_math_coll_grid_2d_classes_hpp
