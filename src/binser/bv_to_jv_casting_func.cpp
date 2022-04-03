#include "bv_to_jv_casting_func.hpp"
#include "../json_stuff/json_stuff.hpp"

namespace liborangepower
{
namespace binser
{

Json::Value bv_to_jv(const binser::Value& bv)
{
	Json::Value ret;

	if (bv.holds_alternative<std::monostate>())
	{
		ret = std::string("null");
	}
	else if (bv.holds_alternative<u8>())
	{
		ret = static_cast<uint>(bv.get<u8>());
	}
	else if (bv.holds_alternative<i8>())
	{
		ret = static_cast<int>(bv.get<i8>());
	}
	else if (bv.holds_alternative<u16>())
	{
		ret = static_cast<uint>(bv.get<u16>());
	}
	else if (bv.holds_alternative<i16>())
	{
		ret = static_cast<int>(bv.get<i16>());
	}
	else if (bv.holds_alternative<u32>())
	{
		ret = bv.get<u32>();
	}
	else if (bv.holds_alternative<i32>())
	{
		ret = bv.get<i32>();
	}
	else if (bv.holds_alternative<u64>())
	{
		ret = bv.get<u64>();
	}
	else if (bv.holds_alternative<i64>())
	{
		ret = bv.get<i64>();
	}
	else if (bv.holds_alternative<float>())
	{
		ret = static_cast<double>(bv.get<float>());
	}
	else if (bv.holds_alternative<double>())
	{
		ret = bv.get<double>();
	}
	else if (bv.holds_alternative<bool>())
	{
		ret = bv.get<bool>();
	}
	else if (bv.holds_alternative<std::string>())
	{
		ret = bv.as_str();
	}
	else if (bv.holds_alternative<ValueVec>())
	{
		const auto& vec = bv.as_vec();

		for (Json::ArrayIndex i=0; i<vec.size(); ++i)
		{
			ret[i] = bv_to_jv(*vec.at(i));
		}
	}
	else // if (bv.holds_alternative<ValueMap>())
	{
		const auto& map = bv.as_map();

		for (const auto& item: map)
		{
			ret[item.first] = bv_to_jv(*item.second);
		}
	}

	return ret;
}
//Value jv_to_bv(const Json::Value& jv)
//{
//	Value ret;
//
//	return ret;
//}

} // namespace binser
} // namespace liborangepower
