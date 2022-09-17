#ifndef liborangepower_json_stuff_json_stuff_hpp
#define liborangepower_json_stuff_json_stuff_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_output_classes.hpp"
#include "../math/vec2_classes.hpp"
#include "../math/vec3_classes.hpp"
#include "../containers/prev_curr_pair_classes.hpp"
#include "../containers/std_container_id_funcs.hpp"
#include "../strings/sconcat_etc.hpp"
#include "../metaprog_defines.hpp"

#include "../concepts/is_specialization_concepts.hpp"
#include "../concepts/misc_concepts.hpp"

#include "from_jv_factory_stuff.hpp"

// jsoncpp headers
#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>

namespace liborangepower
{

using strings::sconcat;

using concepts::is_specialization;

using math::is_vec2;
using math::is_vec3;

using containers::is_prev_curr_pair;
using containers::is_move_only_prev_curr_pair;

using containers::is_non_arr_std_unique_ptr;
using containers::is_non_arr_std_shared_ptr;
using containers::is_non_arr_std_weak_ptr;
using containers::is_std_array;
using containers::is_std_vector;
using containers::is_std_deque;
using containers::is_vec_like_std_container;
using containers::is_arr_like_std_container;

using containers::is_std_set;
using containers::is_std_unordered_set;
using containers::is_set_like_std_container;

using containers::is_std_map;
using containers::is_std_unordered_map;

using containers::is_map_like_std_container;
using containers::MapLikeStdContnr;

using containers::is_pseudo_vec_like_std_container;
using containers::is_basic_indexable_std_container;

namespace json
{

// These are for use with X macros that call a macro on at least some
// members of a class to serialize or deserialize
#define JSON_MEMB_SERIALIZE(name, unused_arg) \
	set_jv_memb(ret, #name, name);
#define JSON_MEMB_DESERIALIZE(name, func_map) \
	get_jv_memb(name, jv, #name, func_map);
#define JSON_MEMB_FROM_JV_DESERIALIZE(name, func_map) \
	get_jv_memb(ret.name, jv, #name, func_map);

class BlankValue;

//template<typename T>
//inline math::Vec2<T> vec2_from_jv(const Json::Value& jv)
//{
//	return
//		math::Vec2<T>
//	(
//		val_from_jv<T>(jv["x"]),
//		val_from_jv<T>(jv["y"])
//	);
//}
template<typename T>
inline Json::Value vec2_to_jv(const math::Vec2<T>& vec)
{
	Json::Value ret;

	ret["x"] = vec.x;
	ret["y"] = vec.y;

	return ret;
}
//
//template<typename T>
//inline math::Vec3<T> vec3_from_jv(const Json::Value& jv)
//{
//	return
//		math::Vec3<T>
//	(
//		val_from_jv<T>(jv["x"]),
//		val_from_jv<T>(jv["y"]),
//		val_from_jv<T>(jv["z"])
//	);
//}
template<typename T>
inline Json::Value vec3_to_jv(const math::Vec3<T>& vec)
{
	Json::Value ret;

	ret["x"] = vec.x;
	ret["y"] = vec.y;
	ret["z"] = vec.z;

	return ret;
}

template<typename T, typename BaseT>
inline void val_from_jv(T& ret, const Json::Value& jv,
	FromJvFactoryFuncMap<BaseT>* func_map)
{
	//--------
	using NonCvrefT = std::remove_cvref_t<T>;
	//--------
	if constexpr (std::is_same<NonCvrefT, int>())
	{
		ret = jv.asInt();
	}
	else if constexpr (std::is_same<NonCvrefT, uint>())
	{
		ret = jv.asUInt();
	}
	else if constexpr (std::is_same<NonCvrefT, int64_t>())
	{
		ret = jv.asInt64();
	}
	else if constexpr (std::is_same<NonCvrefT, uint64_t>())
	{
		ret = jv.asUInt64();
	}
	else if constexpr (std::is_same<NonCvrefT, float>())
	{
		ret = jv.asFloat();
	}
	else if constexpr (std::is_same<NonCvrefT, double>())
	{
		ret = jv.asDouble();
	}
	else if constexpr (std::is_same<NonCvrefT, bool>())
	{
		ret = jv.asBool();
	}
	else if constexpr (is_specialization<NonCvrefT, std::basic_string>())
	{
		ret = jv.asString();
	}
	//--------
	else if constexpr (is_vec2<NonCvrefT>())
	{
		val_from_jv(ret.x, jv["x"], func_map);
		val_from_jv(ret.y, jv["y"], func_map);
	}
	else if constexpr (is_vec3<NonCvrefT>())
	{
		val_from_jv(ret.x, jv["x"], func_map);
		val_from_jv(ret.y, jv["y"], func_map);
		val_from_jv(ret.z, jv["z"], func_map);
	}
	else if constexpr
	(
		is_prev_curr_pair<NonCvrefT>()
		|| is_move_only_prev_curr_pair<NonCvrefT>()
	)
	{
		val_from_jv(ret(), jv["_prev"], func_map);
		ret.back_up();
		val_from_jv(ret(), jv["_curr"], func_map);
	}
	//--------
	else if constexpr (is_non_arr_std_unique_ptr<NonCvrefT>()
		|| is_non_arr_std_shared_ptr<NonCvrefT>()
		|| is_non_arr_std_weak_ptr<NonCvrefT>())
	{
		using ElemT = typename NonCvrefT::element_type;

		////return NonCvrefT(new ElemT(val_from_jv<ElemT>
		////	(jv["obj"])));
		//auto find_func
		//	= [&]<typename FirstFuncMapType, typename... RemFuncMapTypes>
		//	(const FirstFuncMapType& first_func_map,
		//	const RemFuncMapTypes&... rem_func_maps) -> void
		//{
		//	if constexpr (std::is_same<ElemT, >())
		//	if constexpr (sizeof...(rem_func_maps) > 0)
		//	{
		//	}
		//};

		const Json::Value& obj = jv["obj"];
		//bool has_kind_str;
		//val_from_jv(has_kind_str, jv["has_kind_str"], func_map);

		//if (!jv.isMember("kind_str"))
		if constexpr (!std::is_same<ElemT, BaseT>())
		{
			//return NonCvrefT(new ElemT(val_from_jv<ElemT>(obj)));
			ElemT temp;
			val_from_jv(temp, obj, func_map);
			ret.reset(new ElemT(temp));
		}
		//else // if (jv.isMember("kind_str"))
		else // if (std::is_same<ElemT, BaseT>())
		{
			if (!func_map)
			{
				throw std::invalid_argument(sconcat("val_from_jv(): ",
					"Need a non-null `func_map` in this case"));
			}
			std::string kind_str;
			val_from_jv(kind_str, jv["kind_str"], func_map);

			//ret.reset(func_map->at(kind_str)(obj));
			ret = func_map->at(kind_str)(obj);
		}
	}
	else if constexpr (is_pseudo_vec_like_std_container<NonCvrefT>())
	{
		ret = NonCvrefT();

		for (Json::ArrayIndex i=1; i<jv.size(); ++i)
		{
			if constexpr (is_std_array<T>())
			{
				val_from_jv(ret[i], jv[i], func_map);
			}
			else if constexpr (is_vec_like_std_container<T>())
			{
				using ValueT = typename NonCvrefT::value_type;
				ValueT temp;

				val_from_jv(temp, jv[i], func_map);

				if constexpr (is_non_arr_std_unique_ptr<ValueT>())
				{
					ret.push_back(std::move(temp));
				}
				else
				{
					ret.push_back(temp);
				}
			}
			else // if constexpr (is_set_like_std_container<T>())
			{
				using KeyT = typename NonCvrefT::key_type;
				KeyT temp;

				val_from_jv(temp, jv[i], func_map);

				if constexpr (is_non_arr_std_unique_ptr<KeyT>())
				{
					ret.insert(std::move(temp));
				}
				else
				{
					ret.insert(temp);
				}
			}
		}
	}
	else if constexpr (is_map_like_std_container<NonCvrefT>())
	{
		ret = NonCvrefT();
		using KeyT = typename NonCvrefT::key_type;
		using MappedT = typename NonCvrefT::mapped_type;

		for (Json::ArrayIndex i=1; i<jv.size(); ++i)
		{
			//ret[i]["key"] = val_from_jv
			KeyT key;
			val_from_jv(key, jv[i]["key"], func_map);

			MappedT value;
			val_from_jv(value, jv[i]["value"], func_map);

			if constexpr (is_non_arr_std_unique_ptr<MappedT>())
			{
				ret[key] = std::move(value);
			}
			else
			{
				ret[key] = value;
			}
		}
	}
	//--------
	else if constexpr (HasJvDeserializeFunc<NonCvrefT>)
	{
		ret.deserialize(jv);
	}
	else if constexpr (std::is_constructible<NonCvrefT, Json::Value>())
	{
		ret = T(jv);
	}
	else
	{
		// Assume a static member function called `from_jv` exists
		ret = T::from_jv(jv);
	}
	//--------
}
template<typename T>
inline void val_from_jv(T& ret, const Json::Value& jv,
	const std::nullopt_t& some_nullopt)
{
	val_from_jv<T, void>(ret, jv, nullptr);
}

template<typename T, typename BaseT>
inline void get_jv_memb(T& ret, const Json::Value& jv,
	const std::string& name, FromJvFactoryFuncMap<BaseT>* func_map)
{
	val_from_jv(ret, jv[name], func_map);
}
template<typename T>
inline void get_jv_memb(T& ret, const Json::Value& jv,
	const std::string& name, const std::nullopt_t& some_nullopt)
{
	//FromJvFactoryFuncMap<void> func_map;
	//get_jv_memb(ret, jv, name, func_map);
	//val_from_jv(ret, jv[name], std::nullopt);
	val_from_jv<T, void>(ret, jv[name], nullptr);
}

template<typename TempT, typename RetT, typename BaseT>
inline void get_jv_memb_w_stat_cast(RetT& ret, const Json::Value& jv,
	const std::string& name, FromJvFactoryFuncMap<BaseT>* func_map)
{
	TempT temp;
	get_jv_memb(temp, jv, name, func_map);
	ret = static_cast<RetT>(temp);
}
template<typename TempT, typename RetT>
inline void get_jv_memb_w_stat_cast(RetT& ret, const Json::Value& jv,
	const std::string& name, const std::nullopt_t& some_nullopt)
{
	TempT temp;
	get_jv_memb(temp, jv, name, some_nullopt);
	ret = static_cast<RetT>(temp);
}

template<typename T>
inline void set_jv(Json::Value& jv, const T& val);

template<MapLikeStdContnr T>
inline void set_jv_map_like_std_container(Json::Value& jv, const T& val,
	const std::function<bool(const typename T::value_type&)>& skip_func)
{
	//--------
	jv = Json::Value();
	//--------
	Json::ArrayIndex i = 0;

	jv[i++] = BlankValue();

	for (const auto& pair: val)
	{
		if (!skip_func(pair))
		{
			Json::Value inner_jv;

			set_jv(inner_jv["key"], pair.first);
			set_jv(inner_jv["value"], pair.second);

			jv[i++] = inner_jv;
		}
	}
	//--------
}

template<MapLikeStdContnr T>
inline void set_jv_map_like_std_container(Json::Value& jv, const T& val)
{
	set_jv_map_like_std_container(jv, val,
		[](const typename T::value_type& pair) -> bool
			{ return false; });
}

//template<containers::MapLikeStdContnr T>
//inline void set_jv_map_like_std_container(Json::Value& jv, const T& val,
//	const std::nullopt_t& some_nullopt)
//{
//	set_jv_map_like_std_container(jv, val, nullptr);
//}

template<typename T>
inline void set_jv(Json::Value& jv, const T& val)
{
	using NonCvrefT = std::remove_cvref_t<T>;

	jv = Json::Value();

	//static_assert(!std::is_same<T, int64_t>()
	//	&& !std::is_same<T, uint64_t>());

	//--------
	if constexpr (is_vec2<NonCvrefT>())
	{
		jv = vec2_to_jv(val);
	}
	else if constexpr (is_vec3<NonCvrefT>())
	{
		jv = vec3_to_jv(val);
	}
	else if constexpr
	(
		is_prev_curr_pair<NonCvrefT>()
		|| is_move_only_prev_curr_pair<NonCvrefT>()
	)
	{
		set_jv(jv["_prev"], val.prev());
		set_jv(jv["_curr"], val.curr());
	}
	//--------
	else if constexpr (is_non_arr_std_unique_ptr<NonCvrefT>()
		|| is_non_arr_std_shared_ptr<NonCvrefT>()
		|| is_non_arr_std_weak_ptr<NonCvrefT>())
	{
		//jv["obj"] = *val;
		set_jv(jv["obj"], *val);
		using ElemT = typename NonCvrefT::element_type;
		//if constexpr (concepts::HasStaticKindStr<T>)
		//{
		//	jv["has_kind_str"] = true;
		//	jv["kind_str"] = T::KIND_STR;
		//}
		//else
		if constexpr (concepts::HasFuncKindStr<ElemT>)
		{
			//jv["has_kind_str"] = true;
			jv["kind_str"] = val->kind_str();
		}
		//else
		//{
		//	jv["has_kind_str"] = false;
		//}
	}
	else if constexpr (is_arr_like_std_container<NonCvrefT>())
	{
		jv[0] = BlankValue();

		for (Json::ArrayIndex i=0; i<val.size(); ++i)
		{
			if constexpr (is_basic_indexable_std_container
				<typename NonCvrefT::value_type>())
			{
				Json::Value inner_jv;

				set_jv(inner_jv, val.at(i));

				jv[i + 1] = inner_jv;
			}
			else
			{
				jv[i + 1] = val.at(i);
			}
		}
	}
	else if constexpr (is_set_like_std_container<NonCvrefT>())
	{
		Json::ArrayIndex i = 0;

		jv[i++] = BlankValue();

		for (const auto& key: val)
		{
			if constexpr (is_basic_indexable_std_container
				<typename NonCvrefT::key_type>())
			{
				Json::Value inner_jv;

				set_jv(inner_jv, key);

				jv[i++] = inner_jv;
			}
			else
			{
				jv[i++] = key;
			}
		}
	}
	else if constexpr (is_map_like_std_container<NonCvrefT>())
	{
		set_jv_map_like_std_container(jv, val);
	}
	//--------
	else
	{
		jv = val;
	}
	//--------
}

template<typename T>
inline void set_jv_memb(Json::Value& jv, const std::string& name,
	const T& val)
{
	//--------
	//if constexpr (std::is_same<T, int>()
	//	|| std::is_same<T, uint>()
	//	|| std::is_same<T, float>()
	//	|| std::is_same<T, double>())
	//if constexpr (std::is_same<T, int64_t>()
	//	|| std::is_same<T, uint64_t>())
	//{
	//	jv[sconcat(name, ".high")] 
	//		= static_cast<uint32_t>(static_cast<uint64_t>(val)
	//			>> static_cast<uint64_t>(32u));
	//	jv[sconcat(name, ".low")]
	//		= static_cast<uint32_t>(static_cast<uint64_t>(val)
	//			& static_cast<uint64_t>(0xffffffffu));
	//}
	//else
	//{
	//	set_jv(jv[name], val);
	//}
	set_jv(jv[name], val);
}

std::string get_json_value_type_as_str(const Json::Value& some_value);
inline std::string get_json_value_type_as_str(Json::Value* iter)
{
	return get_json_value_type_as_str(*iter);
}

inline void print_json_value_type(const Json::Value& some_value,
	std::ostream& os=std::cout)
{
	misc_output::osprintout(os, 
		get_json_value_type_as_str(some_value));
}
inline void print_json_value_type(Json::Value* iter, 
	std::ostream& os=std::cout)
{
	misc_output::osprintout(os, 
		get_json_value_type_as_str(iter));
}

// Errors from the `parse_json()` family of functions only happened if the
// return value is false.
bool parse_json(Json::CharReaderBuilder* rbuilder, std::istream& is,
	Json::Value* root, std::string* errs);
bool parse_json(Json::CharReaderBuilder* rbuilder, 
	const std::string& input_file_name, Json::Value* root, 
	std::string* errs);

inline bool parse_json(std::istream& is, Json::Value* root, 
	std::string* errs)
{
	return parse_json(nullptr, is, root, errs);
}
inline bool parse_json(const std::string& input_file_name, 
	Json::Value* root, std::string* errs)
{
	return parse_json(nullptr, input_file_name, root, errs);
}


void write_json(Json::StreamWriterBuilder* wbuilder,
	std::ostream& os, Json::Value* root);
void write_json(Json::StreamWriterBuilder* wbuilder,
	const std::string& output_file_name, Json::Value* root);

inline void write_json(std::ostream& os, Json::Value* root)
{
	write_json(nullptr, os, root);
}
inline void write_json(const std::string& output_file_name, 
	Json::Value* root)
{
	write_json(nullptr, output_file_name, root);
}



// A recursive function for printing out the contents of a JSON file.
// Note that it does NOT print out valid JSON, just something similar.
// The main difference from real JSON is that every value ends with a
// comma, even when at the end of an objectValue or arrayValue.
void debug_print_json(const Json::Value& some_value, 
	std::ostream& os=std::cout, size_t tabs_level=0);
inline void debug_print_json(Json::Value* iter, 
	std::ostream& os=std::cout, size_t tabs_level=0)
{
	debug_print_json(*iter, os, tabs_level);
}

class BlankValue final
{
public:		// functions
	constexpr inline BlankValue() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(BlankValue);
	constexpr inline BlankValue(const Json::Value& jv)
	{
	}

	inline operator Json::Value () const
	{
		Json::Value ret;

		set_jv_memb(ret, "<is_blank_value>", true);

		return ret;
	}
};

} // namespace json
} // namespace liborangepower

#endif		// liborangepower_json_stuff_json_stuff_hpp
