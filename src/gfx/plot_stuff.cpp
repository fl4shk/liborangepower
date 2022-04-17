#include "plot_stuff.hpp"

namespace liborangepower
{
namespace gfx
{

std::vector<Vec2<i32>> bresenham(const Vec2<i32>& p0, const Vec2<i32>& p1)
{
	std::vector<Vec2<i32>> ret;

	const Vec2<i32> delta(std::abs(p1.x - p0.x) << 1,
		std::abs(p1.y - p0.y) << 1);
	const Vec2<i32> plus_amount((delta.x > 0) - (delta.x < 0),
		(delta.y > 0) - (delta.y < 0));

	Vec2<i32> p(p0);

	ret.push_back(p);

	if (delta.x >= delta.y)
	{
		i32 error = delta.y - (delta.x >> 1);

		while (p.x != p1.x)
		{
			if ((error > 0) || ((!error) && (plus_amount.x > 0)))
			{
				error -= delta.x;
				p.y += plus_amount.y;
			}

			error += delta.y;
			p.x += plus_amount.x;

			ret.push_back(p);
		}
	}
	else // if (delta.x < delta.y)
	{
		i32 error = delta.x - (delta.y >> 1);

		while (p.y != p1.y)
		{
			if ((error > 0) || ((!error) && (plus_amount.y > 0)))
			{
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

} // namespace gfx
} // namespace liborangepower
