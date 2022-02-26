#ifndef liborangepower_json_stuff_json_stuff_hpp
#define liborangepower_json_stuff_json_stuff_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_output_classes.hpp"
#include "../containers/vec2_classes.hpp"
#include "../containers/vec3_classes.hpp"
#include "../containers/prev_curr_pair_classes.hpp"
#include "../containers/std_container_id_funcs.hpp"
#include "../strings/sconcat_etc.hpp"
#include "../metaprog_defines.hpp"

#include "../concepts/is_specialization_concepts.hpp"
#include "../concepts/misc_concepts.hpp"

// jsoncpp headers
#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>

namespace liborangepower
{

using strings::sconcat;

using concepts::is_specialization;

using containers::is_vec2;
using containers::is_vec3;

using containers::is_prev_curr_pair;
using containers::is_move_only_prev_curr_pair;

using containers::is_non_arr_std_unique_ptr;
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

using containers::is_pseudo_vec_like_std_container;
using containers::is_basic_indexable_std_container;

namespace json
{

// These are for use with X macros that call a macro on at least some
// members of a class to serialize or deserialize
#define JSON_MEMB_SERIALIZE(name) \
	set_jv_memb(ret, #name, name);
#define JSON_MEMB_DESERIALIZE(name) \
	get_jv_memb(name, jv, #name); \
#define JSON_MEMB_FROM_JV_DESERIALIZE(name) \
	get_jv_memb(ret.name, jv, #name);

class BlankValue;

//template<typename T>
//inline containers::Vec2<T> vec2_from_jv(const Json::Value& jv)
//{
//	return
//		containers::Vec2<T>
//	(
//		val_from_jv<T>(jv["x"]),
//		val_from_jv<T>(jv["y"])
//	);
//}
template<typename T>
inline Json::Value vec2_to_jv(const containers::Vec2<T>& vec)
{
	Json::Value ret;

	ret["x"] = vec.x;
	ret["y"] = vec.y;

	return ret;
}
//
//template<typename T>
//inline containers::Vec3<T> vec3_from_jv(const Json::Value& jv)
//{
//	return
//		containers::Vec3<T>
//	(
//		val_from_jv<T>(jv["x"]),
//		val_from_jv<T>(jv["y"]),
//		val_from_jv<T>(jv["z"])
//	);
//}
template<typename T>
inline Json::Value vec3_to_jv(const containers::Vec3<T>& vec)
{
	Json::Value ret;

	ret["x"] = vec.x;
	ret["y"] = vec.y;
	ret["z"] = vec.z;

	return ret;
}

concept HasJvDeserializeFunc = requires(auto obj, const Json::Value& jv)
{
	{ obj.deserialize(jv) } -> std::same_as<void>;
};

template<typename T>
inline void val_from_jv(T& ret, const Json::Value& jv)
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
		return jv.asBool();
	}
	else if constexpr 
		(is_specialization<NonCvrefT, std::basic_string>())
	{
		ret = jv.asString();
	}
	//--------
	else if constexpr (is_vec2<T>())
	{
		val_from_jv(ret.x, jv["x"]);
		val_from_jv(ret.y, jv["y"]);
	}
	else if constexpr (is_vec3<T>())
	{
			val_from_jv(ret.x, jv["x"]);
			val_from_jv(ret.y, jv["y"]);
			val_from_jv(ret.z, jv["z"]);
	}
	else if constexpr
	(
		is_prev_curr_pair<T>()
		|| is_move_only_prev_curr_pair<T>()
	)
	{
		val_from_jv(ret(), jv["_prev"]);
		ret.back_up();
		val_from_jv(ret(), jv["_curr"]);
	}
	//--------
	//else if constexpr (is_non_arr_std_unique_ptr<T>())
	//{
	//	using ElemT = typename NonCvrefT::element_type;

	//	return NonCvrefT(new ElemT(val_from_jv<ElemT>
	//		(jv["obj"])));
	//}
	else if constexpr (is_pseudo_vec_like_std_container<T>())
	{
		ret = NonCvrefT();

		for (Json::ArrayIndex i=1; i<jv.size(); ++i)
		{
			if constexpr (is_std_array<T>())
			{
				val_from_jv(ret[i], jv[i]);
			}
			else if constexpr (is_vec_like_std_container<T>())
			{
				typename NonCvrefT::value_type temp;

				val_from_jv(temp, jv[i]);

				ret.push_back(temp);
			}
			else // if constexpr (is_set_like_std_container<T>())
			{
				typename NonCvrefT::key_type temp;

				val_from_jv(temp, jv[i]);

				ret.insert(temp);
			}
		}
	}
	else if constexpr (is_map_like_std_container<T>())
	{
		ret = NonCvrefT();

		for (Json::ArrayIndex i=1; i<jv.size(); ++i)
		{
			//ret[i]["key"] = val_from_jv
			typename NonCvrefT::key_type key;
			val_from_jv(key, jv[i]["key"])

			typename NonCvrefT::value_type value;
			val_from_jv(value, jv[i]["value"]);

			ret[key] = value;
		}
	}
	//--------
	else if constexpr (HasJvDeserializeFunc<T>)
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

inline void get_jv_memb(auto& ret, const Json::Value& jv,
	const std::string& name)
{
	val_from_jv<decltype(ret)>(ret, jv[name]);
}
template<typename TempT, typename RetT>
inline void get_jv_memb_w_stat_cast(RetT& ret, const Json::Value& jv,
	const std::string& name)
{
	TempT temp;
	get_jv_memb(temp, jv, name);
	ret = static_cast<RetT>(temp);
}

template<typename T>
inline void _set_jv(Json::Value& jv, const T& val)
{
	using NonCvrefT = std::remove_cvref_t<T>;

	jv = Json::Value();

	//static_assert((!std::is_same<T, int64_t>())
	//	&& (!std::is_same<T, uint64_t>()));

	//--------
	if constexpr (is_vec2<T>())
	{
		jv = vec2_to_jv(val);
	}
	else if constexpr (is_vec3<T>())
	{
		jv = vec3_to_jv(val);
	}
	else if constexpr
	(
		is_prev_curr_pair<T>()
		|| is_move_only_prev_curr_pair<T>()
	)
	{
		_set_jv(jv["_prev"], val.prev());
		_set_jv(jv["_curr"], val.curr());
	}
	//--------
	else if constexpr (is_arr_like_std_container<T>())
	{
		jv[0] = BlankValue();

		for (Json::ArrayIndex i=0; i<val.size(); ++i)
		{
			if constexpr (is_basic_indexable_std_container
				<typename NonCvrefT::value_type>())
			{
				Json::Value inner_jv;

				_set_jv(inner_jv, val.at(i));

				jv[i + 1] = inner_jv;
			}
			else
			{
				jv[i + 1] = val.at(i);
			}
		}
	}
	else if constexpr (is_set_like_std_container<T>())
	{
		Json::ArrayIndex i = 0;

		jv[i++] = BlankValue();

		for (const auto& key: val)
		{
			if constexpr (is_basic_indexable_std_container
				<typename NonCvrefT::key_type>())
			{
				Json::Value inner_jv;

				_set_jv(inner_jv, key);

				jv[i++] = inner_jv;
			}
			else
			{
				jv[i++] = key;
			}
		}
	}
	else if constexpr (is_map_like_std_container<T>())
	{
		Json::ArrayIndex i = 0;

		jv[i++] = BlankValue();

		for (const auto& pair: val)
		{
			Json::Value inner_jv;

			_set_jv(inner_jv["key"], pair.first);
			_set_jv(inner_jv["value"], pair.second);

			jv[i++] = inner_jv;
		}
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
	//	_set_jv(jv[name], val);
	//}
	_set_jv(jv[name], val);
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
