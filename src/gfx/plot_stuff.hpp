#ifndef liborangepower_gfx_plot_stuff_hpp
#define liborangepower_gfx_plot_stuff_hpp

#include "../gen_class_innards_defines.hpp"

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../math/vec2_classes.hpp"
#include "../math/shape_2d_classes.hpp"

#include <cstdlib>
#include <concepts>

namespace liborangepower {
using math::Vec2;
namespace gfx {
//--------
template<typename PosElemT=int32_t,
	typename Alloc=std::allocator<Vec2<PosElemT>>>
using PlotPosVec2Dynarr = std::vector<Vec2<PosElemT>, Alloc>;

template<typename GridElemT,
	template<typename> typename Alloc=std::allocator>
using PlotGridDynarr = std::vector<GridElemT, Alloc<GridElemT>>;
//--------
template<typename PosElemT=int32_t,
	template<typename> typename Alloc=std::allocator>
PlotPosVec2Dynarr<PosElemT, Alloc> bresenham_line(
	const Vec2<PosElemT>& p0, const Vec2<PosElemT>& p1,
	const std::optional<size_t>& max_num_iterations=std::nullopt
) {
	//std::vector<Vec2<PosElemT>, Alloc> ret;
	PlotPosVec2Dynarr<PosElemT, Alloc> ret;

	const Vec2<PosElemT> delta(std::abs(p1.x - p0.x) << 1,
		std::abs(p1.y - p0.y) << 1);
	const Vec2<PosElemT> plus_amount((delta.x > 0) - (delta.x < 0),
		(delta.y > 0) - (delta.y < 0));

	Vec2<PosElemT> p(p0);

	ret.push_back(p);

	if (delta.x >= delta.y) {
		PosElemT error = delta.y - (delta.x >> 1);

		while (
			p.x != p1.x
			&& (!max_num_iterations
				|| ret.size() <= (*max_num_iterations) + size_t(1))
		) {
			if ((error > 0) || ((!error) && (plus_amount.x > 0))) {
				error -= delta.x;
				p.y += plus_amount.y;
			}

			error += delta.y;
			p.x += plus_amount.x;

			ret.push_back(p);
		}
	} else { // if (delta.x < delta.y)
		PosElemT error = delta.x - (delta.y >> 1);

		while (
			p.y != p1.y
			&& (!max_num_iterations
				|| ret.size() <= (*max_num_iterations) + size_t(1))
		) {
			if ((error > 0) || ((!error) && (plus_amount.y > 0))) {
				error -= delta.y;
				p.x += plus_amount.x;
			}

			error += delta.x;
			p.y += plus_amount.y;

			ret.push_back(p);
		}
	}

	return ret;
}
//template<typename GridElemT, typename PosElemT=int32_t,
//	template<typename> typename Alloc=std::allocator>
//inline void flood_fill_tri(const math::Tri2<PosElemT>& tri);
//--------
} // namespace gfx
} // namespace liborangepower

#endif		// liborangepower_gfx_plot_stuff_hpp
