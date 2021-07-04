#ifndef liborangepower_containers_vec3_classes_hpp
#define liborangepower_containers_vec3_classes_hpp

namespace liborangepower
{

namespace containers
{

template<typename Type>
class Vec3
{
public:		// variables
	Type x = 0, y = 0, z = 0;
public:		// functions
	inline Vec3() = default;
	inline Vec3(const Type& s_x, const Type& s_y, const Type& s_z)
		: x(s_x), y(s_y), z(s_z)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Vec3);
	virtual inline ~Vec3() = default;
};

} // namespace containers

} // namespace liborangepower
#endif		// liborangepower_containers_vec3_classes_hpp

