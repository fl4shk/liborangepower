#ifndef liborangepower_json_stuff_from_jv_factory_stuff_hpp
#define liborangepower_json_stuff_from_jv_factory_stuff_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/misc_concepts.hpp"

#include <map>

// jsoncpp headers
#include <json/value.h>

namespace liborangepower
{
namespace json
{

using liborangepower::concepts::IsDerivedAndHasStaticKindStr;
template<typename DerivedT, typename BaseT>
concept IsValidFromJvFactoryT
	= IsDerivedAndHasStaticKindStr<DerivedT, BaseT> 
	&& requires(const Json::Value& jv)
{
	DerivedT(jv);
};

template<typename BaseT>
class FromJvFactory final
{
public:		// types
	using Func
		= std::function<std::unique_ptr<BaseT>(const Json::Value&)>;
	using FuncMap = std::map<std::string, Func>;
public:		// functions
	// Create a `FuncMap` that maps each derived type's `KIND_STR` to a
	// lambda function that generates an `std::unique_ptr<BaseT>` that
	// points to a `new FirstDerivedT(jv)`.
	template<IsValidFromJvFactoryT<BaseT> FirstDerivedT,
		IsValidFromJvFactoryT<BaseT>... RemDerivedTs>
	static FuncMap gen_func_map()
	{
		FuncMap ret;

		if constexpr (sizeof...(RemDerivedTs) > 0)
		{
			ret = gen_func_map<RemDerivedTs...>();
		}

		//ret[FirstDerivedT::KIND_STR] = Func(FirstDerivedT::from_jv);
		ret[FirstDerivedT::KIND_STR]
			= Func
			(
				[](const Json::Value& jv) -> std::unique_ptr<BaseT>
				{
					return std::unique_ptr<BaseT>
						(new FirstDerivedT(jv));
				}
			);

		return ret;
	}
};

} // namespace json
} // namespace liborangepower

#endif		// liborangepower_json_stuff_from_jv_factory_stuff_hpp
