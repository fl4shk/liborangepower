#ifndef liborangepower_math_misc_types_hpp
#define liborangepower_math_misc_types_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_bitwise_funcs.hpp"
//#include "../containers/misc_templates.hpp"

namespace liborangepower
{
namespace math
{

using bitwise::width_of_type;

template<std::signed_integral IntT, std::signed_integral OtherIntT>
using SmallerInt
	= std::conditional_t<
		(width_of_type<IntT>() < width_of_type<OtherIntT>()),
		IntT, OtherIntT
	>;
template<std::unsigned_integral UIntT, std::unsigned_integral OtherUIntT>
using SmallerUInt
	= std::conditional_t<
		(width_of_type<UIntT>() < width_of_type<OtherUIntT>()),
		UIntT, OtherUIntT
	>;

template<std::signed_integral IntT, std::signed_integral OtherIntT>
using LargerInt
	= std::conditional_t<
		(width_of_type<IntT>() > width_of_type<OtherIntT>()),
		IntT, OtherIntT
	>;
template<std::unsigned_integral UIntT, std::unsigned_integral OtherUIntT>
using LargerUInt
	= std::conditional_t<
		(width_of_type<UIntT>() > width_of_type<OtherUIntT>()),
		UIntT, OtherUIntT
	>;

} // namespace math
} // namespace liborangepower

#endif		// liborangepower_math_misc_types_hpp
