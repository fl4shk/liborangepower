#ifndef liborangepower_gfx_plot_stuff_hpp
#define liborangepower_gfx_plot_stuff_hpp

#include "../gen_class_innards_defines.hpp"

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../containers/vec2_classes.hpp"

#include <cstdlib>
#include <concepts>

namespace liborangepower
{

using containers::Vec2;

namespace gfx
{

std::vector<Vec2<int32_t>> bresenham(const Vec2<int32_t>& p0,
	const Vec2<int32_t>& p1);

} // namespace gfx
} // namespace liborangepower

#endif		// liborangepower_gfx_plot_stuff_hpp
