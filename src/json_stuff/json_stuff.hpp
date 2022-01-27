#ifndef liborangepower_json_stuff_json_stuff_hpp
#define liborangepower_json_stuff_json_stuff_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_output_classes.hpp"
#include "../containers/vec2_classes.hpp"
#include "../containers/vec3_classes.hpp"
#include "../strings/sconcat_etc.hpp"

// jsoncpp headers
#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>

#include <cstdint>
#include <deque>

namespace liborangepower
{

using strings::sconcat;

namespace json
{

// These are for use with X macros that call a macro on at least some
// members of a class to serialize or deserialize
#define MEMB_SERIALIZE(name) \
	set_jv_memb(ret, #name, name);
#define MEMB_DESERIALIZE(name) \
	name = get_jv_memb<decltype(name)>(jv, #name);
#define MEMB_FROM_JV_DESERIALIZE(name) \
	ret.name = get_jv_memb<decltype(ret.name)>(jv, #name);

template<typename Type>
extern uint32_t _is_std_vector_func(const std::vector<Type>&);
template<typename Type>
extern uint8_t _is_std_vector_func(const Type&);

template<typename Type>
constexpr inline bool is_std_vector()
{
	return (sizeof(_is_std_vector_func(std::declval<Type>()))
		== sizeof(uint32_t));
}

template<typename Type>
extern uint32_t _is_std_deque_func(const std::deque<Type>&);
template<typename Type>
extern uint8_t _is_std_deque_func(const Type&);

template<typename Type>
constexpr inline bool is_std_deque()
{
	return (sizeof(_is_std_deque_func(std::declval<Type>()))
		== sizeof(uint32_t));
}

template<typename Type>
inline containers::Vec2<Type> vec2_from_jv(const Json::Value& jv)
{
	return
		containers::Vec2<Type>
	(
		val_from_jv<Type>(jv["x"]),
		val_from_jv<Type>(jv["y"])
	);
}
template<typename Type>
inline Json::Value vec2_to_jv(const containers::Vec2<Type>& vec)
{
	Json::Value ret;

	ret["x"] = vec.x;
	ret["y"] = vec.y;

	return ret;
}

template<typename Type>
inline containers::Vec3<Type> vec3_from_jv(const Json::Value& jv)
{
	return
		containers::Vec3<Type>
	(
		val_from_jv<Type>(jv["x"]),
		val_from_jv<Type>(jv["y"]),
		val_from_jv<Type>(jv["z"])
	);
}
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
inline Type val_from_jv(const Json::Value& jv)
{
	//--------
	using NonCvrefType = typename std::remove_cvref<Type>::type;
	//--------
	if constexpr (std::is_same<Type, int>())
	{
		return jv.asInt();
	}
	else if constexpr (std::is_same<Type, uint>())
	{
		return jv.asUInt();
	}
	else if constexpr (std::is_same<Type, float>())
	{
		return jv.asFloat();
	}
	else if constexpr (std::is_same<Type, double>())
	{
		return jv.asDouble();
	}
	else if constexpr (std::is_same<Type, bool>())
	{
		return jv.asBool();
	}
	else if constexpr (std::is_same<Type, std::string>())
	{
		return jv.asString();
	}
	//--------
	else if constexpr (containers::is_vec2<Type>())
	{
		return vec2_from_jv<decltype(NonCvrefType().x)>(jv);
	}
	else if constexpr (containers::is_vec3<Type>())
	{
		return vec3_from_jv<decltype(NonCvrefType().x)>(jv);
	}
	//--------
	else if constexpr (is_std_vector<Type>()
		|| is_std_deque<Type>())
	{
		NonCvrefType ret;

		for (Json::ArrayIndex i=0; i<jv.size(); ++i)
		{
			ret.push_back(val_from_jv<decltype(NonCvrefType().at(0))>
				(jv[i]));
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
inline Type get_jv_memb(const Json::Value& jv,
	const std::string& name)
{
	if constexpr (std::is_same<Type, int64_t>()
		|| std::is_same<Type, uint64_t>())
	{
		Type ret = 0;

		ret = (static_cast<Type>(val_from_jv<uint>
			(jv[sconcat(name, ".high")])) << static_cast<uint64_t>(32u))
			| static_cast<Type>(val_from_jv<uint>
				(jv[sconcat(name, ".low")]));

		return ret;
	}
	else
	{
		return val_from_jv<Type>(jv[name]);
	}
}

template<typename Type>
inline void _set_jv(Json::Value& jv, const Type& val)
{
	static_assert((!std::is_same<Type, int64_t>())
		&& (!std::is_same<Type, uint64_t>()));

	//--------
	if constexpr (containers::is_vec2<Type>())
	{
		jv = vec2_to_jv(val);
	}
	else if constexpr (containers::is_vec3<Type>())
	{
		jv = vec3_to_jv(val);
	}
	//--------
	else if constexpr (is_std_vector<Type>() || is_std_deque<Type>())
	{
		for (Json::ArrayIndex i=0; i<val.size(); ++i)
		{
			using NonCvrefType = typename std::remove_cvref<Type>::type;
			if constexpr (is_std_vector<decltype(NonCvrefType().at(0))>()
				|| is_std_deque<decltype(NonCvrefType().at(0))>())
			{
				Json::Value inner_jv;

				_set_jv(inner_jv, val.at(i));

				jv[i] = inner_jv;
			}
			else
			{
				jv[i] = val.at(i);
			}
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
	if constexpr (std::is_same<Type, int64_t>()
		|| std::is_same<Type, uint64_t>())
	{
		jv[sconcat(name, ".high")] 
			= static_cast<uint32_t>(static_cast<uint64_t>(val)
				>> static_cast<uint64_t>(32u));
		jv[sconcat(name, ".low")]
			= static_cast<uint32_t>(static_cast<uint64_t>(val)
				& static_cast<uint64_t>(0xffffffffu));
	}
	else
	{
		_set_jv(jv[name], val);
	}
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

} // namespace json
} // namespace liborangepower

#endif		// liborangepower_json_stuff_json_stuff_hpp
