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
#define MEMB_SERIALIZE(name, unused_arg) \
	set_jv_memb(ret, #name, name);
#define MEMB_DESERIALIZE(name, use_func_cond) \
	IF(use_func_cond) \
	( \
		name.deserialize(jv[#name]);, \
		name = get_jv_memb<decltype(name)>(jv, #name); \
	)
#define MEMB_FROM_JV_DESERIALIZE(name, unused_arg) \
	ret.name = get_jv_memb<decltype(ret.name)>(jv, #name);

class BlankValue;

//template<typename Type>
//inline containers::Vec2<Type> vec2_from_jv(const Json::Value& jv)
//{
//	return
//		containers::Vec2<Type>
//	(
//		val_from_jv<Type>(jv["x"]),
//		val_from_jv<Type>(jv["y"])
//	);
//}
template<typename Type>
inline Json::Value vec2_to_jv(const containers::Vec2<Type>& vec)
{
	Json::Value ret;

	ret["x"] = vec.x;
	ret["y"] = vec.y;

	return ret;
}
//
//template<typename Type>
//inline containers::Vec3<Type> vec3_from_jv(const Json::Value& jv)
//{
//	return
//		containers::Vec3<Type>
//	(
//		val_from_jv<Type>(jv["x"]),
//		val_from_jv<Type>(jv["y"]),
//		val_from_jv<Type>(jv["z"])
//	);
//}
template<typename Type>
inline Json::Value vec3_to_jv(const containers::Vec3<Type>& vec)
{
	Json::Value ret;

	ret["x"] = vec.x;
	ret["y"] = vec.y;
	ret["z"] = vec.z;

	return ret;
}

template<typename Type>
inline std::remove_cvref_t<Type> val_from_jv(const Json::Value& jv)
{
	//--------
	using NonCvrefType = std::remove_cvref_t<Type>;
	//--------
	if constexpr (std::is_same<NonCvrefType, int>())
	{
		return jv.asInt();
	}
	else if constexpr (std::is_same<NonCvrefType, uint>())
	{
		return jv.asUInt();
	}
	else if constexpr (std::is_same<NonCvrefType, int64_t>())
	{
		return jv.asInt64();
	}
	else if constexpr (std::is_same<NonCvrefType, uint64_t>())
	{
		return jv.asUInt64();
	}
	else if constexpr (std::is_same<NonCvrefType, float>())
	{
		return jv.asFloat();
	}
	else if constexpr (std::is_same<NonCvrefType, double>())
	{
		return jv.asDouble();
	}
	else if constexpr (std::is_same<NonCvrefType, bool>())
	{
		return jv.asBool();
	}
	else if constexpr 
		(is_specialization<NonCvrefType, std::basic_string>())
	{
		return jv.asString();
	}
	//--------
	else if constexpr (is_vec2<Type>())
	{
		//return vec2_from_jv<decltype(std::declval<NonCvrefType>().x)>(jv);
		return NonCvrefType
		(
			val_from_jv<decltype(std::declval<NonCvrefType>().x)>(jv["x"]),
			val_from_jv<decltype(std::declval<NonCvrefType>().y)>(jv["y"])
		);
	}
	else if constexpr (is_vec3<Type>())
	{
		//return vec3_from_jv<decltype(std::declval<NonCvrefType>().x)>(jv);
		return NonCvrefType
		(
			val_from_jv<decltype(std::declval<NonCvrefType>().x)>(jv["x"]),
			val_from_jv<decltype(std::declval<NonCvrefType>().y)>(jv["y"]),
			val_from_jv<decltype(std::declval<NonCvrefType>().z)>(jv["z"])
		);
	}
	else if constexpr
	(
		is_prev_curr_pair<Type>()
		|| is_move_only_prev_curr_pair<Type>()
	)
	{
		NonCvrefType ret;

		using ElemOfNonCvrefType
			= std::remove_cvref_t<decltype(std::declval<NonCvrefType>()())>;

		ret() = val_from_jv<ElemOfNonCvrefType>(jv["_prev"]);
		ret.back_up_and_update(val_from_jv<ElemOfNonCvrefType>
			(jv["_curr"]));

		return ret;
	}
	//--------
	//else if constexpr (is_non_arr_std_unique_ptr<Type>())
	//{
	//	using ElemType = typename NonCvrefType::element_type;

	//	return NonCvrefType(new ElemType(val_from_jv<ElemType>
	//		(jv["obj"])));
	//}
	else if constexpr (is_pseudo_vec_like_std_container<Type>())
	{
		NonCvrefType ret;

		for (Json::ArrayIndex i=1; i<jv.size(); ++i)
		{
			if constexpr (is_std_array<Type>())
			{
				ret[i] = val_from_jv
					<decltype(std::declval<NonCvrefType>().at(0))>
					(jv[i]);
			}
			else if constexpr (is_vec_like_std_container<Type>())
			{
				ret.push_back(val_from_jv
					<decltype(std::declval<NonCvrefType>().at(0))>
					(jv[i]));
			}
			else // if constexpr (is_set_like_std_container<Type>())
			{
				ret.insert(val_from_jv<typename NonCvrefType::key_type>
					(jv[i]));
			}
		}

		return ret;
	}
	else if constexpr (is_map_like_std_container<Type>())
	{
		NonCvrefType ret;

		for (Json::ArrayIndex i=1; i<jv.size(); ++i)
		{
			//ret[i]["key"] = val_from_jv
			ret[val_from_jv<typename NonCvrefType::key_type>(jv[i]["key"])]
				= val_from_jv<typename NonCvrefType::value_type>
					(jv[i]["value"]);
		}

		return ret;
	}
	//--------
	else if constexpr (std::is_constructible<NonCvrefType, Json::Value>())
	{
		return Type(jv);
	}
	else
	{
		// Assume a static member function called `from_jv` exists
		return Type::from_jv(jv);
	}
	//--------
}

template<typename Type>
inline Type get_jv_memb(const Json::Value& jv, const std::string& name)
{
	//if constexpr (std::is_same<std::remove_cvref_t<Type>, int64_t>()
	//	|| std::is_same<std::remove_cvref_t<Type>, uint64_t>()
	//	|| std::is_same<std::remove_cvref_t<Type>, long int>()
	//	|| std::is_same<std::remove_cvref_t<Type>, long unsigned int>())
	//{
	//	Type ret = 0;

	//	ret = (static_cast<Type>(val_from_jv<uint>
	//		(jv[sconcat(name, ".high")])) << static_cast<uint64_t>(32u))
	//		| static_cast<Type>(val_from_jv<uint>
	//			(jv[sconcat(name, ".low")]));

	//	return ret;
	//}
	//else
	//{
	//	return val_from_jv<Type>(jv[name]);
	//}
	return val_from_jv<Type>(jv[name]);
}

template<typename Type>
inline void _set_jv(Json::Value& jv, const Type& val)
{
	using NonCvrefType = std::remove_cvref_t<Type>;

	jv = Json::Value();

	//static_assert((!std::is_same<Type, int64_t>())
	//	&& (!std::is_same<Type, uint64_t>()));

	//--------
	if constexpr (is_vec2<Type>())
	{
		jv = vec2_to_jv(val);
	}
	else if constexpr (is_vec3<Type>())
	{
		jv = vec3_to_jv(val);
	}
	else if constexpr
	(
		is_prev_curr_pair<Type>()
		|| is_move_only_prev_curr_pair<Type>()
	)
	{
		_set_jv(jv["_prev"], val.prev());
		_set_jv(jv["_curr"], val.curr());
	}
	//--------
	else if constexpr (is_arr_like_std_container<Type>())
	{
		jv[0] = BlankValue();

		for (Json::ArrayIndex i=0; i<val.size(); ++i)
		{
			if constexpr (is_basic_indexable_std_container
				<decltype(std::declval<NonCvrefType>().at(0))>())
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
	else if constexpr (is_set_like_std_container<Type>())
	{
		Json::ArrayIndex i = 0;

		jv[i++] = BlankValue();

		for (const auto& key: val)
		{
			if constexpr (is_basic_indexable_std_container
				<typename NonCvrefType::key_type>())
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
	else if constexpr (is_map_like_std_container<Type>())
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

template<typename Type>
inline void set_jv_memb(Json::Value& jv, const std::string& name,
	const Type& val)
{
	//--------
	//if constexpr (std::is_same<Type, int>()
	//	|| std::is_same<Type, uint>()
	//	|| std::is_same<Type, float>()
	//	|| std::is_same<Type, double>())
	//if constexpr (std::is_same<Type, int64_t>()
	//	|| std::is_same<Type, uint64_t>())
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
