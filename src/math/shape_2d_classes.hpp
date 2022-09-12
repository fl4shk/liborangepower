#ifndef liborangepower_math_shape_2d_classes_hpp
#define liborangepower_math_shape_2d_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_output_classes.hpp"
#include "../strings/sconcat_etc.hpp"

#include "../containers/std_hash_stuff.hpp"

//#include "../binser/serialize_funcs.hpp"
#include "../concepts/is_specialization_concepts.hpp"
#include "../concepts/math_concepts.hpp"

#include "misc_funcs.hpp"
#include "vec2_classes.hpp"

#include <cmath>
#include <cstdint>
#include <concepts>

namespace liborangepower
{

namespace binser
{
//--------
class Value;
//--------
};

namespace math
{
//--------
template<typename T>
class Hit2 final
{
public:		// types
	using ElemT = T;
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
	static inline Hit2 from_bv(const binser::Value& bv);
	inline operator binser::Value () const;
	//--------
};

template<typename T, typename CharT,
	typename Traits=std::char_traits<CharT>>
inline BasOstm<CharT, Traits>& operator << (BasOstm<CharT, Traits>& os,
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

			#define X(memb, dummy_arg) \
				arg . memb ,

			strings::strjoin2_rm_last
			(
				" ",
				MEMB_LIST_SHAPE_HIT2(X)
				std::string()
			),

			#undef X
		"}"
	);
}

template<typename T>
class Sweep2 final
{
public:		// types
	using ElemT = T;
public:		// variables
	#define MEMB_LIST_SHAPE_SWEEP2(X) \
		X(hit, std::nullopt) \
		X(pos, std::nullopt) \
		X(tm, std::nullopt) \

	std::optional<Hit2<T>> hit = std::nullopt;
	Vec2<T> pos;

	// This is a copy of `hit->time`, offset by epsiol=Ton, or 1 if the
	// object didn't hit anything during the sweep
	T tm = T(1);
public:		// functions
	//--------
	static inline Sweep2 from_bv(const binser::Value& bv);
	inline operator binser::Value () const;
	//--------
	constexpr inline T didnt_hit() const
	{
		return tm == T(1);
	}
	//--------
};

template
<
	typename T,
	typename CharT,
	typename Traits=std::char_traits<CharT>
>
inline BasOstm<CharT, Traits>& operator << (BasOstm<CharT, Traits>& os,
	const Sweep2<T>& arg)
{
	return misc_output::osprintout
	(
		os,
		"{",
			//arg.hit, " ",
			//arg.pos, " ",
			//arg.tm,

			#define X(memb, dummy_arg) \
				arg . memb ,

			strings::strjoin2_rm_last
			(
				" ",
				MEMB_LIST_SHAPE_SWEEP2(X)
				std::string()
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
	static inline LineSeg2 from_bv(const binser::Value& bv);
	inline operator binser::Value () const;
	//--------
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
	static inline Rect2 from_bv(const binser::Value& bv);
	inline operator binser::Value () const;
	//--------
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
		return size_2d / T(2);
	}

	constexpr inline T l_side_x() const
	{
		return pos.x;
	}
	constexpr inline T t_side_y() const
	{
		return pos.y;
	}
	constexpr inline T r_side_x() const
	{
		return pos.x + size_2d.x - T(1);
	}
	constexpr inline T b_side_y() const
	{
		return pos.y + size_2d.y - T(1);
	}

	constexpr inline Vec2<T> tl_corner() const
	{
		return Vec2<T>(l_side_x(), t_side_y());
	}
	constexpr inline Vec2<T> tr_corner() const
	{
		return Vec2<T>(r_side_x(), t_side_y());
	}
	constexpr inline Vec2<T> bl_corner() const
	{
		return Vec2<T>(l_side_x(), b_side_y());
	}
	constexpr inline Vec2<T> br_corner() const
	{
		return Vec2<T>(r_side_x(), b_side_y());
	}
	//--------
	// `ret.pos` and `ret.delta` will be set to the nearest edge of the
	// `Rect2`
	constexpr std::optional<Hit2<T>> intersect(const Vec2<T>& arg,
		const Vec2<T>& padding=Vec2<T>()) const
	{
		if (padding != Vec2<T>())
		{
			//return intersect(LineSeg2<T>{arg, arg}, padding);
			const Rect2<T>
				rect
				{
					.pos
					{
						arg.x - (padding / T(2)),
						arg.y - (padding / T(2)),
					},
					.size_2d=padding
				};

			return intersect(rect);
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
		if (px <= T(0))
		//if (px < T(0))
		{
			return std::nullopt;
		}

		const ElemT
			dy = arg.y - temp_cpos.y,
			py = temp_hsize.y - cstm_abs(dy);
		if (py <= T(0))
		//if (py < T(0))
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
	constexpr std::optional<Hit2<T>> intersect(const LineSeg2<T>& arg,
		const Vec2<T>& padding=Vec2<T>()) const
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
			//		{
			//			pi.x - (padding.x / T(2)),
			//			pi.y - (padding.y / T(2))
			//		},
			//		.size_2d
			//		{
			//			(pa.x - pi.x) + (padding.x / T(2)),
			//			(pa.y - pi.y) + (padding.y / T(2))
			//		},
			//	};

			Rect2<T> rect;

			if (arg.p0.x < arg.p1.x)
			{
				// In this case, we have `arg.p0.y == arg.p1.y`
				rect.pos.x = arg.p0.x - (padding.x / T(2));
				rect.pos.y = arg.p0.y - (padding.y / T(2));

				rect.size_2d.x = (arg.p1.x - arg.p0.x) + padding.x;
				rect.size_2d.y = padding.y;
			}
			else if (arg.p0.x == arg.p1.x)
			{
				if (arg.p0.y < arg.p1.y)
				{
					rect.pos.x = arg.p0.x - (padding.x / T(2));
					rect.pos.y = arg.p0.y - (padding.y / T(2));

					rect.size_2d.x = padding.x;
					rect.size_2d.y = (arg.p1.y - arg.p0.y) + padding.x;
				}
				else if (arg.p0.y == arg.p1.y)
				{
					rect.pos.x = arg.p0.x - (padding.x / T(2));
					rect.pos.y = arg.p0.y - (padding.y / T(2));

					rect.size_2d = padding;
				}
				else // if (arg.p0.y > arg.p1.y)
				{
					rect.pos.x = arg.p1.x - (padding.x / T(2));
					rect.pos.y = arg.p1.y - (padding.y / T(2));

					rect.size_2d.x = padding.x;
					rect.size_2d.y = (arg.p0.y - arg.p1.y) + padding.x;
				}
			}
			else // if (arg.p0.x > arg.p1.x)
			{
				// In this case, we have `arg.p0.y == arg.p1.y`
				rect.pos.x = arg.p1.x - (padding.x / T(2));
				rect.pos.y = arg.p0.y - (padding.y / T(2));

				rect.size_2d.x = (arg.p0.x - arg.p1.x) + padding.x;
				rect.size_2d.y = padding.y;
			}

			return intersect(rect);
		}
		//--------
		auto calc_scale = [](const Vec2<T>& some_delta) -> Vec2<T>
		{
			if constexpr (concepts::HasArithRecipMbrFunc<T>)
			{
				return
					typename Vec2<T>::CtorArgs
					{
						.x=some_delta.x.recip(),
						.y=some_delta.y.recip(),
					};
			}
			else
			{
				return
					typename Vec2<T>::CtorArgs
					{
						.x=T(1) / some_delta.x,
						.y=T(1) / some_delta.y,
					};
			}
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
			({
				.x=cstm_sign(scale.x),
				.y=cstm_sign(scale.y),
			}),
			partial_time_vec
			({
				.x=sign.x * (temp_hsize.x + padding.x),
				.y=sign.y * (temp_hsize.y + padding.y),
			}),
			near_time_vec
			({
				.x=(temp_cpos.x - partial_time_vec.x - arg.p0.x)
					* scale.x,
				.y=(temp_cpos.y - partial_time_vec.y - arg.p0.y)
					* scale.y,
			}),
			far_time_vec
			({
				.x=(temp_cpos.x + partial_time_vec.x - arg.p0.x)
					* scale.x,
				.y=(temp_cpos.y + partial_time_vec.y - arg.p0.y)
					* scale.y,
			});
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

		if (near_time >= T(1) || far_time <= T(0))
		// The below line is my modification, which may not be correct.
		// That is why I am not using it.
		//if (near_time > T(1) || far_time < T(0))
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
	constexpr std::optional<Hit2<T>> intersect(const Rect2& arg,
		const Vec2<T>& padding=Vec2<T>()) const
	{
		//--------
		const Rect2<T>
			temp_rect_0
			{
				.pos
				{
					pos.x - (padding.x / T(2)),
					pos.y - (padding.y / T(2))
				},
				.size_2d
				{
					size_2d.x + padding.x,
					size_2d.y + padding.y
				}
			},
			temp_rect_1
			{
				.pos
				{
					arg.pos.x - (padding.x / T(2)),
					arg.pos.y - (padding.y / T(2))
				},
				.size_2d
				{
					arg.size_2d.x + padding.x,
					arg.size_2d.y + padding.y
				}
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
		if (px <= T(0))
		//if (px < T(0))
		{
			return std::nullopt;
		}

		const T
			dy = temp_arg_cpos.y - temp_cpos.y,
			py = (temp_arg_hsize.y + temp_hsize.y) - cstm_abs(dy);
		if (py <= T(0))
		//if (py < T(0))
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

	// Whether or not the *argument* is inside this `Rect2`, inclusive
	inline bool arg_inside_inclusive(const LineSeg2<T>& arg,
		const Vec2<T>& padding=Vec2<T>()) const
	{
		return intersect(arg.p0, padding)
			&& intersect(arg.p1, padding);
	}
	inline bool arg_inside_inclusive(const Rect2& arg,
		const Vec2<T>& padding=Vec2<T>()) const
	{
		return intersect(arg.tl_corner(), padding)
			&& intersect(arg.tr_corner(), padding)
			&& intersect(arg.bl_corner(), padding)
			&& intersect(arg.br_corner(), padding);
	}
	//--------
};
//--------
} // namespace math
} // namespace liborangepower
//--------
#include "../binser/serialize_funcs.hpp"
//--------
namespace liborangepower
{
namespace math
{
//--------
template<typename T>
inline auto Hit2<T>::from_bv(const binser::Value& bv) -> Hit2
{
	Hit2 ret;

	MEMB_LIST_SHAPE_HIT2(BINSER_MEMB_FROM_BV_DESERIALIZE);

	return ret;
}

template<typename T>
inline Hit2<T>::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_SHAPE_HIT2(BINSER_MEMB_SERIALIZE);

	return ret;
}
//--------
template<typename T>
inline auto Sweep2<T>::from_bv(const binser::Value& bv) -> Sweep2
{
	Sweep2 ret;

	MEMB_LIST_SHAPE_SWEEP2(BINSER_MEMB_FROM_BV_DESERIALIZE);

	return ret;
}

template<typename T>
inline Sweep2<T>::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_SHAPE_SWEEP2(BINSER_MEMB_SERIALIZE);

	return ret;
}
//--------
template<typename T>
inline auto LineSeg2<T>::from_bv(const binser::Value& bv) -> LineSeg2
{
	LineSeg2 ret;

	MEMB_LIST_SHAPE_LINE_SEG2(BINSER_MEMB_FROM_BV_DESERIALIZE);

	return ret;
}

template<typename T>
inline LineSeg2<T>::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_SHAPE_LINE_SEG2(BINSER_MEMB_SERIALIZE);

	return ret;
}
//--------
template<typename T>
inline auto Rect2<T>::from_bv(const binser::Value& bv) -> Rect2
{
	Rect2 ret;

	MEMB_LIST_SHAPE_RECT2(BINSER_MEMB_FROM_BV_DESERIALIZE);

	return ret;
}

template<typename T>
inline Rect2<T>::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_SHAPE_RECT2(BINSER_MEMB_SERIALIZE);

	return ret;
}
//--------
} // namespace math
} // namespace liborangepower

#endif		// liborangepower_math_shape_2d_classes_hpp
