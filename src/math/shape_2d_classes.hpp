#ifndef liborangepower_math_shape_2d_classes_hpp
#define liborangepower_math_shape_2d_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_output_funcs.hpp"
#include "../strings/sconcat_etc.hpp"

#include "../containers/std_hash_stuff.hpp"

//#include "../binser/serialize_funcs.hpp"
#include "../binser/serialize_defines.hpp"
#include "../binser/from_bv_factory_stuff.hpp"
#include "../binser/serialize_func_decls.hpp"
#include "../concepts/is_specialization_concepts.hpp"
#include "../concepts/math_concepts.hpp"

#include "misc_funcs.hpp"
#include "vec2_classes.hpp"

#include <cmath>
#include <cstdint>
#include <concepts>

namespace liborangepower
{
namespace math
{
//--------
template<typename T>
class Hit2
{
public:		// types
	using ElemT = T;
public:		// static constants
	static constexpr int
		DIDNT_HIT_TM = 1;
public:		// variables
	//--------
	#define MEMB_LIST_SHAPE_HIT2(X) \
		X(pos, std::nullopt) \
		X(normal, std::nullopt) \
		X(delta, std::nullopt) \
		X(tm, std::nullopt) \

	Vec2<T>
		// `pos` is the point of contact between the two objects (or an
		// estimation of it, in some sweep tests)
		pos,

		// `normal` is the surface normal at the point of contact
		normal,

		// `delta` is the overlap between the two objects, and is a vector
		// that can be added to the colliding object's position to move it
		// back to a non-colliding state.
		delta;

	// `tm` (time) is only defined for segment and sweep intersections, and
	// is a fraction from 0 to 1 indicating how far along the line of
	// collision
	T tm;
	//--------
public:		// functions
	//--------
	static inline Hit2 from_bv(const binser::Value& bv)
	{
		Hit2<T> ret;

		MEMB_LIST_SHAPE_HIT2(BINSER_MEMB_FROM_BV_DESERIALIZE);

		return ret;
	}
	inline operator binser::Value () const
	{
		binser::Value ret;

		MEMB_LIST_SHAPE_HIT2(BINSER_MEMB_SERIALIZE);

		return ret;
	}
	//--------
	template<typename OtherElemT>
	explicit constexpr inline operator Hit2<OtherElemT> () const
		requires std::convertible_to<T, OtherElemT>
	{
		Hit2<OtherElemT> ret;

		#define X(name, dummy_arg) \
			ret.name = std::remove_cvref_t<decltype(ret.name)>(name);
		MEMB_LIST_SHAPE_HIT2(X);
		#undef X

		return ret;
	}
	//--------
};

template<typename T>
constexpr inline std::ostream& operator << (std::ostream& os,
	const Hit2<T>& arg)
{
	return misc_output::osprintout
	(
		os,
		"{",
			//arg.pos, " ",
			//arg.normal, " ",
			//arg.delta, " ",
			//arg.tm,

			//#define X(memb, dummy_arg) strings::sconcat( #memb , "{", arg . memb , "}" ),
			#define X(memb, dummy_arg) \
				strings::sconcat( #memb , arg . memb ),

			strings::strjoin2
			(
				std::string(" "),
				std::vector
				({
					MEMB_LIST_SHAPE_HIT2(X)
				})
			),

			#undef X
		"}"
	);
}

template<typename T>
class Sweep2
{
public:		// types
	using ElemT = T;
public:		// static constants
	static constexpr int
		DIDNT_HIT_TM = 1;
public:		// variables
	#define MEMB_LIST_SHAPE_SWEEP2(X) \
		X(hit, std::nullopt) \
		X(pos, std::nullopt) \
		X(tm, std::nullopt) \

	std::optional<Hit2<T>> hit = std::nullopt;
	Vec2<T> pos;

	// This is a copy of `hit->time`, offset by EPSILON, or 1 if the
	// object didn't hit anything during the sweep
	T tm = T(DIDNT_HIT_TM);
public:		// functions
	//--------
	static inline Sweep2 from_bv(const binser::Value& bv)
	{
		Sweep2<T> ret;

		MEMB_LIST_SHAPE_SWEEP2(BINSER_MEMB_FROM_BV_DESERIALIZE);

		return ret;
	}
	inline operator binser::Value () const
	{
		binser::Value ret;

		MEMB_LIST_SHAPE_SWEEP2(BINSER_MEMB_SERIALIZE);

		return ret;
	}
	//--------
	constexpr inline T didnt_hit() const
	{
		return tm == T(DIDNT_HIT_TM);
	}
	//--------
};

template<typename T>
constexpr inline std::ostream& operator << (std::ostream& os,
	const Sweep2<T>& arg)
{
	return misc_output::osprintout
	(
		os,
		"{",
			//arg.hit, " ",
			//arg.pos, " ",
			//arg.tm,

			//#define X(memb, dummy_arg) strings::sconcat( #memb , "{", arg . memb , "}" ),
			#define X(memb, dummy_arg) \
				strings::sconcat( #memb , arg . memb ),

			strings::strjoin2
			(
				std::string(" "),
				std::vector
				({
					MEMB_LIST_SHAPE_SWEEP2(X)
				})
			),

			#undef X
		"}"
	);
}
//--------
template<typename T>
class LineSeg2
{
public:		// types
	using ElemT = T;
public:		// variables
	#define MEMB_LIST_SHAPE_LINE_SEG2(X) \
		X(p0, std::nullopt) \
		X(p1, std::nullopt) \

	Vec2<T>
		p0,
		p1;
public:		// functions
	//--------
	static inline LineSeg2 from_bv(const binser::Value& bv)
	{
		LineSeg2<T> ret;

		MEMB_LIST_SHAPE_LINE_SEG2(BINSER_MEMB_FROM_BV_DESERIALIZE);

		return ret;
	}
	inline operator binser::Value () const
	{
		binser::Value ret;

		MEMB_LIST_SHAPE_LINE_SEG2(BINSER_MEMB_SERIALIZE);

		return ret;
	}
	//--------
	template<typename OtherElemT>
	explicit constexpr inline operator LineSeg2<OtherElemT> () const
		requires std::convertible_to<T, OtherElemT>
	{
		LineSeg2<OtherElemT> ret;

		#define X(name, dummy_arg) \
			ret.name = std::remove_cvref_t<decltype(ret.name)>(name);
		MEMB_LIST_SHAPE_LINE_SEG2(X);
		#undef X

		return ret;
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline auto operator <=> (const LineSeg2<OtherElemT>& to_cmp)
		const
	{
		const Vec2<Vec2<T>>
			temp_self(p0, p1);
		const Vec2<Vec2<OtherElemT>>
			temp_to_cmp(to_cmp.p0, to_cmp);
		return temp_self <=> temp_to_cmp;
	}
	//--------
	// The delta between the two points
	constexpr inline Vec2<T> pt_delta() const
	{
		return p1 - p0;
	}
	//--------
};

template<typename T>
constexpr inline std::ostream& operator << (std::ostream& os,
	const LineSeg2<T>& arg)
{
	return misc_output::osprintout
	(
		os,
		"{",
			//arg.p0, " ",
			//arg.p1,

			//#define X(memb, dummy_arg) strings::sconcat( #memb , "{", arg . memb , "}" ),
			#define X(memb, dummy_arg) \
				strings::sconcat( #memb , arg . memb ),

			strings::strjoin2
			(
				std::string(" "),
				std::vector
				({
					MEMB_LIST_SHAPE_LINE_SEG2(X)
				})
			),

			#undef X
		"}"
	);
}
//--------
template<typename T>
class Rect2
{
public:		// types
	using ElemT = T;
public:		// variables
	#define MEMB_LIST_SHAPE_RECT2(X) \
		X(pos, std::nullopt) \
		X(size_2d, std::nullopt) \

	// The top-left position, with larger values growing down and to the
	// right
	Vec2<T>
		pos = Vec2<T>(),
		size_2d = Vec2<T>();
public:		// functions
	//--------
	template<std::convertible_to<T> LimElemT,
		std::convertible_to<T> PtElemT=T>
	constexpr inline Rect2 fit_into_grid_lim
		(const Rect2<LimElemT>& lim,
		const Vec2<PtElemT>& grid_elem_size_2d=Vec2<PtElemT>(1, 1)) const
	//constexpr inline Rect2 fit_into_grid_lim
	//	(const Rect2& lim,
	//	const Vec2<T>& grid_elem_size_2d=Vec2<T>(1, 1)) const
	{
		//const Vec2<T>
		//	temp_size_2d
		//		(min_va(size_2d.x, T(lim.size_2d.x)),
		//		min_va(size_2d.y, T(lim.size_2d.y)));
		//return Rect2<T>
		//	{.pos=Vec2<T>(max_va(left_x(), T(lim.left_x()))};
		//if (lim.arg_inside(*this))
		//{
		//	return *this;
		//}
		//else
		//{
		//	return build_in_grid<T, true>
		//		(Vec2<T>(max_va(left_x(), T(lim.left_x())),
		//			max_va(top_y(), T(lim.top_y()))),
		//		Vec2<T>(min_va(right_x(), T(lim.right_x())),
		//			min_va(bottom_y(), T(lim.bottom_y()))));
		//}

		const Vec2<PtElemT>
			temp_tl_corner
				(clamp(PtElemT(left_x()), lim.left_x(), lim.right_x()),
				clamp(PtElemT(top_y()), lim.top_y(), lim.bottom_y())),
			temp_br_corner
				(clamp(PtElemT(right_x()), lim.left_x(), lim.right_x()),
				clamp(PtElemT(bottom_y()), lim.top_y(), lim.bottom_y())),
			temp_pos
				(min_va(temp_tl_corner.x, temp_br_corner.x),
				min_va(temp_tl_corner.y, temp_br_corner.y)),
			temp_size_2d
				(cstm_abs(temp_br_corner.x - temp_tl_corner.x
					+ PtElemT(grid_elem_size_2d.x)),
				cstm_abs(temp_br_corner.y - temp_tl_corner.y
					+ PtElemT(grid_elem_size_2d.y)));
		return Rect2(Vec2<T>(temp_pos), Vec2<T>(temp_size_2d));

		//return build_in_grid
		//	(Vec2<T>,
		//	Vec2<T>);

		//return build_in_grid_lim(Vec2<OtherElemT>(tl_corner()),
		//	Vec2<OtherElemT>(br_corner()), Rect2<OtherElemT>(lim));
	}

	//template<std::convertible_to<T> OtherElemT>
	//static constexpr inline Rect2 build_in_grid
	//	(const Rect2<OtherElemT>& to_conv)
	//{
	//	return build_in_grid(to_conv.tl_corner(), to_conv.br_corner());
	//}
	//template<std::convertible_to<T> OtherElemT, bool inc_size_2d=true>
	template<std::convertible_to<T> PtElemT>
	static constexpr inline Rect2 build_in_grid
		(const Vec2<PtElemT>& p0, const Vec2<PtElemT>& p1,
		const Vec2<PtElemT>& grid_elem_size_2d=Vec2<PtElemT>(1, 1))
	{
		return Rect2<T>
			//{.pos=Vec2<T>(T(min_va(p0.x, p1.x)), T(min_va(p0.y, p1.y))),
			//.size_2d=Vec2<T>
			//	(T(cstm_abs(p1.x - p0.x)) + T(inc_size_2d),
			//	T(cstm_abs(p1.y - p0.y)) + T(inc_size_2d))};
			{.pos=Vec2<T>(T(min_va(p0.x, p1.x)), T(min_va(p0.y, p1.y))),
			.size_2d=Vec2<T>
				(T(cstm_abs(p1.x - p0.x) + grid_elem_size_2d.x),
				T(cstm_abs(p1.y - p0.y) + grid_elem_size_2d.y))};
			//{.pos=Vec2<T>(T(min_va(p0.x, p1.x)), T(min_va(p0.y, p1.y))),
			//.size_2d=Vec2<T>
			//	(T(cstm_abs(p1.x - p0.x)),
			//	T(cstm_abs(p1.y - p0.y)))};
	}
	//template<std::convertible_to<T> ToConvElemT,
	//	std::convertible_to<T> LimElemT>
	//static constexpr inline Rect2 build_in_grid_lim
	//	(const Rect2<ToConvElemT>& to_conv, const Rect2<LimElemT>& lim)
	//{
	//	return build_in_grid_lim<ToConvElemT, LimElemT>
	//		(to_conv.tl_corner(), to_conv.br_corner(), lim);
	//}
	template<std::convertible_to<T> PtElemT,
		std::convertible_to<T> LimElemT>
	static constexpr inline Rect2 build_in_grid_lim
		(const Vec2<PtElemT>& p0, const Vec2<PtElemT>& p1,
		const Rect2<LimElemT>& lim,
		const Vec2<PtElemT>& grid_elem_size_2d=Vec2<PtElemT>(1, 1))
	{
		//const Vec2<T>
		//	temp_size_2d
		//		(T(cstm_abs<T>(p1.x - p0.x) + T(1)),
		//		T(cstm_abs<T>(p1.y - p0.y) + T(1)));
		//		//(T(cstm_abs<T>(p1.x - p0.x)),
		//		//T(cstm_abs<T>(p1.y - p0.y)));
		//return Rect2<T>
		//	{.pos=Vec2<T>
		//		(max_va(T(min_va(p0.x, p1.x)), T(lim.pos.x)),
		//		max_va(T(min_va(p0.y, p1.y)), T(lim.pos.y))),
		//	.size_2d=Vec2<T>
		//		(min_va(temp_size_2d.x, T(lim.size_2d.x)),
		//		min_va(temp_size_2d.y, T(lim.size_2d.y)))};

		return build_in_grid(p0, p1, grid_elem_size_2d)
			.fit_into_grid_lim(lim, grid_elem_size_2d);

		//const Rect2<LimElemT>
		//	temp_rect = Rect2<PtElemT>::build_in_grid(p0, p1)
		//		.fit_into_lim(lim);
		//return Rect2<T>
		//	{.pos=Vec2<T>(T(temp_rect.pos.x), T(temp_rect.pos.y)),
		//	.size_2d=Vec2<T>(T(temp_rect.size_2d.x),
		//		T(temp_rect.size_2d.y))};

		//return Rect2<T>::build_in_grid(Vec2<T>(T(p0.x), T(p0.y)),
		//	Vec2<T>(T(p1.x), T(p1.y))).fit_into_lim
		//	(Rect2<T>
		//		{.pos=Vec2<T>(T(lim.pos.x), T(lim.pos.y)),
		//		.size_2d=Vec2<T>(T(lim.size_2d.x), T(lim.size_2d.y))});
		//return Rect2<T>::build_in_grid(Vec2<T>(p0), Vec2<T>(p1))
		//	.fit_into_lim(Rect2<T>(lim));
	}

	template<std::convertible_to<T> PtElemT>
	constexpr inline Rect2 build_in_grid_inflated
		(const Vec2<PtElemT>& tl_amount, const Vec2<PtElemT>& br_amount,
		const Vec2<PtElemT>& grid_elem_size_2d=Vec2<PtElemT>()) const
	{
		return build_in_grid
			(Vec2<PtElemT>(PtElemT(left_x()) - tl_amount.x,
				PtElemT(top_y()) - tl_amount.y),
			Vec2<PtElemT>(PtElemT(right_x()) + br_amount.x,
				PtElemT(bottom_y()) + br_amount.y),
			grid_elem_size_2d);
	}
	//// This function intend for forcing the created `Rect2` to fit within
	//// some other `Rect2`, which is what `tl_lim` and `br_lim` are for.
	//constexpr inline Rect2 build_in_grid_inflated_lim
	//	(const Vec2<T>& tl_amount, const Vec2<T>& br_amount,
	//	const Vec2<T>& tl_lim, const Vec2<T>& br_lim)
	// This function intend for forcing the created `Rect2` to fit within
	// some other `Rect2`, `lim`.
	template<std::convertible_to<T> PtElemT,
		std::convertible_to<T> LimElemT>
	constexpr inline Rect2 build_in_grid_inflated_lim
		(const Vec2<PtElemT>& tl_amount, const Vec2<PtElemT>& br_amount,
		const Rect2<LimElemT>& lim,
		const Vec2<PtElemT>& grid_elem_size_2d=Vec2<PtElemT>())
		const
	{
		//return build_in_grid
		//	(Vec2<T>{.x=max_va(left_x() - tl_amount.x, tl_lim.x),
		//		.y=min_va(top_y() - tl_amount.y, tl_lim.y)},
		//	Vec2<T>{.x=min_va(right_x() + br_amount.x, br_lim.x),
		//		.y=min_va(bottom_y() + br_amount.y, br_lim.y)});
		//return build_in_grid
		//	(Vec2<PtElemT>(PtElemT(left_x()) - tl_amount.x,
		//		PtElemT(top_y()) - tl_amount.y),
		//	Vec2<PtElemT>(PtElemT(right_x()) + br_amount.x
		//		PtElemT(bottom_y()) + br_amount.y),
		//	grid_elem_size_2d)
		//	.fit_into_grid_lim(lim, grid_elem_size_2d);
		return build_in_grid_inflated(tl_amount, br_amount,
			grid_elem_size_2d)
			.fit_into_grid_lim(lim, grid_elem_size_2d);
	}
	//--------
	template<typename OtherElemT>
	explicit constexpr inline operator Rect2<OtherElemT> () const
		requires std::convertible_to<T, OtherElemT>
	{
		//return Rect2<OtherElemT>
		//	(Vec2<OtherElemT>(pos), Vec2<OtherElemT>(size_2d));
		Rect2<OtherElemT> ret;

		#define X(name, dummy_arg) \
			ret.name = std::remove_cvref_t<decltype(ret.name)>(name);
		MEMB_LIST_SHAPE_RECT2(X);
		#undef X

		return ret;
	}
	//--------
	static inline Rect2 from_bv(const binser::Value& bv)
	{
		Rect2<T> ret;

		MEMB_LIST_SHAPE_RECT2(BINSER_MEMB_FROM_BV_DESERIALIZE);

		return ret;
	}
	inline operator binser::Value () const
	{
		binser::Value ret;

		MEMB_LIST_SHAPE_RECT2(BINSER_MEMB_SERIALIZE);

		return ret;
	}
	//--------
	//inline auto operator <=> (const Rect2& to_cmp) const = default;
	template<std::convertible_to<T> OtherElemT>
	constexpr inline auto operator <=> (const Rect2<OtherElemT>& to_cmp)
		const
	{
		const Vec2<Vec2<T>>
			temp_self(pos, size_2d);
		const Vec2<Vec2<OtherElemT>>
			temp_to_cmp(to_cmp.pos, to_cmp.size_2d);
		return temp_self <=> temp_to_cmp;
	}
	//--------
	constexpr inline Vec2<T> cntr_pos() const
	{
		return pos + half_size();
	}
	constexpr inline Vec2<T> half_size() const
	{
		//return tl_corner() + ((size_2d - Vec2<T>(T(1), T(1))) / T(2));
		//return tl_corner() + (br_corner() / T(2));
		//return tl_corner() + (size_2d / T(2));
		//if constexpr (concepts::HasArithDiv2MbrFunc<T>)
		//{
		//	return {div_2(size_2d.x), div_2(size_2d.y)}
		//}
		//else
		//{
		//	return size_2d / T(2);
		//}
		return div_2(size_2d);
	}

	constexpr inline T left_x() const
	{
		return pos.x;
	}
	constexpr inline T top_y() const
	{
		return pos.y;
	}
	constexpr inline T right_x() const
	{
		return pos.x + size_2d.x - T(1);
	}
	constexpr inline T bottom_y() const
	{
		return pos.y + size_2d.y - T(1);
	}

	constexpr inline Vec2<T> tl_corner() const
	{
		return Vec2<T>(left_x(), top_y());
	}
	constexpr inline Vec2<T> tr_corner() const
	{
		return Vec2<T>(right_x(), top_y());
	}
	constexpr inline Vec2<T> bl_corner() const
	{
		return Vec2<T>(left_x(), bottom_y());
	}
	constexpr inline Vec2<T> br_corner() const
	{
		return Vec2<T>(right_x(), bottom_y());
	}
	//--------
	template<bool exclusive=false>
	constexpr inline bool intersect(const Vec2<T>& arg) const
	{
		//return intersect(Rect2<T>{.pos=arg, .size_2d=Vec2<T>()});

		if constexpr (exclusive)
		{
			return (arg.x > left_x() && arg.x < right_x()
				&& arg.y > top_y() && arg.y < bottom_y());
		}
		else
		{
			return (arg.x >= left_x() && arg.x <= right_x()
				&& arg.y >= top_y() && arg.y <= bottom_y());
		}
	}
	// `ret.pos` and `ret.delta` will be set to the nearest edge of the
	// `Rect2`
	//constexpr inline std::optional<Hit2<T>> intersect_fancy
	//	(const Vec2<T>& arg, bool exclusive=false,
	//	const Vec2<T>& arg_padding=Vec2<T>()) const
	constexpr inline std::optional<Hit2<T>> intersect_fancy
		(const Vec2<T>& arg, const Vec2<T>& arg_padding=Vec2<T>()) const
	{
		if (arg_padding != Vec2<T>())
		{
			//return intersect_fancy(LineSeg2<T>{arg, arg}, arg_padding);
			const Rect2<T>
				rect{//.pos=arg - (arg_padding / T(2)),
					.pos=arg - div_2(arg_padding), .size_2d=arg_padding};

			//return intersect_fancy(rect, exclusive, Vec2<T>());
			return intersect_fancy(rect, Vec2<T>());
		}
		//--------
		const Vec2<T>
			temp_cpos(cntr_pos()),
			temp_hsize(half_size());
		//--------
		//return (arg.x >= temp_cpos.x && arg.x <= br_corner().x
		//	arg.y >= temp_cpos.y && arg.y <= br_corner().y);
		const T
			dx = arg.x - temp_cpos.x,
			px = temp_hsize.x - cstm_abs(dx);
		//if ((exclusive && px <= T(0)) || (!exclusive && px < T(0)))
		//if (px <= T(0))
		if (px < T(0))
		{
			return std::nullopt;
		}

		const ElemT
			dy = arg.y - temp_cpos.y,
			py = temp_hsize.y - cstm_abs(dy);
		//if ((exclusive && py <= T(0)) || (!exclusive && py < T(0)))
		//if (py <= T(0))
		if (py < T(0))
		{
			return std::nullopt;
		}
		//--------
		Hit2<T> ret;

		if (px < py)
		{
			const T
				sx = cstm_sign(dx);
			ret.delta.x = px * sx;
			ret.normal.x = sx;
			ret.pos.x = temp_cpos.x + (temp_hsize.x * sx);
			ret.pos.y = arg.y;
		}
		else // if (px >= py)
		{
			const T
				sy = cstm_sign(dy);
			ret.delta.y = py * sy;
			ret.normal.y = sy;
			ret.pos.x = arg.x;
			ret.pos.y = temp_cpos.y + (temp_hsize.y * sy);
		}

		return ret;
		//--------
	}
	//constexpr inline std::optional<Hit2<T>> intersect_fancy
	//	(const LineSeg2<T>& arg, bool exclusive=false,
	//	const Vec2<T>& arg_padding=Vec2<T>()) const
	constexpr inline std::optional<Hit2<T>> intersect_fancy
		(const LineSeg2<T>& arg, const Vec2<T>& arg_padding=Vec2<T>())
		const
	{
		//--------
		//using misc_output::printout;
		//--------
		if (arg.p0.x == arg.p1.x || arg.p0.y == arg.p1.y)
		{
			//const Vec2<T>
			//	pi
			//	{
			//		min_va(arg.p0.x, arg.p1.x),
			//		min_va(arg.p0.y, arg.p1.y),
			//	},
			//	pa
			//	{
			//		max_va(arg.p0.x, arg.p1.x),
			//		max_va(arg.p0.y, arg.p1.y),
			//	};

			//const Rect2<T>
			//	rect
			//	{
			//		.pos
			//		//{
			//		//	pi.x - (arg_padding.x / T(2)),
			//		//	pi.y - (arg_padding.y / T(2))
			//		//},
			//			=pi - div_2(arg_padding),
			//		.size_2d
			//		//{
			//		//	(pa.x - pi.x) + (arg_padding.x / T(2)),
			//		//	(pa.y - pi.y) + (arg_padding.y / T(2))
			//		//},
			//			=(pa - pi) + div_2(arg_padding),
			//	};

			Rect2<T> rect;

			if (arg.p0.x < arg.p1.x)
			{
				// In this case, we have `arg.p0.y == arg.p1.y`
				//rect.pos.x = arg.p0.x - div_2(arg_padding.x);
				//rect.pos.y = arg.p0.y - div_2(arg_padding.y);
				rect.pos = arg.p0 - div_2(arg_padding);

				rect.size_2d.x = (arg.p1.x - arg.p0.x) + arg_padding.x;
				rect.size_2d.y = arg_padding.y;
			}
			else if (arg.p0.x == arg.p1.x)
			{
				if (arg.p0.y < arg.p1.y)
				{
					//rect.pos.x = arg.p0.x - (arg_padding.x / T(2));
					//rect.pos.y = arg.p0.y - (arg_padding.y / T(2));
					rect.pos.x = arg.p0.x - div_2(arg_padding.x);
					rect.pos.y = arg.p0.y - div_2(arg_padding.y);

					rect.size_2d.x = arg_padding.x;
					rect.size_2d.y = (arg.p1.y - arg.p0.y) + arg_padding.x;
				}
				else if (arg.p0.y == arg.p1.y)
				{
					//rect.pos.x = arg.p0.x - (arg_padding.x / T(2));
					//rect.pos.y = arg.p0.y - (arg_padding.y / T(2));
					rect.pos.x = arg.p0.x - div_2(arg_padding.x);
					rect.pos.y = arg.p0.y - div_2(arg_padding.y);

					rect.size_2d = arg_padding;
				}
				else // if (arg.p0.y > arg.p1.y)
				{
					//rect.pos.x = arg.p1.x - (arg_padding.x / T(2));
					//rect.pos.y = arg.p1.y - (arg_padding.y / T(2));
					rect.pos.x = arg.p1.x - div_2(arg_padding.x);
					rect.pos.y = arg.p1.y - div_2(arg_padding.y);

					rect.size_2d.x = arg_padding.x;
					rect.size_2d.y = (arg.p0.y - arg.p1.y) + arg_padding.x;
				}
			}
			else // if (arg.p0.x > arg.p1.x)
			{
				// In this case, we have `arg.p0.y == arg.p1.y`
				//rect.pos.x = arg.p1.x - (arg_padding.x / T(2));
				//rect.pos.y = arg.p0.y - (arg_padding.y / T(2));
				rect.pos.x = arg.p1.x - div_2(arg_padding.x);
				rect.pos.y = arg.p0.y - div_2(arg_padding.y);

				rect.size_2d.x = (arg.p0.x - arg.p1.x) + arg_padding.x;
				rect.size_2d.y = arg_padding.y;
			}

			//return intersect_fancy(rect, exclusive, Vec2<T>());
			return intersect_fancy(rect, Vec2<T>());
		}
		//--------
		auto calc_scale = [](const Vec2<T>& some_delta) -> Vec2<T>
		{
			//if constexpr (concepts::HasArithRecipMbrFunc<T>)
			//{
			//	return
			//		typename Vec2<T>::CtorArgs
			//		{
			//			.x=some_delta.x.recip(),
			//			.y=some_delta.y.recip(),
			//		};
			//}
			//else
			//{
			//	return
			//		typename Vec2<T>::CtorArgs
			//		{
			//			.x=T(1) / some_delta.x,
			//			.y=T(1) / some_delta.y,
			//		};
			//}
			return math::recip(some_delta.recip());
		};
		//--------
		const Vec2<T>
			//--------
			temp_cpos(cntr_pos()),
			temp_hsize(half_size()),
			delta(arg.pt_delta()),
			//--------
			scale(calc_scale(delta)),
			sign
			{
				.x=cstm_sign(scale.x),
				.y=cstm_sign(scale.y),
			},
			partial_time_vec
			{
				.x=sign.x * (temp_hsize.x + arg_padding.x),
				.y=sign.y * (temp_hsize.y + arg_padding.y),
			},
			near_time_vec
			{
				.x=(temp_cpos.x - partial_time_vec.x - arg.p0.x)
					* scale.x,
				.y=(temp_cpos.y - partial_time_vec.y - arg.p0.y)
					* scale.y,
			},
			far_time_vec
			{
				.x=(temp_cpos.x + partial_time_vec.x - arg.p0.x)
					* scale.x,
				.y=(temp_cpos.y + partial_time_vec.y - arg.p0.y)
					* scale.y,
			};
			//--------
		//--------
		//printout("ntv ftv: ", near_time_vec, " ", far_time_vec, "\n");
		if (near_time_vec.x > far_time_vec.y
			|| near_time_vec.y > far_time_vec.x)
		{
			//printout("!hit\n");
			return std::nullopt;
		}
		//--------
		const T near_time
			= near_time_vec.x > near_time_vec.y
			? near_time_vec.x
			: near_time_vec.y;
		const T far_time
			= far_time_vec.x > far_time_vec.y
			? far_time_vec.x
			: far_time_vec.y;

		//printout("nt ft: ", near_time, " ", far_time, "\n");

		//if (near_time >= T(1) || far_time <= T(0))
		//if ((exclusive && (near_time >= T(1) || far_time <= T(0)))
		//	|| (!exclusive && (near_time > T(1) || far_time < T(0))))
		if (near_time > T(1) || far_time < T(0))
		{
			//printout("!hit\n");
			return std::nullopt;
		}
		//--------
		Hit2<T> ret;

		ret.tm = clamp(near_time, T(0), T(1));
		//ret.tm = near_time;
		//ret.tm = far_time;

		if (near_time_vec.x > near_time_vec.y)
		{
			ret.normal.x = -sign.x;
			ret.normal.y = T(0);
		}
		else
		{
			ret.normal.x = T(0);
			ret.normal.y = -sign.y;
		}

		ret.delta = (T(1) - ret.tm) * (-delta);
		//ret.pos.x = arg.p0.x + delta.x * ret.tm;
		//ret.pos.y = arg.p0.y + delta.y * ret.tm;
		ret.pos = arg.p0 + delta * ret.tm;

		//printout("hit:\n",
		//	"\ttm: ", ret.tm, "\n",
		//	"\tnormal: ", ret.normal, "\n",
		//	"\tdelta: ", ret.delta, "\n",
		//	"\tpos: ", ret.pos, "\n");
		//printout("\n");

		return ret;
		//--------
	}

	constexpr inline bool intersect(const Rect2& arg) const
	{
		// This won't work for `int`s
		//return (cstm_abs(cntr_pos().x - arg.cntr_pos().x) * 2
		//		< (size_2d.x + arg.size_2d.x))
		//	&& (cstm_abs(cntr_pos().y - arg.cntr_pos().y) * 2 
		//		< (size_2d.y + arg.size_2d.y));

		return !(arg.left_x() > right_x()
			|| arg.right_x() < left_x()
			|| arg.top_y() > bottom_y()
			|| arg.bottom_y() < top_y());
	}
	//constexpr inline std::optional<Hit2<T>> intersect_fancy
	//	(const Rect2& arg, bool exclusive=false,
	//	const Vec2<T>& arg_padding=Vec2<T>()) const
	constexpr inline std::optional<Hit2<T>> intersect_fancy
		(const Rect2& arg, const Vec2<T>& arg_padding=Vec2<T>()) const
	{
		//--------
		const Rect2<T>
			temp_rect_0
			{
				.pos
				//{
				//	.x=pos.x - div_2(arg_padding.x),
				//	.y=pos.y - div_2(arg_padding.y),
				//},
					=pos - div_2(arg_padding),
				.size_2d
				//{
				//	size_2d.x + arg_padding.x,
				//	size_2d.y + arg_padding.y
				//}
					=size_2d + arg_padding,
			},
			temp_rect_1
			{
				.pos
				//{
				//	arg.pos.x - div_2(arg_padding.x),
				//	arg.pos.y - div_2(arg_padding.y)
				//},
					=arg.pos - div_2(arg_padding),
				.size_2d
				//{
				//	arg.size_2d.x + arg_padding.x,
				//	arg.size_2d.y + arg_padding.y
				//}
					=arg.size_2d + arg_padding,
			};
		//--------
		const Vec2<T>
			//temp_cpos(cntr_pos()),
			//temp_hsize(half_size()),

			//temp_arg_cpos(arg.cntr_pos()),
			//temp_arg_hsize(arg.half_size());

			temp_cpos(temp_rect_0.cntr_pos()),
			temp_hsize(temp_rect_0.half_size()),

			temp_arg_cpos(temp_rect_1.cntr_pos()),
			temp_arg_hsize(temp_rect_1.half_size());
		//--------
		const T
			dx = temp_arg_cpos.x - temp_cpos.x,
			px = (temp_arg_hsize.x + temp_hsize.x) - cstm_abs(dx);
		//if (px <= T(0))
		if (px < T(0))
		//if ((exclusive && px <= T(0)) || (!exclusive && px < T(0)))
		{
			return std::nullopt;
		}

		const T
			dy = temp_arg_cpos.y - temp_cpos.y,
			py = (temp_arg_hsize.y + temp_hsize.y) - cstm_abs(dy);
		if (py <= T(0))
		//if (py < T(0))
		//if ((exclusive && py <= T(0)) || (!exclusive && py < T(0)))
		{
			return std::nullopt;
		}
		//--------
		Hit2<T> ret;

		if (px < py)
		{
			const T sx = cstm_sign(dx);
			ret.delta.x = px * sx;
			ret.normal.x = sx;
			ret.pos.x = temp_cpos.x + (temp_hsize.x * sx);
			ret.pos.y = temp_arg_cpos.y;
		}
		else
		{
			const T sy = cstm_sign(dy);
			ret.delta.y = py * sy;
			ret.normal.y = sy;
			ret.pos.x = temp_arg_cpos.x;
			ret.pos.y = temp_cpos.y + (temp_hsize.y * sy);
		}

		return ret;
		//--------
	}

	// For this function, `arg` is the moving `Rect2`, and `this` `Rect2`
	// is not moving.
	//constexpr inline Sweep2<T> sweep(const Rect2<T>& arg,
	//	const Vec2<T>& arg_delta, bool exclusive=false) const
	constexpr inline Sweep2<T> sweep(const Rect2<T>& arg,
		const Vec2<T>& arg_delta) const
	{
		//--------
		static const T
			EPSILON = T(1e-8);

		const Vec2<T>
			temp_cpos(cntr_pos()),
			temp_hsize(half_size()),

			temp_arg_cpos(arg.cntr_pos()),
			temp_arg_hsize(arg.half_size());

		Sweep2<T> ret;
		//--------
		if (arg_delta == Vec2<T>())
		{
			ret.pos.x = temp_arg_cpos.x;
			ret.pos.y = temp_arg_cpos.y;
			//ret.hit = intersect_fancy(arg, exclusive);
			ret.hit = intersect_fancy(arg);
			ret.tm
				= ret.hit
				? (ret.hit->tm == T(0))
				: T(Sweep2<T>::DIDNT_HIT_TM);

			return ret;
		}
		//--------
		//ret.hit = intersect_fancy
		//	(LineSeg2<T>{.p0=temp_arg_cpos, .p1=arg_delta},
		//	exclusive, temp_arg_hsize);
		ret.hit = intersect_fancy
			(LineSeg2<T>{.p0=temp_arg_cpos, .p1=arg_delta},
			temp_arg_hsize);

		if (ret.hit)
		{
			ret.tm = clamp
			(
				ret.hit->tm - EPSILON,
				T(0),
				T(1)
			);
			ret.pos.x = temp_arg_cpos.x + (arg_delta.x * ret.tm);
			ret.pos.y = temp_arg_cpos.y + (arg_delta.y * ret.tm);

			const Vec2<T>
				direction(arg_delta.norm());

			ret.hit->pos.x = clamp
			(
				ret.hit->pos.x + (direction.x * temp_arg_hsize.x),
				temp_cpos.x - temp_hsize.x,
				temp_cpos.x + temp_hsize.x
			);
			ret.hit->pos.y = clamp
			(
				ret.hit->pos.y + (direction.y * temp_arg_hsize.y),
				temp_cpos.y - temp_hsize.y,
				temp_cpos.y + temp_hsize.y
			);
		}
		else
		{
			ret.pos.x = temp_arg_cpos.x + arg_delta.x;
			ret.pos.y = temp_arg_cpos.y + arg_delta.y;
			ret.tm = Sweep2<T>::DIDNT_HIT_TM;
		}
		//--------
		return ret;
		//--------
	}
	template<template<typename, typename...> typename ContnrEtcT,
		typename... RemTs>
	//constexpr inline Sweep2<T> sweep_into
	//	(const ContnrEtcT<Rect2<T>, RemTs...>& coll_contnr,
	//	const Vec2<T>& self_delta, bool exclusive=false) const
	constexpr inline Sweep2<T> sweep_into
		(const ContnrEtcT<Rect2<T>, RemTs...>& coll_contnr,
		const Vec2<T>& self_delta) const
	{
		//--------
		//const Vec2<T>
		//	temp_cpos(cntr_pos());
		//--------
		Sweep2<T> nearest;
		//--------
		nearest.tm = T(Sweep2<T>::DIDNT_HIT_TM);
		//nearest.pos.x = temp_cpos.x + self_delta.x;
		//nearest.pos.y = temp_cpos.y + self_delta.y;
		nearest.pos = cntr_pos() + self_delta;

		//for (size_t i=0; i<coll_contnr.size(); ++i)
		for (const auto& item: coll_contnr)
		{
			//const Sweep2<T>
			//	temp_sweep(item.sweep(*this, self_delta, exclusive));
			const Sweep2<T>
				temp_sweep(item.sweep(*this, self_delta));
			if (temp_sweep.tm < nearest.tm)
			{
				nearest = temp_sweep;
			}
		}
		//--------
		return nearest;
		//--------
	}

	// These functions return whether or not the *argument* is inside this
	// `Rect2`.
	//constexpr inline bool arg_inside(const LineSeg2<T>& arg,
	//	bool exclusive=false, const Vec2<T>& arg_padding=Vec2<T>()) const
	constexpr inline bool arg_inside_fancy(const LineSeg2<T>& arg,
		const Vec2<T>& arg_padding=Vec2<T>()) const
	{
		//return intersect_fancy(arg.p0, exclusive, arg_padding)
		//	&& intersect_fancy(arg.p1, exclusive, arg_padding);
		return intersect_fancy(arg.p0, arg_padding)
			&& intersect_fancy(arg.p1, arg_padding);
	}
	template<bool exclusive=false>
	constexpr inline bool arg_inside(const Rect2& arg) const
	{
		return intersect<exclusive>(arg.tl_corner())
			&& intersect<exclusive>(arg.tr_corner())
			&& intersect<exclusive>(arg.bl_corner())
			&& intersect<exclusive>(arg.br_corner());
	}
	//constexpr inline bool arg_inside(const Rect2& arg,
	//	bool exclusive=false, const Vec2<T>& arg_padding=Vec2<T>()) const
	constexpr inline bool arg_inside_fancy(const Rect2& arg,
		const Vec2<T>& arg_padding=Vec2<T>()) const
	{
		//return intersect_fancy(arg.tl_corner(), exclusive, arg_padding)
		//	&& intersect_fancy(arg.tr_corner(), exclusive, arg_padding)
		//	&& intersect_fancy(arg.bl_corner(), exclusive, arg_padding)
		//	&& intersect_fancy(arg.br_corner(), exclusive, arg_padding);
		return intersect_fancy(arg.tl_corner(), arg_padding)
			&& intersect_fancy(arg.tr_corner(), arg_padding)
			&& intersect_fancy(arg.bl_corner(), arg_padding)
			&& intersect_fancy(arg.br_corner(), arg_padding);
	}
	//--------
};

template<typename T>
constexpr inline std::ostream& operator << (std::ostream& os,
	const Rect2<T>& arg)
{
	return misc_output::osprintout
	(
		os,
		"{",
			//arg.pos, " ",
			//arg.size_2d,

			//#define X(memb, dummy_arg) strings::sconcat( #memb , "{", arg . memb , "}" ),
			#define X(memb, dummy_arg) \
				strings::sconcat( #memb , arg . memb ),

			strings::strjoin2
			(
				std::string(" "),
				std::vector
				({
					MEMB_LIST_SHAPE_RECT2(X)
				})
			),

			#undef X
		"}"
	);
}

template<typename ShapeT, typename T=typename ShapeT::ElemT>
concept CanRect2Intersect = requires(ShapeT arg, Rect2<T> r2)
{
	{ r2.intersect(arg) } -> std::convertible_to<bool>;
};
template<typename ShapeT, typename T=typename ShapeT::ElemT>
concept CanRect2IntersectFancy
	= requires(ShapeT arg, Rect2<T> r2, Vec2<T> arg_padding)
{
	{ r2.intersect_fancy(arg, arg_padding) }
		-> std::convertible_to<Hit2<T>>;
};
//--------
//template<typename T>
//using MultiSweepElem
//	= std::variant
//	<
//		std::monostate,
//		Rect2<T>
//	>;
//template<typename T>
//constexpr inline Sweep2<T> multi_sweep_rect
//	(const auto& world_coll, const Rect2<T>& self,
//	const Vec2<T> self_delta);
//--------
} // namespace math
} // namespace liborangepower
//--------
//#include "../binser/serialize_funcs.hpp"
//--------
#endif		// liborangepower_math_shape_2d_classes_hpp
