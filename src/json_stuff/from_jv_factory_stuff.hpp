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

using liborangepower::concepts::DerivedAndHasStaticKindStr;
template<typename DerivedType, typename BaseType>
concept IsValidFromJvFactoryType
	= DerivedAndHasStaticKindStr<DerivedType, BaseType> 
	&& requires(const Json::Value& jv)
{
	DerivedType(jv);
};

template<typename BaseType>
class FromJvFactory final
{
public:		// types
	using Func
		= std::function<std::unique_ptr<BaseType>(const Json::Value&)>;
	using FuncMap = std::map<std::string, Func>;
public:		// functions
	// Create a `FuncMap` that maps each derived type's `KIND_STR` to a
	// lambda function that generates an `std::unique_ptr<BaseType>` that
	// points to a `new FirstDerivedType(jv)`.
	template<IsValidFromJvFactoryType<BaseType> FirstDerivedType,
		IsValidFromJvFactoryType<BaseType>... RemDerivedTypes>
	static FuncMap gen_func_map()
	{
		FuncMap ret;

		if constexpr (sizeof...(RemDerivedTypes) > 0)
		{
			ret = gen_func_map<RemDerivedTypes...>();
		}

		//ret[FirstDerivedType::KIND_STR] = Func(FirstDerivedType::from_jv);
		ret[FirstDerivedType::KIND_STR]
			= Func
			(
				[](const Json::Value& jv) -> std::unique_ptr<BaseType>
				{
					return std::unique_ptr<BaseType>
						(new FirstDerivedType(jv));
				}
			);

		return ret;
	}
};

} // namespace json
} // namespace liborangepower

#endif		// liborangepower_json_stuff_from_jv_factory_stuff_hpp
