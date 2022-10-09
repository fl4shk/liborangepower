#ifndef liborangepower_binser_binser_concepts_hpp
#define liborangepower_binser_binser_concepts_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/misc_concepts.hpp"

#include "value_class.hpp"

#include <memory>
#include <unordered_map>

namespace liborangepower {
namespace binser {
//--------
using liborangepower::concepts::IsDerivedAndHasStaticKindStr;

template<typename T>
concept HasBvDeserializeFunc = requires(T obj, const Value& bv) {
	{ obj.deserialize(bv) } -> std::same_as<void>;
};

template<typename DerivedT, typename BaseT>
concept IsValidFromBvFactoryT
= IsDerivedAndHasStaticKindStr<DerivedT, BaseT> 
&& requires(const Value& bv) {
	//std::declval<DerivedT>(bv);
	DerivedT(bv);
};

//template<typename T, typename BaseT>
//concept IsFromBvFactoryFunc = std::same_as<T,
//	std::function<std::unique_ptr<BaseT>(const Value&)>>;

//template<typename T, typename BaseT>
//concept IsFromBvFactoryFuncMap = std::same_as
//--------
} // namespace binser
} // namespace liborangepower

#endif		// liborangepower_binser_binser_concepts_hpp
