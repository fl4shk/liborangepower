#ifndef liborangepower_math_vec2_classes_hpp
#define liborangepower_math_vec2_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_output_funcs.hpp"
#include "../strings/sconcat_etc.hpp"

#include "../gen_class_innards_defines.hpp"
#include "../concepts/is_specialization_concepts.hpp"
#include "../concepts/math_concepts.hpp"
#include "../containers/std_hash_stuff.hpp"
#include "misc_funcs.hpp"

#include <cmath>
#include <cstdint>
#include <concepts>

namespace liborangepower {
namespace math {
//--------
template<typename T>
concept HasElemT = requires {
	{ std::declval<typename T::ElemT>() };
};

//template<typename Vec2T, typename OtherVec2T>
//concept LikeVec2
//= HasElemT<Vec2T>
//&& requires(OtherVec2T other) {
//	{ other.x } -> std::convertible_to<typename Vec2T::ElemT>;
//	{ other.y } -> std::convertible_to<typename Vec2T::ElemT>;
//};

template<typename T>
class Vec2 {
public:		// types
	using ElemT = T;

	//enum class Ind {
	//	IndX = 0,
	//	IndY = 1,
	//	Lim
	//};

	//template<std::convertible_to<T> OtherElemT>
	//using CexprMapFunc
	//	= std::function<constexpr Vec2(
	//		const Vec2&, const Vec2<OtherElemT>&
	//	)>;
	//template<std::convertible_to<T> OtherElemT>
	//using MapFunc
	//	= std::function<Vec2(const Vec2&, const Vec2<OtherElemT>&)>;
public:		// constants
	static constexpr size_t
		IND_X = 0,
		IND_Y = 1,
		SIZE = 2;
public:		// variables
	#define MEMB_MAIN_LIST_VEC2(X) \
		X(x, std::nullopt) \
		X(y, std::nullopt)
	#define MEMB_LIST_VEC2(X) \
		MEMB_MAIN_LIST_VEC2(X)

	T
		x = T(),
		y = T();
public:		// functions
	//--------
	//template<std::convertible_to<T> OtherElemT>
	//constexpr inline operator Vec2<OtherElemT> () const {
	//	return Vec2<OtherElemT>(T(x), T(y));
	//}
	//template<std::convertible_to<T> OtherElemT>
	//constexpr inline Vec2<T> map (
	//	const CexprMapFunc<OtherElemT>& map_func,
	//	const Vec2<OtherElemT>& other) const {
	//}

	template<typename OtherElemT>
	explicit constexpr inline operator Vec2<OtherElemT> () const
	requires std::convertible_to<T, OtherElemT> {
		//return Vec2<OtherElemT>(OtherElemT(x), OtherElemT(y));
		Vec2<OtherElemT> ret;

		//#define X(name, dummy_arg) ret.name = std::remove_cvref_t<decltype(ret.name)>(name);
		//MEMB_LIST_VEC2(X);
		//#undef X
		//for (size_t i=0; i<size(); ++i) {
		//	ret.at(i) = OtherElemT(at(i));
		//}
		for (size_t i=0; i<size(); ++i) {
			ret.at(i) = std::remove_cvref_t<decltype(ret.at(i))>(at(i));
		}

		return ret;
	}
	//--------
	static constexpr inline size_t size() {
		return SIZE;
	}
	constexpr inline T& at(size_t where) {
		switch (where) {
		//--------
		case IND_X:
			return x;
		case IND_Y:
			return y;
		default:
			throw std::invalid_argument(strings::sconcat(
				"liborangepower::math::Vec2::at(): Error: ",
				"bad `where` argument: ",
				where
			));
		//--------
		}
	}
	constexpr inline const T& at(size_t where) const {
		switch (where) {
		//--------
		case IND_X:
			return x;
		case IND_Y:
			return y;
		default:
			throw std::invalid_argument(strings::sconcat(
				"liborangepower::math::Vec2::at(): Error: ",
				"bad `where` argument: ",
				where
			));
		//--------
		}
	}
	//--------
	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec2 operator + (
		const Vec2<OtherElemT>& other
	) const {
		//return Vec2<T>({.x=x + other.x, .y=y + other.y});
		//return Vec2<T>(x + other.x, y + other.y);
		//Vec2<T> ret;
		//ret.x = x + other.x;
		//ret.y = y + other.y;

		Vec2<T> ret;
		//#define X(name, dummy_arg) ret.name = name + other.name;
		//MEMB_MAIN_LIST_VEC2(X);
		//#undef X

		for (size_t i=0; i<size(); ++i) {
			ret.at(i) = at(i) + other.at(i);
		}
		return ret;
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec2& operator += (
		const Vec2<OtherElemT>& other
	) const {
		*this = *this + other;
		return *this;
	}

	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec2 operator - (
		const Vec2<OtherElemT>& other
	) const {
		//return Vec2<T>({.x=x - other.x, .y=y - other.y});
		//return Vec2<T>(x - other.x, y - other.y);
		//Vec2<T> ret;
		//ret.x = x - other.x;
		//ret.y = y - other.y;
		//return ret;
		Vec2<T> ret;
		//#define X(name, dummy_arg) ret.name = name - other.name;
		//MEMB_MAIN_LIST_VEC2(X);
		//#undef X
		for (size_t i=0; i<size(); ++i) {
			ret.at(i) = at(i) - other.at(i);
		}
		return ret;
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline Vec2& operator -= (
		const Vec2<OtherElemT>& other
	) const {
		*this = *this - other;
		return *this;
	}

	constexpr inline Vec2 operator - () const {
		//return Vec2<T>({.x=-x, .y=-y});
		//return Vec2<T>(-x, -y);
		//Vec2<T> ret;
		//ret.x = -x;
		//ret.y = -y;
		//return ret;

		Vec2<T> ret;
		//#define X(name, dummy_arg) ret.name = -name;
		//MEMB_MAIN_LIST_VEC2(X);
		//#undef X
		for (size_t i=0; i<size(); ++i) {
			ret.at(i) = -at(i);
		}
		return ret;
	}

	template<std::convertible_to<T> ScaleT>
	constexpr inline Vec2 operator * (const ScaleT& scale) const {
		//return Vec2<T>({.x=x * scale, .y=y * scale});
		//return Vec2<T>(x * scale, y * scale);
		//Vec2<T> ret;
		//ret.x = x * scale;
		//ret.y = y * scale;
		//return ret;

		Vec2<T> ret;
		//#define X(name, dummy_arg) ret.name = name * scale;
		//MEMB_MAIN_LIST_VEC2(X);
		//#undef X
		for (size_t i=0; i<size(); ++i) {
			ret.at(i) = at(i) * scale;
		}
		return ret;
	}
	template<std::convertible_to<T> ScaleT>
	constexpr inline Vec2& operator *= (const ScaleT& other) const {
		*this = *this * other;
		return *this;
	}

	template<std::convertible_to<T> ScaleT>
	constexpr inline Vec2 operator / (const ScaleT& scale) const {
		//return Vec2<T>({.x=x / scale, .y=y / scale});
		//return Vec2<T>(x / scale, y / scale);
		//Vec2<T> ret;
		//ret.x = x / scale;
		//ret.y = y / scale;
		//return ret;

		Vec2<T> ret;
		//#define X(name, dummy_arg) ret.name = name / scale;
		//MEMB_MAIN_LIST_VEC2(X);
		//#undef X
		for (size_t i=0; i<size(); ++i) {
			ret.at(i) = at(i) / scale;
		}
		return ret;
	}
	template<std::convertible_to<T> ScaleT>
	constexpr inline Vec2& operator /= (const ScaleT& scale) const {
		*this = *this / scale;
		return *this;
	}

	constexpr inline Vec2 sign() const {
		Vec2<T> ret;
		for (size_t i=0; i<size(); ++i) {
			ret.at(i) = cstm_sign(at(i));
		}
		return ret;
	}
	constexpr inline Vec2 div_2() const {
		//return Vec2({.x=math::div_2(x), .y=math::div_2(y)});
		//return Vec2<T>(math::div_2(x), math::div_2(y));
		//Vec2 ret;
		//ret.x = math::div_2(x);
		//ret.y = math::div_2(y);
		//return ret;
		Vec2<T> ret;
		//#define X(name, dummy_arg) ret.name = div_2(name);
		//MEMB_MAIN_LIST_VEC2(X);
		//#undef X
		for (size_t i=0; i<size(); ++i) {
			ret.at(i) = math::div_2(at(i));
		}
		return ret;
	}
	constexpr inline Vec2 recip() const {
		//return Vec2({.x=math::recip(x), .y=math::recip(y)});
		//return Vec2(math::recip(x), math::recip(y));
		//Vec2 ret;
		//ret.x = math::recip(x);
		//ret.y = math::recip(y);
		//return ret;
		Vec2<T> ret;
		//#define X(name, dummy_arg) ret.name = recip(name);
		//MEMB_MAIN_LIST_VEC2(X);
		//#undef X
		for (size_t i=0; i<size(); ++i) {
			ret.at(i) = math::recip(at(i));
		}
		return ret;
	}
	//--------
	// Dot product
	template<std::convertible_to<T> OtherElemT>
	constexpr inline T dot(const Vec2<OtherElemT>& other) const {
		//return T((x * other.x) + (y * other.y));
		//const T ret = (x * other.x) + (y * other.y);

		T ret = T();
		//#define X(name, dummy_arg) ret += name * other.name;
		//MEMB_MAIN_LIST_VEC2(X);
		//#undef X
		for (size_t i=0; i<size(); ++i) {
			ret += at(i) * other.at(i);
		}
		return ret;
	}

	// Z component of a 3D cross product, which is computed as if *this and
	// to_zcross have been converted to 3D vectors with Z components of zero
	template<std::convertible_to<T> OtherElemT>
	constexpr inline T zcross(const Vec2<OtherElemT>& other) const {
		//return T((x * other.y) - (y * other.x));
		const T ret = (x * other.y) - (y * other.x);
		return ret;
	}

	constexpr inline T magnitude() const {
		//return std::sqrt(dot(*this));
		return math::cstm_sqrt(dot(*this));
	}
	constexpr inline Vec2<T> norm() const {
		return *this / magnitude();
	}
	//--------
	// Templates can't be defaulted for some reason
	//template<std::convertible_to<T> OtherElemT>
	//inline auto operator <=> (const Vec2<OtherElemT>& other) const
	//	= default;
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator == (
		const Vec2<OtherElemT>& other
	) const {
		//return x == other.x && y == other.y;
		bool ret = true;
		for (size_t i=0; i<size(); ++i) {
			ret = ret && (at(i) == other.at(i));
		}
		return ret;
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator != (
		const Vec2<OtherElemT>& other
	) const {
		return !(*this == other);
	}

	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator < (
		const Vec2<OtherElemT>& other
	) const {
		return y < other.y || (y == other.y && x < other.x);
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator > (
		const Vec2<OtherElemT>& other
	) const {
		return y > other.y || (y == other.y && x > other.x);
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator <= (
		const Vec2<OtherElemT>& other
	) const {
		return !(*this > other);
	}
	template<std::convertible_to<T> OtherElemT>
	constexpr inline bool operator >= (
		const Vec2<OtherElemT>& other
	) const {
		return !(*this < other);
	}
	//--------
};

template<typename T, std::convertible_to<T> ScaleT>
constexpr inline Vec2<T> operator * (const ScaleT& scale,
	const Vec2<T>& self) {
	//return Vec2<T>({.x=scale * self.x, .y=scale * self.y});

	//return Vec2<T>(
	//	scale * self.x,
	//	scale * self.y
	//);

	//Vec2<T> ret;
	//ret.x = scale * self.x;
	//ret.y = scale * self.y;
	//return ret;
	//return self * scale;

	Vec2<T> ret;
	for (size_t i=0; i<self.size(); ++i) {
		ret.at(i) = scale * self.at(i);
	}
	return ret;
}
template<typename T, std::convertible_to<T> ScaleT>
constexpr inline Vec2<T> operator / (const ScaleT& inv_scale,
	const Vec2<T>& self) {
	//return Vec2<T>({.x=inv_scale / self.x, .y=inv_scale / self.y});
	//return Vec2<T>(
	//	inv_scale / self.x,
	//	inv_scale / self.y
	//);
	//Vec2<T> ret;
	//ret.x = inv_scale / self.x;
	//ret.y = inv_scale / self.y;
	//return ret;

	Vec2<T> ret;
	for (size_t i=0; i<self.size(); ++i) {
		ret.at(i) = inv_scale / self.at(i);
	}
	return ret;
}

template<typename T>
constexpr inline std::ostream& operator << (
	std::ostream& os, const Vec2<T>& arg
) {
	return misc_output::osprintout(
		os, "{",
			//arg.x, ", ",
			//arg.y,

			#define X(memb, dummy_arg) strings::sconcat( arg . memb ),

			strings::strjoin2(
				//std::string(", "),
				", ",
				std::vector<std::string>({
					//strings::sconcat<CharT, Traits>(arg.x),
					//strings::sconcat<CharT, Traits>(arg.y)
					MEMB_LIST_VEC2(X)
					//strings::sconcat(arg.x),
					//strings::sconcat(arg.y)
				})
			),

			#undef X
		"}"
	);

	//misc_output::osprintout(os, "{");

	//#define X(memb, dummy_arg) misc_output::osprintout(os, ( arg . memb ));
	//MEMB_LIST_VEC2(X)
	//#undef X

	//misc_output::osprintout(os, "}");
}

//template<typename T>
//extern uint32_t _is_vec2_func(const Vec2<T>&);
//template<typename T>
//extern uint8_t _is_vec2_func(const T&);
//
//template<typename T>
//constexpr inline bool is_vec2() {
//	return (sizeof(_is_vec2_func(std::declval<T>()))
//		== sizeof(uint32_t));
//}
//template<typename T>
//constexpr inline bool is_vec2() {
//	return misc_util::is_specialization<T, Vec2>();
//}

//GEN_IS_SPECIALIZATION_CHECK_FUNCS_RTYPES(is_vec2, Vec2);
//template<typename T>
//constexpr inline bool is_vec2() {
//	GEN_IS_SPECIALIZATION_FUNC_CONTENTS(is_vec2);
//}
template<typename T>
constexpr inline bool is_vec2() {
	return concepts::is_specialization<T, Vec2>();
}
template<typename PosElT=int32_t,
	template<typename> typename Alloc=std::allocator>
using Vec2Dynarr = std::vector<Vec2<PosElT>, Alloc<Vec2<PosElT>>>;

} // namespace math
} // namespace liborangepower

namespace std {
template<typename T>
struct hash<liborangepower::math::Vec2<T>> {
	std::size_t operator () (const liborangepower::math::Vec2<T>& vec2)
		const noexcept {
		//return liborangepower::containers::hash_va(vec2.x, vec2.y);
		#define X(name, dummy_arg) \
			liborangepower::containers::hash_va(vec2 . name ),
		return liborangepower::containers::hash_merge(
			std::vector<size_t>({
				MEMB_LIST_VEC2(X)
			}));
		#undef X
	}
};
} // namespace std

#endif		// liborangepower_math_vec2_classes_hpp
