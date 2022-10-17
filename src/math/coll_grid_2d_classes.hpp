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
// A grid for doing cheaper collision checking in 2D, with constant
// numerical attributes of the grid
template<typename PhysElTarg,
	HasRect2BboxConGetter<PhysElTarg> DataElTarg,
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
	template<typename T>
	using Dynarr = std::vector<T, Alloc<T>>;

	template<typename T>
	using Uset = std::unordered_set
		<T, std::hash<T>, std::equal_to<T>, Alloc<T>>;
	template<typename Key, typename T>
	using Umap = std::unordered_map
		<Key, T, std::hash<Key>, std::equal_to<Key>,
		Alloc<std::pair<const Key, T>>>;

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
	using DataElT = DataElTarg;
	using DataElPtrUsetT = Uset<DataElT*>;
	//using DataRowT
	//	= std::array<Uset<DataElT*>, ENC_GRID_IND_RECT2.size_2d.x>;
	//using DataT
	//	= std::array<DataRowT, ENC_GRID_IND_RECT2.size_2d.y>;
	using DataT = Umap<GridIndVec2, DataElPtrUsetT>;
protected:		// variables
	DataT
		_data;
public:		// functions
	//--------
	CollGridCsz2d() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(CollGridCsz2d);
	virtual ~CollGridCsz2d() = default;
public:		// functions
	bool insert(DataElT* data_el) {
		const GridIndRect2
			grid_ind_rect2 = to_grid_ind_rect2_lim(data_el->bbox());

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
				//_at(pos).insert(data_el);
				_data.insert(std::pair(pos, DataElPtrUsetT()));
				_data.at(pos).insert(data_el);
			}
		}

		return ret;
	}
	//void insert(const Uset<DataElT*>& to_insert_uset) {
	//	for (const auto& item: to_insert_uset) {
	//		insert(item);
	//	}
	//}

	bool erase(
		DataElT* data_el,
		const std::optional<GridIndRect2>& search_grid_ind_rect2
	) {
		bool ret = false;
		GridIndRect2 temp_grid_ind_rect2
			= search_grid_ind_rect2
			? *search_grid_ind_rect2
			: to_grid_ind_rect2_lim(data_el->bbox());

		GridIndVec2 pos;
		for (
			pos.y=temp_grid_ind_rect2.top_y();
			pos.y<=temp_grid_ind_rect2.bottom_y();
			++pos.y
		) {
			for (
				pos.x=temp_grid_ind_rect2.left_x();
				pos.x<=temp_grid_ind_rect2.right_x();
				++pos.x
			) {
				if (
					_data.contains(pos)
					&& _data.at(pos).contains(data_el)
				) {
					ret = true;
					_data.at(pos).erase(data_el);
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
	DataElPtrUsetT find_others(DataElT* data_el) const {
		DataElPtrUsetT ret;

		const GridIndRect2
			grid_ind_rect2 = to_grid_ind_rect2_lim(data_el->bbox());

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
					//&& _data.at(pos).contains(data_el)
				) {
					ret.insert(_data.at(pos).cbegin(),
						_data.at(pos).cend());
				}
			}
		}
		if (ret.contains(data_el)) {
			ret.erase(data_el);
		}
		return ret;
	}

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
