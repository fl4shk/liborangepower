#ifndef liborangepower_binser_serialize_funcs_hpp
#define liborangepower_binser_serialize_funcs_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_output_funcs.hpp"
#include "../misc/misc_defines.hpp"
#include "../math/vec2_classes.hpp"
#include "../math/vec3_classes.hpp"
#include "../containers/prev_curr_pair_classes.hpp"
#include "../containers/linked_list_classes.hpp"
#include "../containers/std_container_id_funcs.hpp"
#include "../strings/sconcat_etc.hpp"
#include "../metaprog_defines.hpp"

#include "../concepts/is_specialization_concepts.hpp"
#include "../concepts/misc_concepts.hpp"

#include "value_class.hpp"
#include "from_bv_factory_stuff.hpp"
#include "ex_container_classes.hpp"

namespace liborangepower
{

using strings::sconcat;

using concepts::is_specialization;

using math::is_vec2;
using math::is_vec3;

using containers::is_prev_curr_pair;
//using containers::is_move_only_prev_curr_pair;

using containers::is_ind_circ_link_list;

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

namespace binser
{

//class BlankValue;

template<typename T>
inline Value vec2_to_bv(const math::Vec2<T>& vec)
{
	Value ret;

	ret.insert("x", vec.x);
	ret.insert("y", vec.y);

	return ret;
}
template<typename T>
inline Value vec3_to_bv(const math::Vec3<T>& vec)
{
	Value ret;

	ret.insert("x", vec.x);
	ret.insert("y", vec.y);
	ret.insert("z", vec.z);

	return ret;
}


template<typename ValT>
inline void val_from_bv_test_ex_cs
(
	const std::optional<std::string>& func_name,
	const std::optional<std::string>& msg,
	const auto& ret_data_size, const std::string& ret_data_size_str,
	const ValT& data, const std::string& data_str,
	const ExSizeT& checked_size, const std::string& checked_size_str,
	const ExBoolT& cs_is_max, const std::string& cs_is_max_str,
	const ExSizeT& min_size, const std::string& min_size_str
)
{
	//const auto& ret_data_size = ret.data.size();
	//if (!ret.cs_is_max)
	//{
	//	if (ret_data_size != ret.checked_size)
	//	{
	//		throw std::invalid_argument(sconcat
	//			("liborangepower::binser::val_from_bv(): ",
	//			"is vector/deque with extras: ",
	//			"ret_data_size != ret.checked_size: ",
	//			ret_data_size, " ", ret.checked_size));
	//	}
	//}
	//else // if (ret.cs_is_max)
	//{
	//	if (ret_data_size < ret.min_size
	//		|| ret_data_size > ret.checked_size)
	//	{
	//		throw std::invalid_argument(sconcat
	//			("liborangepower::binser::val_from_bv(): ",
	//			"is vector/deque with extras: ",
	//			"ret_data_size < ret.min_size ",
	//			"|| ret_data_size > ret.checked_size: ",
	//			ret_data_size, " ", ret.min_size, " ",
	//			ret.checked_size));
	//	}
	//}
	if (!cs_is_max)
	{
		if (ret_data_size != checked_size)
		{
			throw std::invalid_argument
			(
				sconcat
				(
					(
						func_name
						? sconcat(*func_name, "(): ")
						: std::string()
					),
					(msg ? sconcat(*msg, ": ") : std::string()),
					"(!", cs_is_max_str, ") "
						"&& "
						"(",
							ret_data_size_str, " != ", checked_size_str,
						"): ",
					ret_data_size, " ", checked_size
				)
			);
		}
	}
	else // if (cs_is_max)
	{
		if (ret_data_size < min_size
			|| ret_data_size > checked_size)
		{
			throw std::invalid_argument
			(
				sconcat
				(
					(
						func_name 
						? sconcat(*func_name, "(): ")
						: std::string()
					),
					(msg ? sconcat(*msg, ": ") : std::string()),
					cs_is_max_str, 
						" && (", 
							ret_data_size_str, " < ", min_size_str,
							" || ", ret_data_size_str > checked_size_str, 
						"): ",
					ret_data_size, " ", min_size, " ", checked_size
				)
			);
		}
	}
}
template<typename ValT>
inline void val_from_bv_test_ex_mm_err
(
	const std::optional<std::string>& func_name,
	const std::optional<std::string>& msg,
	const ValT& data, const std::string& data_str, 
	const ValT& min, const std::string& min_str,
	const ValT& max, const std::string& max_str
)
{
	throw std::invalid_argument
	(
		sconcat
		(
			(func_name ? sconcat(*func_name, "(): ") : std::string()),
			(msg ? sconcat(*msg, ": ") : std::string()),
			data_str, " < ", min_str,
				" || ", data_str, " || ", max_str,
				": ",
			data, " ", min, " ", max
		)
	);
}
template<typename ValT>
inline void val_from_bv_test_ex_mm
(
	const std::optional<std::string>& func_name,
	const std::optional<std::string>& msg,
	const ValT& data, const std::string& data_str, 
	const ValT& min, const std::string& min_str,
	const ValT& max, const std::string& max_str
)
{
	//if ((ret.data.x < ret.min.x) || (ret.data.x > ret.max.x))
	//{
	//	throw std::invalid_argument(sconcat
	//		("liborangepower::binser::val_from_bv(): ",
	//		"is_vec3_ex: ",
	//		"ret.data.x < ret.min.x || ret.data.x > ret.max.x: ",
	//		ret.data.x, " ", ret.min.x, " ", ret.max.x));
	//}
	if (data < min || data > max)
	{
		val_from_bv_test_ex_mm_err
		(
			func_name, msg,
			data, data_str,
			min, min_str,
			max, max_str
		);
	}
}

template<typename T, typename BaseT>
inline void val_from_bv(T& ret, const Value& bv,
	FromBvFactoryFuncMap<BaseT>* func_map)
{
	//--------
	using NonCvrefT = std::remove_cvref_t<T>;
	//--------
	//if constexpr (std::is_same<NonCvrefT, int>())
	//{
	//	ret = bv.asInt();
	//}
	//else if constexpr (std::is_same<NonCvrefT, uint>())
	//{
	//	ret = bv.asUInt();
	//}
	//else if constexpr (std::is_same<NonCvrefT, int64_t>())
	//{
	//	ret = bv.asInt64();
	//}
	//else if constexpr (std::is_same<NonCvrefT, uint64_t>())
	//{
	//	ret = bv.asUInt64();
	//}
	//else if constexpr (std::is_same<NonCvrefT, float>())
	//{
	//	ret = bv.asFloat();
	//}
	//else if constexpr (std::is_same<NonCvrefT, double>())
	//{
	//	ret = bv.asDouble();
	//}
	//else if constexpr (std::is_same<NonCvrefT, bool>())
	//{
	//	ret = bv.asBool();
	//}
	//else if constexpr (is_specialization<NonCvrefT, std::basic_string>())
	//{
	//	ret = bv.asString();
	//}
	if constexpr (std::is_same<NonCvrefT, char>())
	{
		ret = bv.get<std::string>().front();
	}
	else if constexpr (std::is_same<NonCvrefT, std::monostate>()
		|| IsValueDataNumOrStr<NonCvrefT>)
	{
		ret = bv.get<NonCvrefT>();
	}
	else if constexpr (std::is_enum<NonCvrefT>())
	{
		//ret = bv.get<std::underlying_type_t<NonCvrefT>>();
		std::underlying_type_t<NonCvrefT> temp;
		val_from_bv(temp, bv, func_map);
		ret = NonCvrefT(temp);
	}
	//--------
	else if constexpr (is_scalar_ex<NonCvrefT>())
	{
		val_from_bv(ret.data, bv, func_map);

		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_scalar_ex: ",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data,
				ret.min,
				ret.max))
		);
	}
	//--------
	else if constexpr (is_vec2<NonCvrefT>())
	{
		val_from_bv(ret.x, bv.at("x"), func_map);
		val_from_bv(ret.y, bv.at("y"), func_map);
	}
	else if constexpr (is_vec3<NonCvrefT>())
	{
		val_from_bv(ret.x, bv.at("x"), func_map);
		val_from_bv(ret.y, bv.at("y"), func_map);
		val_from_bv(ret.z, bv.at("z"), func_map);
	}
	else if constexpr (is_vec2_ex<NonCvrefT>())
	{
		val_from_bv(ret.data, bv, func_map);

		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_vec2_ex: ",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.x,
				ret.min.x,
				ret.max.x))
		);
		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_vec2_ex: ",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.y,
				ret.min.y,
				ret.max.y))
		);
	}
	else if constexpr (is_vec3_ex<NonCvrefT>())
	{
		val_from_bv(ret.data, bv, func_map);

		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_vec3_ex: ",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.x,
				ret.min.x,
				ret.max.x))
		);
		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_vec3_ex: ",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.y,
				ret.min.y,
				ret.max.y))
		);
		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_vec3_ex: ",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.z,
				ret.min.z,
				ret.max.z))
		);
	}
	else if constexpr (is_line_seg2_ex<NonCvrefT>())
	{
		val_from_bv(ret.data, bv, func_map);

		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_line_seg2_ex",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.p0.x,
				ret.min.p0.x,
				ret.max.p0.x))
		);
		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_line_seg2_ex",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.p0.y,
				ret.min.p0.y,
				ret.max.p0.y))
		);
		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_line_seg2_ex",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.p1.x,
				ret.min.p1.x,
				ret.max.p1.x))
		);
		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_line_seg2_ex",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.p1.y,
				ret.min.p1.y,
				ret.max.p1.y))
		);
	}
	else if constexpr (is_rect2_ex<NonCvrefT>())
	{
		val_from_bv(ret.data, bv, func_map);

		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_rect2_ex",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.pos.x,
				ret.min.pos.x,
				ret.max.pos.x))
		);
		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_rect2_ex",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.pos.y,
				ret.min.pos.y,
				ret.max.pos.y))
		);
		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_rect2_ex",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.size_2d.x,
				ret.min.size_2d.x,
				ret.max.size_2d.x))
		);
		val_from_bv_test_ex_mm
		(
			"liborangepower::binser::val_from_bv",
			"is_rect2_ex",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.size_2d.y,
				ret.min.size_2d.y,
				ret.max.size_2d.y))
		);
	}
	else if constexpr
	(
		is_prev_curr_pair<NonCvrefT>()
		//|| is_move_only_prev_curr_pair<NonCvrefT>()
	)
	{
		val_from_bv(ret(), bv.at("_prev"), func_map);
		ret.back_up();
		val_from_bv(ret(), bv.at("_curr"), func_map);
	}
	//--------
	else if constexpr (is_ind_circ_link_list<NonCvrefT>())
	{
		ret = NonCvrefT();

		for (size_t i=0; i<bv.size(); ++i)
		{
			using ElemT = typename NonCvrefT::ElemT;
			ElemT temp;

			val_from_bv(temp, bv.at(i), func_map);

			if constexpr (is_non_arr_std_unique_ptr<ElemT>())
			{
				ret.push_back(std::move(temp));
			}
			else
			{
				ret.push_back(temp);
			}
		}
	}
	//--------
	else if constexpr (is_non_arr_std_unique_ptr<NonCvrefT>()
		|| is_non_arr_std_shared_ptr<NonCvrefT>()
		|| is_non_arr_std_weak_ptr<NonCvrefT>())
	{
		using ElemT = typename NonCvrefT::element_type;

		const Value& obj = bv.at("obj");
		//bool has_kind_str;
		//val_from_bv(has_kind_str, bv.at("has_kind_str"), func_map);

		//if (!bv.isMember("kind_str"))
		if constexpr (!std::is_same<ElemT, BaseT>())
		{
			//return NonCvrefT(new ElemT(val_from_bv<ElemT>(obj)));
			ElemT temp;
			val_from_bv(temp, obj, func_map);
			ret.reset(new ElemT(temp));
		}
		//else // if (bv.isMember("kind_str"))
		else // if (std::is_same<ElemT, BaseT>())
		{
			if (!func_map)
			{
				throw std::invalid_argument(sconcat
					("liborangepower::binser::val_from_bv(): ",
					"is non-array smart pointer: ",
					"Need a non-null `func_map` in this case"));
			}
			std::string kind_str;
			val_from_bv(kind_str, bv.at("kind_str"), func_map);

			//ret.reset(func_map->at(kind_str)(obj));
			ret = func_map->at(kind_str)(obj);
		}
	}
	else if constexpr (is_std_array<NonCvrefT>())
	{
		ret = NonCvrefT();

		if (ret.size() != bv.size())
		{
			throw std::invalid_argument(sconcat
				("liborangepower::binser::val_from_bv(): ",
				"is_std_array<NonCvrefT>(): ",
				"ret.size() != bv.size(): ",
				ret.size(), " ", bv.size()));
		}

		for (size_t i=0; i<bv.size(); ++i)
		{
			val_from_bv(ret[i], bv.at(i), func_map);
		}
	}
	else if constexpr (is_vector_ex<NonCvrefT>()
		|| is_deque_ex<NonCvrefT>()
		|| is_ind_circ_link_list_ex<NonCvrefT>())
	{
		//ret = NonCvrefT();

		//val_from_bv(ret.data, bv.at("data"), func_map);
		val_from_bv(ret.data, bv, func_map);

		// Prevent multiple O(n) computations of `ret.data.size()` when
		// `is_ind_circ_link_list_ex<NonCvrefT>()` is `true`.
		//const auto& ret_data_size = ret.data.size();
		//if (!ret.cs_is_max)
		//{
		//	if (ret_data_size != ret.checked_size)
		//	{
		//		throw std::invalid_argument(sconcat
		//			("liborangepower::binser::val_from_bv(): ",
		//			"is vector/deque with extras: ",
		//			"ret_data_size != ret.checked_size: ",
		//			ret_data_size, " ", ret.checked_size));
		//	}
		//}
		//else // if (ret.cs_is_max)
		//{
		//	if (ret_data_size < ret.min_size
		//		|| ret_data_size > ret.checked_size)
		//	{
		//		throw std::invalid_argument(sconcat
		//			("liborangepower::binser::val_from_bv(): ",
		//			"is vector/deque with extras: ",
		//			"ret_data_size < ret.min_size ",
		//			"|| ret_data_size > ret.checked_size: ",
		//			ret_data_size, " ", ret.min_size, " ",
		//			ret.checked_size));
		//	}
		//}
		val_from_bv_test_ex_cs
		(
			"liborangepower::binser::val_from_bv",
			"is vector/deque with extras",
			EVAL(MAP(ARG_DUP_AS_STR, COMMA,
				ret.data.size(),
				ret.data,
				ret.checked_size,
				ret.cs_is_max,
				ret.min_size))
		);
		//#define TEST_MAP_MACRO(x) printout(x, "\n")
		//EVAL(MAP(TEST_MAP_MACRO, SEMICOLON,
		//	ret.data,
		//	ret.checked_size,
		//	ret.cs_is_max,
		//	ret.min_size));
		//#undef TEST_MAP_MACRO
	}
	else if constexpr (is_pseudo_vec_like_std_container<NonCvrefT>())
	{
		ret = NonCvrefT();

		//for (size_t i=1; i<bv.size(); ++i)
		for (size_t i=0; i<bv.size(); ++i)
		{
			if constexpr (is_vec_like_std_container<NonCvrefT>())
			{
				using ValueT = typename NonCvrefT::value_type;
				ValueT temp;

				val_from_bv(temp, bv.at(i), func_map);

				if constexpr (is_non_arr_std_unique_ptr<ValueT>())
				{
					ret.push_back(std::move(temp));
				}
				else
				{
					ret.push_back(temp);
				}
			}
			else // if constexpr (is_set_like_std_container<NonCvrefT>())
			{
				using KeyT = typename NonCvrefT::key_type;
				KeyT temp;

				val_from_bv(temp, bv.at(i), func_map);

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

		//for (size_t i=1; i<bv.size(); ++i)
		for (size_t i=0; i<bv.size(); i+=2)
		{
			KeyT key;
			val_from_bv(key, bv.at(i), func_map);

			MappedT value;
			val_from_bv(value, bv.at(i + 1), func_map);

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
	else if constexpr (HasBvDeserializeFunc<NonCvrefT>)
	{
		ret.deserialize(bv);
	}
	else if constexpr (std::is_constructible<NonCvrefT, Value>())
	{
		ret = NonCvrefT(bv);
	}
	else
	{
		// Assume a static member function called `from_bv` exists
		ret = NonCvrefT::from_bv(bv);
	}
	//--------
}
template<typename T>
inline void val_from_bv(T& ret, const Value& bv,
	const std::nullopt_t& some_nullopt)
{
	val_from_bv<T, void>(ret, bv, nullptr);
}

template<typename T, typename BaseT>
inline void get_bv_memb(T& ret, const Value& bv,
	const std::string& name, FromBvFactoryFuncMap<BaseT>* func_map)
{
	val_from_bv(ret, bv.at(name), func_map);
}
template<typename T>
inline void get_bv_memb(T& ret, const Value& bv,
	const std::string& name, const std::nullopt_t& some_nullopt)
{
	//FromBvFactoryFuncMap<void> func_map;
	//get_bv_memb(ret, bv, name, func_map);
	//val_from_bv(ret, bv.at(name), std::nullopt);
	val_from_bv<T, void>(ret, bv.at(name), nullptr);
}

template<typename TempT, typename RetT, typename BaseT>
inline void get_bv_memb_w_stat_cast(RetT& ret, const Value& bv,
	const std::string& name, FromBvFactoryFuncMap<BaseT>* func_map)
{
	TempT temp;
	get_bv_memb(temp, bv, name, func_map);
	ret = static_cast<RetT>(temp);
}
template<typename TempT, typename RetT>
inline void get_bv_memb_w_stat_cast(RetT& ret, const Value& bv,
	const std::string& name, const std::nullopt_t& some_nullopt)
{
	TempT temp;
	get_bv_memb(temp, bv, name, some_nullopt);
	ret = static_cast<RetT>(temp);
}

template<typename T>
inline void set_bv(Value& bv, const T& val);

template<typename T>
inline void set_bv_sptr_w_rst(ValueSptr& bv_sptr, const T& val)
{
	Value bv;
	set_bv(bv, val);
	bv_sptr.reset(new Value(std::move(bv)));
}

template<MapLikeStdContnr T>
inline void set_bv_map_like_std_container(Value& bv, const T& val,
	const std::function<bool(const typename T::value_type&)>& skip_func)
{
	//--------
	bv = ValueVec();
	//--------
	for (const auto& pair: val)
	{
		if (!skip_func(pair))
		{
			Value to_push;

			set_bv(to_push, pair.first);
			bv.push_back(std::move(to_push));

			set_bv(to_push, pair.second);
			bv.push_back(std::move(to_push));
		}
	}
	//--------
}

template<MapLikeStdContnr T>
inline void set_bv_map_like_std_container(Value& bv, const T& val)
{
	set_bv_map_like_std_container(bv, val,
		[](const typename T::value_type& pair) -> bool
			{ return false; });
}

//template<containers::MapLikeStdContnr T>
//inline void set_bv_map_like_std_container(Value& bv, const T& val,
//	const std::nullopt_t& some_nullopt)
//{
//	set_bv_map_like_std_container(bv, val, nullptr);
//}

template<typename T>
inline void set_bv(Value& bv, const T& val)
{
	using NonCvrefT = std::remove_cvref_t<T>;

	bv = Value();

	//static_assert(!std::is_same<T, int64_t>()
	//	&& !std::is_same<T, uint64_t>());
	//--------
	if constexpr (std::is_same<NonCvrefT, char>())
	{
		std::string temp_str;
		temp_str += val;
		bv = std::move(temp_str);
	}
	else if constexpr (std::is_enum<NonCvrefT>())
	{
		set_bv(bv, std::underlying_type_t<NonCvrefT>(val));
	}
	//--------
	else if constexpr (is_scalar_ex<NonCvrefT>())
	{
		set_bv(bv, val.data);
	}
	//--------
	else if constexpr (is_vec2<NonCvrefT>())
	{
		bv = vec2_to_bv(val);
	}
	else if constexpr (is_vec3<NonCvrefT>())
	{
		bv = vec3_to_bv(val);
	}
	else if constexpr (is_vec2_ex<NonCvrefT>()
		|| is_vec3_ex<NonCvrefT>()
		|| is_line_seg2_ex<NonCvrefT>()
		|| is_rect2_ex<NonCvrefT>())
	{
		set_bv(bv, val.data);
	}
	else if constexpr
	(
		is_prev_curr_pair<NonCvrefT>()
		//|| is_move_only_prev_curr_pair<NonCvrefT>()
	)
	{
		ValueMap map;

		set_bv_sptr_w_rst(map["_prev"], val.prev());
		set_bv_sptr_w_rst(map["_curr"], val.curr());

		bv = std::move(map);
	}
	//--------
	else if constexpr (is_non_arr_std_unique_ptr<NonCvrefT>()
		|| is_non_arr_std_shared_ptr<NonCvrefT>()
		|| is_non_arr_std_weak_ptr<NonCvrefT>())
	{
		//bv = ValueMap();
		ValueMap map;

		//map["obj"] = *val;
		set_bv_sptr_w_rst(map["obj"], *val);
		using ElemT = typename NonCvrefT::element_type;
		//if constexpr (concepts::HasStaticKindStr<T>)
		//{
		//	map["has_kind_str"] = true;
		//	map["kind_str"] = T::KIND_STR;
		//}
		//else
		if constexpr (concepts::HasKindStrMbrFunc<ElemT>)
		{
			//map["has_kind_str"] = true;
			//map["kind_str"] = ValueSptr(new Value(val->kind_str()));
			map["kind_str"] = Value::to_sptr(val->kind_str());
		}
		//else
		//{
		//	map["has_kind_str"] = false;
		//}
		bv = std::move(map);
	}
	else if constexpr (is_vector_ex<NonCvrefT>()
		|| is_deque_ex<NonCvrefT>()
		|| is_ind_circ_link_list_ex<NonCvrefT>())
	{
		set_bv(bv, val.data);
	}
	else if constexpr (is_arr_like_std_container<NonCvrefT>()
		|| is_ind_circ_link_list<NonCvrefT>())
	{
		ValueVec vec;

		for (const auto& item: val)
		{
			Value inner_bv;
			set_bv(inner_bv, item);
			vec.push_back(Value::to_sptr(std::move(inner_bv)));
		}
		bv = std::move(vec);
	}
	else if constexpr (is_set_like_std_container<NonCvrefT>())
	{
		ValueVec vec;

		for (const auto& key: val)
		{
			Value inner_bv = ValueMap();
			set_bv(inner_bv, key);
			vec.push_back(Value::to_sptr(std::move(inner_bv)));
		}
		bv = std::move(vec);
	}
	else if constexpr (is_map_like_std_container<NonCvrefT>())
	{
		set_bv_map_like_std_container(bv, val);
	}
	//--------
	else
	{
		bv = val;
	}
	//--------
}

template<typename T>
inline void set_bv_memb(Value& bv, const std::string& name, const T& val)
{
	//--------
	//if constexpr (std::is_same<T, int>()
	//	|| std::is_same<T, uint>()
	//	|| std::is_same<T, float>()
	//	|| std::is_same<T, double>())
	//if constexpr (std::is_same<T, int64_t>()
	//	|| std::is_same<T, uint64_t>())
	//{
	//	bv[sconcat(name, ".high")] 
	//		= uint32_t(uint64_t(val)
	//			>> uint64_t(32u));
	//	bv[sconcat(name, ".low")]
	//		= uint32_t(uint64_t(val)
	//			& uint64_t(0xffffffffu));
	//}
	//else
	//{
	//	set_bv(bv[name], val);
	//}

	Value temp;
	set_bv(temp, val);
	bv.insert(name, std::move(temp));
}

inline void parse_binser(std::istream& is, binser::Value& root)
{
	std::vector<char> vec;
	while (!is.eof())
	{
		vec.push_back(is.get());
	}
	root = vec;
}
inline bool parse_binser(const std::string& input_file_name, 
	binser::Value& root)
{
	if (auto file=std::fstream(input_file_name,
		std::ios_base::in | std::ios_base::binary);
		file.is_open())
	{
		parse_binser(file, root);
		return true;
	}
	else
	{
		return false;
	}
}

inline void write_binser(std::ostream& os, const binser::Value& root)
{
	const auto& ser_vec = std::vector<char>(root);
	for (const auto& c: ser_vec)
	{
		os.put(c);
	}
}
inline bool write_binser(const std::string& output_file_name, 
	const binser::Value& root)
{
	if (auto file=std::fstream(output_file_name,
		std::ios_base::out | std::ios_base::binary);
		file.is_open())
	{
		write_binser(file, root);
		return true;
	}
	else
	{
		return false;
	}
}

//class BlankValue final
//{
//public:		// functions
//	constexpr inline BlankValue() = default;
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(BlankValue);
//	constexpr inline BlankValue(const Value& bv)
//	{
//	}
//
//	inline operator Value () const
//	{
//		Value ret;
//
//		//set_bv_memb(ret, "<is_blank_value>", true);
//
//		return ret;
//	}
//};

} // namespace binser
} // namespace liborangepower

#endif		// liborangepower_binser_serialize_funcs_hpp
