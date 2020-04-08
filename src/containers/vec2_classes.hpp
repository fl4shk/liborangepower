#ifndef liborangepower_containers_vec2_classes_hpp
#define liborangepower_containers_vec2_classes_hpp

#include "../gen_class_innards_defines.hpp"

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
	inline Vec2() = default;
	inline Vec2(const Type& s_x, const Type& s_y)
		: x(s_x), y(s_y)
	{
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Vec2);
	virtual ~Vec2() = default;

};

} // namespace containers

} // namespace liborangepower

#endif		// liborangepower_containers_vec2_classes_hpp
