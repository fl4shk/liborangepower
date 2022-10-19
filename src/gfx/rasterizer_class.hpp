#ifndef liborangepower_gfx_rasterizer_class_hpp
#define liborangepower_gfx_rasterizer_class_hpp

#include "../misc/misc_includes.hpp"
#include "../math/shape_2d_classes.hpp"
#include "plot_stuff.hpp"

namespace liborangepower {
using math::Vec2;
using math::Tri2;
namespace gfx {
//--------
template<typename ColorTarg,
	typename GridElTarg=int32_t>
class Edge final {
	// Based on https://joshbeam.com/articles/triangle_rasterization/
public:		// types
	using ColorT = ColorTarg;
	using ColorVec2 = Vec2<ColorT>;
	//using ColorLineSeg2 = LineSeg2<ColorT>;
	using GridElT = GridElTarg;
	using GridElVec2 = Vec2<GridElT>;
	//using GridElLineSeg2 = LineSeg2<GridElT>;
private:		// variables
	ColorT _col0;
	GridElVec2 _p0;
	ColorT _col1;
	GridElVec2 _p1;
	//ExtPt p0, p1;
public:		// functions
	constexpr inline Edge() = default;
	constexpr inline Edge(
		const ColorT& some_col0, const GridElVec2& some_p0,
		const ColorT& some_col1, const GridElVec2& some_p1
	) {
		if (some_p0.y < some_p1.y) {
			_col0 = s_col0;
			_p0 = some_p0;
			_col1 = s_col1;
			_p1 = some_p1;
		} else { // if (some_p0.y >= some_p1.y)
			_col0 = s_col1;
			_p0 = some_p1;
			_col1 = s_col0;
			_p1 = some_p0;
		}
	}
	GEN_CX_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Edge);
	constexpr inline ~Edge() = default;
	GEN_GETTER_BY_CON_REF(col0);
	GEN_GETTER_BY_CON_REF(p0);
	GEN_GETTER_BY_CON_REF(col1);
	GEN_GETTER_BY_CON_REF(p1);
};
//--------
template<typename ColorTarg,
	typename GridElTarg=int32_t>
class Rasterizer {
public:		// types
	using ColorT = ColorTarg;
	using ColorVec2 = Vec2<ColorT>;
	//using ColorLineSeg2 = LineSeg2<ColorT>;
	using GridElT = GridElTarg;
	using GridElVec2 = Vec2<GridElT>;
	//using GridElLineSeg2 = LineSeg2<GridElT>;
};
//--------
} // namespace gfx
} // namespace liborangepower

#endif		// liborangepower_gfx_rasterizer_class_hpp
