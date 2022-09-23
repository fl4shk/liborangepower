#ifndef liborangepower_binser_from_bv_factory_stuff_hpp
#define liborangepower_binser_from_bv_factory_stuff_hpp

#include "../misc/misc_includes.hpp"
#include "../concepts/misc_concepts.hpp"

#include "binser_concepts.hpp"
#include "value_class.hpp"

namespace liborangepower
{
namespace binser
{

template<typename BaseT>
using FromBvFactoryFunc
	= std::function<std::unique_ptr<BaseT>(const Value&)>;

template<typename BaseT>
using FromBvFactoryFuncMap
	= std::unordered_map<std::string, FromBvFactoryFunc<BaseT>>;

template<typename BaseT>
class FromBvFactory final
{
public:		// types
	using Func = FromBvFactoryFunc<BaseT>;
	using FuncMap = FromBvFactoryFuncMap<BaseT>;
public:		// functions
	// Create a `FuncMap` that maps each derived type's `KIND_STR` to a
	// lambda function that generates an `std::unique_ptr<BaseT>` that
	// points to a `new FirstDerivedT(bv)`.
	template<IsValidFromBvFactoryT<BaseT> FirstDerivedT,
		IsValidFromBvFactoryT<BaseT>... RemDerivedTs>
	static FuncMap gen_func_map()
	{
		FuncMap ret;

		if constexpr (sizeof...(RemDerivedTs) > 0)
		{
			ret = gen_func_map<RemDerivedTs...>();
		}

		//ret[FirstDerivedT::KIND_STR] = Func(FirstDerivedT::from_bv);
		ret[FirstDerivedT::KIND_STR] 
			= Func
		([](const Value& bv) -> std::unique_ptr<BaseT>
		{
			if constexpr (std::is_constructible
				<FirstDerivedT, Value>())
			{
				return std::unique_ptr<BaseT>
					(new FirstDerivedT(bv));
			}
			else
			{
				return std::unique_ptr<BaseT>
					(new FirstDerivedT
						(FirstDerivedT::from_bv(bv)));
			}
		});

		return ret;
	}
};

} // namespace binser
} // namespace liborangepower

#endif		// liborangepower_binser_from_bv_factory_stuff_hpp
