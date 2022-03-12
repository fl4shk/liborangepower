#ifndef liborangepower_json_stuff_json_concepts_hpp
#define liborangepower_json_stuff_json_concepts_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/misc_concepts.hpp"

#include <memory>
#include <unordered_map>

// jsoncpp headers
#include <json/value.h>

namespace liborangepower
{
namespace json
{

using liborangepower::concepts::IsDerivedAndHasStaticKindStr;

template<typename T>
concept HasJvDeserializeFunc = requires(T obj, const Json::Value& jv)
{
	{ obj.deserialize(jv) } -> std::same_as<void>;
};

template<typename DerivedT, typename BaseT>
concept IsValidFromJvFactoryT
	= IsDerivedAndHasStaticKindStr<DerivedT, BaseT> 
	&& requires(const Json::Value& jv)
{
	//std::declval<DerivedT>(jv);
	DerivedT(jv);
};

//template<typename T, typename BaseT>
//concept IsFromJvFactoryFunc = std::same_as<T,
//	std::function<std::unique_ptr<BaseT>(const Json::Value&)>>;

//template<typename T, typename BaseT>
//concept IsFromJvFactoryFuncMap = std::same_as


} // namespace json
} // namespace liborangepower

#endif		// liborangepower_json_stuff_json_concepts_hpp
