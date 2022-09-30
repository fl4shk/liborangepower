#ifndef liborangepower_math_quadtree_class_hpp
#define liborangepower_math_quadtree_class_hpp

#include "shape_2d_classes.hpp"

namespace liborangepower
{
namespace math
{
//--------
template<typename T, template<typename> Alloc>
class Quadtree
{
//--------
public:		// types
	using QtreePtr
		//= std::unique_ptr<Quadtree<T, Alloc>>;
		= std::shared_ptr<Quadtree<T, Alloc>>;
	using QtreePtrV2d
		= std::vector<std::vector<std::unique_ptr<QtreePtr>>>;
//--------
public:		// 
};
//--------
} // namespace math
} // namespace liborangepower
#endif		// liborangepower_math_quadtree_class_hpp
