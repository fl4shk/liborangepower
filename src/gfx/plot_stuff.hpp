#ifndef liborangepower_gfx_plot_stuff_hpp
#define liborangepower_gfx_plot_stuff_hpp

#include "../gen_class_innards_defines.hpp"

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../math/vec2_classes.hpp"
#include "../math/shape_2d_classes.hpp"
#include "../math/misc_funcs.hpp"

#include <cstdlib>
#include <concepts>

namespace liborangepower {
using math::Vec2;
using math::LineSeg2;
using math::Tri2;
using math::Rect2;
//using math::Vec2Dynarr;
namespace gfx {
//--------
//template<typename GridElT=int32_t,
//	template<typename> typename Alloc=std::allocator>
//using PlotGridElVec2Dynarr = std::vector<Vec2<GridElT>, Alloc<Vec2<GridElT>>>;

//template<typename GridElemT,
//	template<typename> typename Alloc=std::allocator>
//using PlotGridDynarr = std::vector<GridElemT, Alloc<GridElemT>>;
//template<typename GridElT=int32_t,
//	template<typename> typename Alloc=std::allocator>
//using StopCheckFunc = std::function<bool(
//	const Vec2Dynarr<GridElT, Alloc>&
//)>;
template<typename GridElT=int32_t>
using PlotFunc = std::function<bool(const Vec2<GridElT>&)>;

template<typename GridElT=int32_t>
void bresenham_line(
	//const Vec2<GridElT>& p0, const Vec2<GridElT>& p1,
	const LineSeg2<GridElT>& lseg,
	const PlotFunc<GridElT>& plot_func
	//const StopCheckFunc<GridElT, Alloc>& stop_check_func=nullptr
) {
	//std::vector<Vec2<GridElT>, Alloc> ret;
	//GridElVec2Dynarr ret;
	using GridElVec2 = Vec2<GridElT>;

	const GridElVec2
		delta
			(math::cstm_abs(lseg.p1.x - lseg.p0.x) * 2,
			math::cstm_abs(lseg.p1.y - lseg.p0.y) * 2),
		offset
			((delta.x > 0) - (delta.x < 0), (delta.y > 0) - (delta.y < 0));

	//std::cout << "bresenham_line(): "
	//	<< lseg.p0 << " " << lseg.p1
	//	<< "\n";

	//GridElVec2 p(lseg.p0);

	//ret.push_back(p);
	//plot_func(p);
	const GridElT
		min_x = math::min_va(lseg.p0.x, lseg.p1.x),
		max_x = math::max_va(lseg.p0.x, lseg.p1.x),
		min_y = math::min_va(lseg.p0.y, lseg.p1.y),
		max_y = math::max_va(lseg.p0.y, lseg.p1.y);
	if (lseg.p0 == lseg.p1) {
		//std::cout << "lseg.p0 == lseg.p1: "
		//	<< lseg.p0 << " " << lseg.p1
		//	<< "\n";
		plot_func(lseg.p0);
	} else if (lseg.p0.x == lseg.p1.x) {
		// Vertical line
		//std::cout << "Vertical line!\n";
		GridElVec2 p(lseg.p0);

		for (
			p.y=min_y;
			(p.y >= min_y) && (p.y <= max_y);
			//p.y+=offset.y
			++p.y
		) {
			plot_func(p);
		}
	} else if (lseg.p0.y == lseg.p1.y) {
		// Horizontal line
		//std::cout << "Horizontal line!\n";
		GridElVec2 p(lseg.p0);

		//plot_func(p);
		for (
			p.x=min_x;
			(p.x >= min_x) && (p.x <= max_x);
			//p.x+=offset.x
			++p.x
		) {
			plot_func(p);
		}
	} else if (delta.x >= delta.y) {
		//std::cout << "delta.x >= delta.y\n";
		GridElVec2 p(lseg.p0);

		GridElT error = delta.y - (delta.x >> 1);
		plot_func(p);

		while (
			p.x != lseg.p1.x
			//&& (!max_num_iterations
			//	|| ret.size() <= (*max_num_iterations) + size_t(1))
			//&& (!stop_check_func || stop_check_func(ret))
		) {
			if (error > 0 || (!error && offset.x > 0)) {
				error -= delta.x;
				p.y += offset.y;
			}

			error += delta.y;
			p.x += offset.x;

			//ret.push_back(p);
			if (!plot_func(p)) {
				//std::cout << "delta.x >= delta.y: Eek! " << p << "\n";
				break;
			}
		}
	} else { // if (delta.x < delta.y)
		//std::cout << "delta.x < delta.y\n";
		GridElVec2 p(lseg.p0);

		GridElT error = delta.x - (delta.y >> 1);
		plot_func(p);

		while (
			p.y != lseg.p1.y
			//&& (!max_num_iterations
			//	|| ret.size() <= (*max_num_iterations) + size_t(1))
			//&& (!stop_check_func || stop_check_func(ret))
		) {
			if (error > 0 || (!error && offset.y > 0)) {
				error -= delta.y;
				p.x += offset.x;
			}

			error += delta.x;
			p.y += offset.y;

			//ret.push_back(p);
			if (!plot_func(p)) {
				//std::cout << "delta.x < delta.y: Eek! " << p << "\n";
				break;
			}
		}
	}
	//if (delta.x >= delta.y) {
	//	GridElVec2
	//} else { // if (delta.x < delta.y)
	//}

	//return ret;
}
template<typename GridElT=int32_t>
inline void bresenham_line(
	const Vec2<GridElT>& p0, const Vec2<GridElT>& p1,
	const std::function<bool(const Vec2<GridElT>&)>& plot_func
) {
	bresenham_line(LineSeg2<GridElT>{.p0=p0, .p1=p1}, plot_func);
}

//template<typename GridElT=int32_t,
//	typename PhysElT=long double>
//void flood_fill_old(
//	const Tri2<GridElT>& tri2,
//	const PlotFunc<GridElT>& plot_func
//) {
//	// This is based on
//	// http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
//	//--------
//	//const LineSeg2<GridElT>
//	//	lseg_0_1(tri2.p0, tri2.p1),
//	//	lseg_1_2(tri2.p1, tri2.p2),
//	//	lseg_2_0(tri2.p2, tri2.p0);
//	using GridElVec2 = Vec2<GridElT>;
//	using GridElTri2 = Tri2<GridElT>;
//	//using PhysElVec2 = Vec2<PhysElT>;
//	//--------
//	//// Insertion sort in ascending order by y
//	GridElTri2 sorted = tri2;
//	for (int i=1; i<int(tri2.size()); ++i) {
//		int j = i - 1;
//		const GridElVec2& key = tri2.at(i);
//		while (j >= 0 && sorted.at(j).y > key.y) {
//			sorted.at(j + 1) = sorted.at(j);
//			--j;
//		}
//		sorted.at(j + 1) = key;
//	}
//	//std::cout
//	//	<< sorted.p0 << " "
//	//	<< sorted.p1 << " "
//	//	<< sorted.p2
//	//	<< std::endl;
//	//--------
//	auto fill_bottom_flat = [&plot_func](
//		const GridElVec2& p0, const GridElVec2& p1, const GridElVec2& p2
//	) -> void {
//		const PhysElT
//			inv_slope_0_raw_scale = PhysElT(p1.y - p0.y),
//			inv_slope_0
//				= ((inv_slope_0_raw_scale != PhysElT(0))
//				? (PhysElT(p1.x - p0.x) / inv_slope_0_raw_scale)
//				: PhysElT(0)),
//			inv_slope_1_raw_scale = PhysElT(p2.y - p0.y),
//			inv_slope_1
//				= ((inv_slope_1_raw_scale != PhysElT(0))
//				? (PhysElT(p2.x - p0.x) / inv_slope_1_raw_scale)
//				: PhysElT(0));
//
//		PhysElT
//			curr_x_0 = p0.x,
//			curr_x_1 = p0.x;
//
//		for (GridElT scanline_y=p0.y; scanline_y<=p1.y; ++scanline_y) {
//			bresenham_line
//				(GridElVec2(curr_x_0, scanline_y),
//				GridElVec2(curr_x_1, scanline_y), 
//				plot_func);
//			curr_x_0 += inv_slope_0;
//			curr_x_1 += inv_slope_1;
//		}
//	};
//	auto fill_top_flat = [&plot_func](
//		const GridElVec2& p0, const GridElVec2& p1, const GridElVec2& p2
//	) -> void {
//		const PhysElT
//			inv_slope_0_raw_scale = PhysElT(p2.y - p0.y),
//			inv_slope_0
//				= ((inv_slope_0_raw_scale != PhysElT(0))
//				? PhysElT(p2.x - p0.x) / inv_slope_0_raw_scale
//				: PhysElT(0)),
//			inv_slope_1_raw_scale = PhysElT(p2.y - p1.y),
//			inv_slope_1
//				= ((inv_slope_1_raw_scale != PhysElT(0))
//				? PhysElT(p2.x - p1.x) / inv_slope_1_raw_scale
//				: PhysElT(0));
//
//		PhysElT
//			curr_x_0 = p2.x,
//			curr_x_1 = p2.x;
//
//		for (GridElT scanline_y=p2.y; scanline_y>p0.y; --scanline_y) {
//			bresenham_line
//				(GridElVec2(curr_x_0, scanline_y),
//				GridElVec2(curr_x_1, scanline_y), 
//				plot_func);
//			curr_x_0 -= inv_slope_0;
//			curr_x_1 -= inv_slope_1;
//		}
//	};
//	//--------
//	const auto
//		& p0 = sorted.p0,
//		& p1 = sorted.p1,
//		& p2 = sorted.p2;
//	if (p1.y == p2.y) {
//		fill_bottom_flat(p0, p1, p2);
//	} else if (p0.y == p1.y) {
//		fill_top_flat(p0, p1, p2);
//	} else {
//		const GridElVec2 p3
//			(p0.x
//				+ (
//					(PhysElT(p1.y - p0.y) / PhysElT(p2.y - p0.y)) 
//					* (p2.x - p0.x)
//				),
//			p1.y);
//		fill_bottom_flat(p0, p1, p3);
//		fill_top_flat(p1, p3, p2);
//	}
//	//--------
//}
//template<typename GridElT=int32_t>
//void flood_fill(
//	const Rect2<GridElT>& rect2,
//	const PlotFunc<GridElT>& plot_func
//) {
//}
//--------
//--------
//template<typename GridElTarg=int32_t,
//	template<typename> typename Alloc=std::allocator>
//class Plot final {
//public:		// types
//	//--------
//	using GridElT = GridElTarg;
//	//using GridElVec2 = Vec2<GridElT>;
//	using GridElVec2Dynarr = Vec2Dynarr<GridElT>;
//	using StopCheckFunc = std::function<bool(const GridElVec2Dynarr&)>;
//	//--------
//public:		// functions
//};
//--------
//template<typename GridElemT, typename GridElT=int32_t,
//	template<typename> typename Alloc=std::allocator>
//inline void flood_fill_tri(const math::Tri2<GridElT>& tri);
//--------
} // namespace gfx
} // namespace liborangepower

#endif		// liborangepower_gfx_plot_stuff_hpp
