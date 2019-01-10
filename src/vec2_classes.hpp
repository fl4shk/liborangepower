#ifndef liborangepower_vec2_classes_hpp
#define liborangepower_vec2_classes_hpp

namespace liborangepower
{

namespace containers
{

template<typename Type>
class Vec2
{
public:		// variables
	Type x, y;

public:		// functions
	inline Vec2()
	{
	}
	inline Vec2(const Type& s_x, const Type& s_y)
		: x(s_x), y(s_y)
	{
	}

	inline Vec2(const Vec2& to_copy) = default;
	inline Vec2(Vec2&& to_move) = default;

	inline Vec2& operator = (const Vec2& to_copy) = default;
	inline Vec2& operator = (Vec2&& to_move) = default;
};

} // namespace containers

} // namespace liborangepower

#endif		// liborangepower_vec2_classes_hpp
