#ifndef liborangepower_containers_misc_templates_hpp
#define liborangepower_containers_misc_templates_hpp

#include "../misc/misc_includes.hpp"

namespace liborangepower {
namespace containers {
//--------
template<bool cond, typename FirstT, typename SecondT>
class Pick final {
public:		// types
	using Type = FirstT;
};

template<typename FirstT, typename SecondT>
class Pick<false, FirstT, SecondT> {
public:		// types
	using Type = SecondT;
};

template<bool cond, typename FirstT, typename SecondT>
using PickT = typename Pick<cond, FirstT, SecondT>::Type;

// I considered this, but deemed it too much
//template<
//	std::integral IntT,
//	std::unsigned_integral UnsgnChoiceT,
//	std::signed_integral SgnChoiceT
//>
//using PickSignOfIntT 
//	= PickT<
//		std::unsigned_integral<IntT>,
//		UnsgnChoiceT,
//		SgnChoiceT
//	>;
//--------
} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_misc_templates_hpp
