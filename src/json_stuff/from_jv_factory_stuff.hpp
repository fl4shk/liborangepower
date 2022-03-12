#ifndef liborangepower_json_stuff_from_jv_factory_stuff_hpp
#define liborangepower_json_stuff_from_jv_factory_stuff_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/misc_concepts.hpp"

#include "json_concepts.hpp"

// jsoncpp headers
#include <json/value.h>

namespace liborangepower
{
namespace json
{

template<typename BaseT>
class FromJvFactory final
{
public:		// types
	using Func = std::function<std::unique_ptr<BaseT>(const Json::Value&)>;
	using FuncMap = std::unordered_map<std::string, Func>;
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
					if constexpr (std::is_constructible
						<FirstDerivedT, Json::Value>())
					{
						return std::unique_ptr<BaseT>
							(new FirstDerivedT(jv));
					}
					else
					{
						return std::unique_ptr<BaseT>
							(new FirstDerivedT
								(FirstDerivedT::from_jv(jv)));
					}
				}
			);

		return ret;
	}
};

} // namespace json
} // namespace liborangepower

#endif		// liborangepower_json_stuff_from_jv_factory_stuff_hpp
