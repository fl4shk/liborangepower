#ifndef liborangepower_binser_value_class_hpp
#define liborangepower_binser_value_class_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_output_classes.hpp"
#include "../misc/misc_types.hpp"
#include "../strings/sconcat_etc.hpp"
#include "../metaprog_defines.hpp"

#include "../concepts/misc_concepts.hpp"
#include "../gen_class_innards_defines.hpp"

#include <utility>

namespace liborangepower
{

using namespace integer_types;

namespace binser
{
//--------
class Value;
//--------
using ValueSptr = std::shared_ptr<Value>;
using ValueVec = std::vector<ValueSptr>;
using ValueMap = std::unordered_map<std::string, ValueSptr>;
using ValueMapInsertRet = std::pair<typename ValueMap::iterator, bool>;
//--------
//// `_holds_mbrs` is short for "holds members"
//template<bool _holds_mbrs>
//class ValueMap final
//{
//public:		// constants
//	static constexpr inline bool HOLDS_MBRS = _holds_mbrs;
//public:		// variables
//	std::unordered_map<std::string, Value> data;
//};
//--------
using ValueData
	= std::variant
	<
		u8, i8, u16, i16, u32, i32, u64, i64, float, double, bool,
		std::string,
		ValueVec,
		//ValueMap<true>,
		//ValueMap<false>
		ValueMap
	>;
//--------
template<typename T>
concept IsValueDataNum
	= std::same_as<T, u8> || std::same_as<T, i8>
	|| std::same_as<T, u16> || std::same_as<T, i16>
	|| std::same_as<T, u32> || std::same_as<T, i32>
	|| std::same_as<T, u64> || std::same_as<T, i64>

	|| std::same_as<T, float> || std::same_as<T, double>

	// `bool` is perhaps not technically a numeric type, but it kind of is,
	// I guess?
	|| std::same_as<T, bool>;

template<typename T>
concept IsValueDataNumOrStr
	= IsValueDataNum<T> || std::same_as<T, std::string>;

template<typename T>
concept IsValueData
	= IsValueDataNumOrStr<T>
	|| std::same_as<T, ValueVec>
	//|| std::same_as<T, ValueMap<true>>
	//|| std::same_as<T, ValueMap<false>>;
	|| std::same_as<T, ValueMap>;

template<typename T>
concept IsValueDataNonNum
	= std::same_as<T, std::string>
	|| std::same_as<T, ValueVec>
	|| std::same_as<T, ValueMap>;
//--------
class Value final
{
public:		// types
	enum class Tag: char
	{
		UInt8,
		Int8,
		UInt16,
		Int16,
		UInt32,
		Int32,
		UInt64,
		Int64,

		Float,
		Double,

		Bool,

		Str,
		Vec,
		Map,
	};
private:		// variables
	ValueData _data = static_cast<u8>(0u);
public:		// functions
	//--------
	inline Value() = default;
	template<IsValueData T>
	inline Value(const T& s_data)
	{
		*this = s_data;
	}
	template<IsValueData T>
	inline Value(T&& s_data)
	{
		*this = std::move(s_data);
	}
//--------
private:		// functions
	template<typename T>
	static inline T _inner_init_do_memcpy
		(const std::vector<char>& to_cast, u64& i, const Tag& tag)
	{
		T temp_ret;

		if (i + sizeof(T) >= to_cast.size())
		{
			throw std::invalid_argument(strings::sconcat
				("Value::_inner_init_do_memcpy(): ",
				"do_memcpy(): i + sizeof(T) >= to_cast.size(): ",
				static_cast<int>(tag), " ", i, " ", sizeof(T), " ",
				to_cast.size(), "."));
		}

		std::memcpy(&temp_ret, to_cast.data() + i, sizeof(T));
		i += sizeof(T);

		return temp_ret;
	}
	void _inner_init(const std::vector<char>& to_cast, u64& i);
public:		// functions
	inline Value(const std::vector<char>& to_cast)
	{
		u64 i = 0;
		_inner_init(to_cast, i);
	}
	//--------
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Value);
	inline ~Value() = default;

	operator std::vector<char> () const;
	//--------
	template<IsValueData T> 
	inline Value& operator = (const T& n_data) noexcept
	{
		_data = n_data;
		return *this;
	}
	template<IsValueData T>
	inline Value& operator = (T&& n_data) noexcept
	{
		_data = std::move(n_data);
		return *this;
	}
	//--------
	template<IsValueData T>
	constexpr inline bool holds_alternative() const noexcept
	{
		return std::holds_alternative<T>(_data);
	}
	constexpr inline bool holds_num_alternative() const noexcept
	{
		return holds_any_int_alternative()
			|| holds_fp_alternative()
			|| holds_alternative<bool>();
	}
	constexpr inline bool holds_any_int_alternative() const noexcept
	{
		return holds_alternative<u8>() || holds_alternative<i8>()
			|| holds_alternative<u16>() || holds_alternative<i16>()
			|| holds_alternative<u32>() || holds_alternative<i32>()
			|| holds_alternative<u64>() || holds_alternative<i64>();
	}
	constexpr inline bool holds_fp_alternative() const noexcept
	{
		return holds_alternative<float>() || holds_alternative<double>();
	}
	//--------
	template<IsValueData T>
	inline bool set_type_if_not_ha()
	{
		//std::cout << "testificate: " << typeid(T()).name() << "\n";
		if (!holds_alternative<T>())
		{
			*this = T();
			return true;
		}
		return false;
	}

	template<IsValueData T>
	T& get()
	{
		return std::get<T>(_data);
	}
	template<IsValueData T>
	const T& get() const
	{
		return std::get<T>(_data);
	}

	inline std::string& as_str()
	{
		return get<std::string>();
	}
	inline const std::string& as_str() const
	{
		return get<std::string>();
	}
	inline ValueVec& as_vec()
	{
		return get<ValueVec>();
	}
	inline const ValueVec& as_vec() const
	{
		return get<ValueVec>();
	}
	inline ValueMap& as_map()
	{
		return get<ValueMap>();
	}
	inline const ValueMap& as_map() const
	{
		return get<ValueMap>();
	}
	//--------
	size_t size() const;
	//--------
	inline Value& at(u64 where)
	{
		return *as_vec().at(where);
	}
	inline const Value& at(u64 where) const
	{
		return *as_vec().at(where);
	}

	//inline Value& operator [] (u64 where)
	//{
	//	return *as_vec()[where];
	//}
	//inline const Value& operator [] (u64 where) const
	//{
	//	return *as_vec()[where];
	//}
	inline void push_back(const Value& to_push)
	{
		set_type_if_not_ha<ValueVec>();
		as_vec().push_back(ValueSptr(new Value(to_push)));
	}
	inline void push_back(Value&& to_push)
	{
		set_type_if_not_ha<ValueVec>();
		as_vec().push_back(ValueSptr(new Value(std::move(to_push))));
	}
	//--------
	inline Value& at(const std::string& where)
	{
		return *as_map().at(where);
	}
	inline const Value& at(const std::string& where) const
	{
		return *as_map().at(where);
	}

	//inline Value& operator [] (const std::string& where)
	//{
	//	return *get<ValueMap>()[where];
	//}
	//inline const Value& operator [] (const std::string& where) const
	//{
	//	return *get<ValueMap>()[where];
	//}
	inline ValueMapInsertRet insert(const std::string& where,
		const Value& to_insert)
	{
		set_type_if_not_ha<ValueMap>();
		return as_map().insert(typename ValueMap::value_type
			(where, ValueSptr(new Value(to_insert))));
	}
	inline ValueMapInsertRet insert(const std::string& where,
		Value&& to_insert)
	{
		set_type_if_not_ha<ValueMap>();
		return as_map().insert(typename ValueMap::value_type
			(where, ValueSptr(new Value(std::move(to_insert)))));
	}
	//--------
};
//--------
} // namespace binser
} // namespace liborangepower

#endif		// liborangepower_binser_value_class_hpp
