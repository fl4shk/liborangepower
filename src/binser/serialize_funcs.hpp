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

namespace liborangepower {
//--------
using strings::sconcat;

using concepts::is_specialization;

using math::is_vec2;
using math::is_vec3;

using containers::is_prev_curr_pair;
//using containers::is_move_only_prev_curr_pair;

using containers::is_ind_circ_link_list;

using containers::is_std_unique_ptr_to_non_arr;
using containers::is_std_shared_ptr_to_non_arr;
using containers::is_std_weak_ptr_to_non_arr;
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

namespace binser {
//--------
//class BlankValue;

template<typename T>
inline Value vec2_to_bv(const math::Vec2<T>& vec) {
	Value ret;

	ret.insert("x", vec.x);
	ret.insert("y", vec.y);

	return ret;
}
template<typename T>
inline Value vec3_to_bv(const math::Vec3<T>& vec) {
	Value ret;

	ret.insert("x", vec.x);
	ret.insert("y", vec.y);
	ret.insert("z", vec.z);

	return ret;
}


template<typename ValT>
inline void val_from_bv_test_ex_cs(
	const std::optional<std::string>& func_name,
	const std::optional<std::string>& msg,
	const auto& ret_data_size, const std::string& ret_data_size_str,
	const ValT& data, const std::string& data_str,
	const ExSizeT& checked_size, const std::string& checked_size_str,
	const ExBoolT& cs_is_max, const std::string& cs_is_max_str,
	const ExSizeT& min_size, const std::string& min_size_str
) {
	//const auto& ret_data_size = ret.data.size();
	//if (!ret.cs_is_max) {
	//	if (ret_data_size != ret.checked_size) {
	//		throw std::invalid_argument(sconcat(
	//	"liborangepower::binser::val_from_bv(): ",
	//			"is vector/deque with extras: ",
	//			"ret_data_size != ret.checked_size: ",
	//			ret_data_size, " ", ret.checked_size
	//	));
	//	}
	//} else { // if (ret.cs_is_max)
	//	if (ret_data_size < ret.min_size
	//	|| ret_data_size > ret.checked_size) {
	//		throw std::invalid_argument(sconcat(
	//			"liborangepower::binser::val_from_bv(): ",
	//			"is vector/deque with extras: ",
	//			"ret_data_size < ret.min_size ",
	//			"|| ret_data_size > ret.checked_size: ",
	//			ret_data_size, " ", ret.min_size, " ",
	//			ret.checked_size
	//		));
	//	}
	//}
	if (!cs_is_max) {
		if (ret_data_size != checked_size) {
			throw std::invalid_argument(sconcat(
				(func_name ? sconcat(*func_name, "(): ") : std::string()),
				(msg ? sconcat(*msg, ": ") : std::string()),
				"(!", cs_is_max_str, ")",
				" && (", ret_data_size_str, " != ", checked_size_str, ")",
				": ", ret_data_size, " ", checked_size
			));
		}
	} else { // if (cs_is_max)
		if (ret_data_size < min_size || ret_data_size > checked_size) {
			throw std::invalid_argument(sconcat(
				(func_name ? sconcat(*func_name, "(): ") : std::string()),
				(msg ? sconcat(*msg, ": ") : std::string()),
				cs_is_max_str, 
				" && (", ret_data_size_str, " < ", min_size_str,
				" || ", ret_data_size_str > checked_size_str, "): ",
				ret_data_size, " ", min_size, " ", checked_size
			));
		}
	}
}
template<typename ValT>
inline void val_from_bv_test_ex_mm_err(
	const std::optional<std::string>& func_name,
	const std::optional<std::string>& msg,
	const ValT& data, const std::string& data_str, 
	const ValT& min, const std::string& min_str,
	const ValT& max, const std::string& max_str
) {
	throw std::invalid_argument(sconcat(
		(func_name ? sconcat(*func_name, "(): ") : std::string()),
		(msg ? sconcat(*msg, ": ") : std::string()),
		data_str, " < ", min_str, " || ", data_str, " || ", max_str, ": ",
		data, " ", min, " ", max
	));
}
template<typename ValT>
inline void val_from_bv_test_ex_mm(
	const std::optional<std::string>& func_name,
	const std::optional<std::string>& msg,
	const ValT& data, const std::string& data_str, 
	const ValT& min, const std::string& min_str,
	const ValT& max, const std::string& max_str
) {
	//if ((ret.data.x < ret.min.x) || (ret.data.x > ret.max.x)) {
	//	throw std::invalid_argument(sconcat(
	//		"liborangepower::binser::val_from_bv(): ",
	//		"is_vec3_ex: ",
	//		"ret.data.x < ret.min.x || ret.data.x > ret.max.x: ",
	//		ret.data.x, " ", ret.min.x, " ", ret.max.x
	//	));
	//}
	if (data < min || data > max) {
		val_from_bv_test_ex_mm_err(
			func_name, msg,
			data, data_str,
			min, min_str,
			max, max_str
		);
	}
}

//template<typename ValueEtcT, typename T, typename BaseT,
//	typename IteratorT>
//inline void _val_from_bv_handle_ex_contnr(
//	T& ret, const Value& bv, FromBvFactoryFuncUmap<BaseT>* func_umap
//) {
//}

//template<typename ValueEtcT>
//concept IsValFromBvFieDoCopy
//	= (!(is_std_unique_ptr_to_non_arr<ValueEtcT>()
//	|| std::movable<ValueEtcT>));
//
//template<typename ValueEtcT>
//concept IsValFromBvFieDoMove
//	= (!IsValFromBvFieDoCopy<ValueEtcT>);
//
//template<IsValFromBvFieDoCopy ValueEtcT>
//inline void _val_from_bv_final_insert_etc(
//	const std::function<void(const ValueEtcT&)>& copy_func,
//	const std::function<void(ValueEtcT&&)>& move_func,
//	const ValueEtcT& temp
//) {
//	copy_func(temp);
//}
//template<IsValFromBvFieDoMove ValueEtcT>
//inline void _val_from_bv_final_insert_etc(
//	const std::function<void(const ValueEtcT&)>& copy_func,
//	const std::function<void(ValueEtcT&&)>& move_func,
//	ValueEtcT&& temp
//) {
//	move_func(std::move(temp));
//}

template<typename IterT>
inline void _val_from_bv_inc_iter(
	IterT& some_iter, const IterT& some_end
) {
	if (some_iter != some_end) {
		++some_iter;
	}
}

template<typename T, typename BaseT>
inline void val_from_bv(
	T& ret, const Value& bv, FromBvFactoryFuncUmap<BaseT>* func_umap
) {
	#define BINSER_VAL_FROM_BV_COPY_EX_STUFF_AND_CALL_VFBV(ValueEtcT, \
		temp, to_copy_ex_stuff_from, some_bv) \
		do { \
			if constexpr (LikeExContnrAny<ValueEtcT>) { \
				copy_ex_contnr_extras(temp, to_copy_ex_stuff_from); \
			} \
			val_from_bv(temp, some_bv, func_umap); \
		} while (0)

	#define BINSER_VAL_FROM_BV_FINAL_INSERT_ETC(ValueEtcT, temp, \
		copy_func, move_func) \
		do { \
			if constexpr ( \
				!(is_std_unique_ptr_to_non_arr<ValueEtcT>() \
				|| std::movable<ValueEtcT>) \
			) { \
				copy_func (temp); \
			} else { \
				move_func (std::move(temp)); \
			} \
		} while (0)
	//--------
	using NonCvrefT = std::remove_cvref_t<T>;
	//--------
	//if constexpr (std::is_same<NonCvrefT, int>()) {
	//	ret = bv.asInt();
	//} else if constexpr (std::is_same<NonCvrefT, uint>()) {
	//	ret = bv.asUInt();
	//} else if constexpr (std::is_same<NonCvrefT, int64_t>()) {
	//	ret = bv.asInt64();
	//} else if constexpr (std::is_same<NonCvrefT, uint64_t>()) {
	//	ret = bv.asUInt64();
	//} else if constexpr (std::is_same<NonCvrefT, float>()) {
	//	ret = bv.asFloat();
	//} else if constexpr (std::is_same<NonCvrefT, double>()) {
	//	ret = bv.asDouble();
	//} else if constexpr (std::is_same<NonCvrefT, bool>()) {
	//	ret = bv.asBool();
	//} else if constexpr (
	//	is_specialization<NonCvrefT, std::basic_string>()
	//) {
	//	ret = bv.asString();
	//}
	if constexpr (std::is_same<NonCvrefT, char>()) {
		ret = bv.get<std::string>().front();
	} else if constexpr (std::is_same<NonCvrefT, std::monostate>()
	|| IsValueDataNumOrStr<NonCvrefT>) {
		ret = bv.get<NonCvrefT>();
	} else if constexpr (std::is_enum<NonCvrefT>()) {
		//ret = bv.get<std::underlying_type_t<NonCvrefT>>();
		std::underlying_type_t<NonCvrefT> temp;
		val_from_bv(temp, bv, func_umap);
		ret = NonCvrefT(temp);
	}
	//--------
	else if constexpr (is_scalar_ex<NonCvrefT>()) {
		val_from_bv(ret.data, bv, func_umap);

		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_scalar_ex: ",
			ARG_DUP_AS_STR(ret.data),
			ARG_DUP_AS_STR(ret.min),
			ARG_DUP_AS_STR(ret.max)
		);
	}
	//--------
	else if constexpr (is_vec2<NonCvrefT>()) {
		//val_from_bv(ret.x, bv.at("x"), func_umap);
		//val_from_bv(ret.y, bv.at("y"), func_umap);

		#define X(name, dummy_arg) \
			val_from_bv(ret. name , bv.at( #name ), func_umap);
		MEMB_LIST_VEC2(X)
		#undef X
	} else if constexpr (is_vec3<NonCvrefT>()) {
		//val_from_bv(ret.x, bv.at("x"), func_umap);
		//val_from_bv(ret.y, bv.at("y"), func_umap);
		//val_from_bv(ret.z, bv.at("z"), func_umap);

		#define X(name, dummy_arg) \
			val_from_bv(ret. name , bv.at( #name ), func_umap);
		MEMB_LIST_VEC3(X)
		#undef X
	} else if constexpr (is_vec2_ex<NonCvrefT>()) {
		val_from_bv(ret.data, bv, func_umap);

		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_vec2_ex: ",
			ARG_DUP_AS_STR(ret.data.x),
			ARG_DUP_AS_STR(ret.min.x),
			ARG_DUP_AS_STR(ret.max.x)
		);
		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_vec2_ex: ",
			ARG_DUP_AS_STR(ret.data.y),
			ARG_DUP_AS_STR(ret.min.y),
			ARG_DUP_AS_STR(ret.max.y))
		;
	} else if constexpr (is_vec3_ex<NonCvrefT>()) {
		val_from_bv(ret.data, bv, func_umap);

		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_vec3_ex: ",
			ARG_DUP_AS_STR(ret.data.x),
			ARG_DUP_AS_STR(ret.min.x),
			ARG_DUP_AS_STR(ret.max.x)
		);
		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_vec3_ex: ",
			ARG_DUP_AS_STR(ret.data.y),
			ARG_DUP_AS_STR(ret.min.y),
			ARG_DUP_AS_STR(ret.max.y)
		);
		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_vec3_ex: ",
			ARG_DUP_AS_STR(ret.data.z),
			ARG_DUP_AS_STR(ret.min.z),
			ARG_DUP_AS_STR(ret.max.z)
		);
	} else if constexpr (is_line_seg2_ex<NonCvrefT>()) {
		val_from_bv(ret.data, bv, func_umap);

		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_line_seg2_ex",
			ARG_DUP_AS_STR(ret.data.p0.x),
			ARG_DUP_AS_STR(ret.min.p0.x),
			ARG_DUP_AS_STR(ret.max.p0.x)
		);
		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_line_seg2_ex",
			ARG_DUP_AS_STR(ret.data.p0.y),
			ARG_DUP_AS_STR(ret.min.p0.y),
			ARG_DUP_AS_STR(ret.max.p0.y)
		);
		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_line_seg2_ex",
			ARG_DUP_AS_STR(ret.data.p1.x),
			ARG_DUP_AS_STR(ret.min.p1.x),
			ARG_DUP_AS_STR(ret.max.p1.x)
		);
		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_line_seg2_ex",
			ARG_DUP_AS_STR(ret.data.p1.y),
			ARG_DUP_AS_STR(ret.min.p1.y),
			ARG_DUP_AS_STR(ret.max.p1.y)
		);
	} else if constexpr (is_rect2_ex<NonCvrefT>()) {
		val_from_bv(ret.data, bv, func_umap);

		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_rect2_ex",
			ARG_DUP_AS_STR(ret.data.pos.x),
			ARG_DUP_AS_STR(ret.min.pos.x),
			ARG_DUP_AS_STR(ret.max.pos.x)
		);
		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_rect2_ex",
			ARG_DUP_AS_STR(ret.data.pos.y),
			ARG_DUP_AS_STR(ret.min.pos.y),
			ARG_DUP_AS_STR(ret.max.pos.y)
		);
		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_rect2_ex",
			ARG_DUP_AS_STR(ret.data.size_2d.x),
			ARG_DUP_AS_STR(ret.min.size_2d.x),
			ARG_DUP_AS_STR(ret.max.size_2d.x)
		);
		val_from_bv_test_ex_mm(
			"liborangepower::binser::val_from_bv",
			"is_rect2_ex",
			ARG_DUP_AS_STR(ret.data.size_2d.y),
			ARG_DUP_AS_STR(ret.min.size_2d.y),
			ARG_DUP_AS_STR(ret.max.size_2d.y)
		);
	}
	else if constexpr (
		is_prev_curr_pair<NonCvrefT>()
		//|| is_move_only_prev_curr_pair<NonCvrefT>()
	) {
		NonCvrefT to_move;

		using ElemT
			= std::remove_cvref_t<typename NonCvrefT::ElemT>;

		//val_from_bv(to_move(), bv.at("_prev"), func_umap);
		//to_move.back_up();

		//val_from_bv(to_move(), bv.at("_curr"), func_umap);

		BINSER_VAL_FROM_BV_COPY_EX_STUFF_AND_CALL_VFBV(
			ElemT, to_move(), ret.prev(), bv.at("_prev")
		);
		to_move.back_up();

		BINSER_VAL_FROM_BV_COPY_EX_STUFF_AND_CALL_VFBV(
			ElemT, to_move(), ret(), bv.at("_curr")
		);

		//ret = std::move(to_move);

		BINSER_VAL_FROM_BV_FINAL_INSERT_ETC(ElemT, to_move, ret =, ret =);
	}
	//--------
	else if constexpr (is_ind_circ_link_list<NonCvrefT>()) {
		//ret = NonCvrefT();
		NonCvrefT to_move;

		auto iter = ret.begin();

		for (size_t i=0; i<bv.size(); ++i) {
			using ElemT = typename NonCvrefT::ElemT;
			ElemT temp;

			//val_from_bv(temp, bv.at(i), func_umap);
			BINSER_VAL_FROM_BV_COPY_EX_STUFF_AND_CALL_VFBV(ElemT, temp,
				*iter, bv.at(i));

			BINSER_VAL_FROM_BV_FINAL_INSERT_ETC(ElemT, temp, ret.push_back,
				ret.push_back);

			//if (iter != ret.end()) {
			//	++iter;
			//}
			_val_from_bv_inc_iter(iter, ret.end());
		}
	}
	//--------
	else if constexpr (
		is_std_unique_ptr_to_non_arr<NonCvrefT>()
		|| is_std_shared_ptr_to_non_arr<NonCvrefT>()
		|| is_std_weak_ptr_to_non_arr<NonCvrefT>()
	) {
		using ElemT = typename NonCvrefT::element_type;

		const Value& obj = bv.at("obj");
		//bool has_kind_str;
		//val_from_bv(has_kind_str, bv.at("has_kind_str"), func_umap);

		//if (!bv.isMember("kind_str"))
		if constexpr (!std::is_same<ElemT, BaseT>()) {
			//return NonCvrefT(new ElemT(val_from_bv<ElemT>(obj)));
			ElemT temp;
			//val_from_bv(temp, obj, func_umap);
			BINSER_VAL_FROM_BV_COPY_EX_STUFF_AND_CALL_VFBV(ElemT, temp,
				*ret, obj);

			//ret.reset(new ElemT(temp));
			BINSER_VAL_FROM_BV_FINAL_INSERT_ETC(
				ElemT, temp,
				[&](const ElemT& some_temp) -> void
					{ ret.reset(new ElemT(some_temp)); },
				[&](ElemT&& some_temp) -> void
					{ ret.reset(new ElemT(std::move(some_temp))); });
		}
		//else // if (bv.isMember("kind_str"))
		else { // if (std::is_same<ElemT, BaseT>()) 
			if (!func_umap) {
				throw std::invalid_argument(sconcat(
					"liborangepower::binser::val_from_bv(): ",
					"is non-array smart pointer: ",
					"Need a non-null `func_umap` in this case"
				));
			}
			std::string kind_str;
			val_from_bv(kind_str, bv.at("kind_str"), func_umap);

			//ret.reset(func_umap->at(kind_str)(obj));
			ret = func_umap->at(kind_str)(obj);
		}
	} else if constexpr (is_std_array<NonCvrefT>()) {
		//ret = NonCvrefT();
		//NonCvrefT to_move;

		if (ret.size() != bv.size()) {
			throw std::invalid_argument(sconcat(
				"liborangepower::binser::val_from_bv(): ",
				"is_std_array<NonCvrefT>(): ",
				"ret.size() != bv.size(): ",
				ret.size(), " ", bv.size()
			));
		}

		auto iter = ret.begin();

		for (size_t i=0; i<bv.size(); ++i) {
			using ValueT = typename NonCvrefT::value_type;
			ValueT temp;
			////val_from_bv(ret[i], bv.at(i), func_umap);
			//val_from_bv(temp, bv.at(i), func_umap);
			BINSER_VAL_FROM_BV_COPY_EX_STUFF_AND_CALL_VFBV(
				ValueT, temp, *iter, bv.at(i)
			);

			BINSER_VAL_FROM_BV_FINAL_INSERT_ETC(
				ValueT, temp,
				[&](const ValueT& some_temp) -> void
					{ ret.at(i) = some_temp; },
				[&](ValueT&& some_temp) -> void
					{ ret.at(i) = std::move(some_temp); }
			);
			//++iter;
			_val_from_bv_inc_iter(iter, ret.end());
		}
	} else if constexpr (
		is_vector_ex<NonCvrefT>()
		|| is_deque_ex<NonCvrefT>()
		|| is_ind_circ_link_list_ex<NonCvrefT>()
	) {
		//ret = NonCvrefT();

		//val_from_bv(ret.data, bv.at("data"), func_umap);

		//using ElemT = typename NonCvrefT::ElemT;
		//ElemT temp;
		val_from_bv(ret.data, bv, func_umap);

		// Prevent multiple O(n) computations of `ret.data.size()` when
		// `is_ind_circ_link_list_ex<NonCvrefT>()` is `true`.
		//const auto& ret_data_size = ret.data.size();
		//if (!ret.cs_is_max) {
		//	if (ret_data_size != ret.checked_size) {
		//		throw std::invalid_argument(sconcat(
		//			"liborangepower::binser::val_from_bv(): ",
		//			"is vector/deque with extras: ",
		//			"ret_data_size != ret.checked_size: ",
		//			ret_data_size, " ", ret.checked_size
		//		));
		//	}
		//} else { // if (ret.cs_is_max)
		//	if (
		//		ret_data_size < ret.min_size
		//		|| ret_data_size > ret.checked_size
		//	) {
		//		throw std::invalid_argument(sconcat(
		//			"liborangepower::binser::val_from_bv(): ",
		//			"is vector/deque with extras: ",
		//			"ret_data_size < ret.min_size ",
		//			"|| ret_data_size > ret.checked_size: ",
		//			ret_data_size, " ", ret.min_size, " ",
		//			ret.checked_size
		//		));
		//	}
		//}
		val_from_bv_test_ex_cs(
			"liborangepower::binser::val_from_bv",
			"is vector/deque with extras",
			ARG_DUP_AS_STR(ret.data.size()),
			ARG_DUP_AS_STR(ret.data),
			ARG_DUP_AS_STR(ret.checked_size),
			ARG_DUP_AS_STR(ret.cs_is_max),
			ARG_DUP_AS_STR(ret.min_size)
		);
		//#define TEST_MAP_MACRO(x) printout(x, "\n")
		//EVAL(MAP(TEST_MAP_MACRO, SEMICOLON,
		//	ret.data,
		//	ret.checked_size,
		//	ret.cs_is_max,
		//	ret.min_size));
		//#undef TEST_MAP_MACRO
	} else if constexpr (is_pseudo_vec_like_std_container<NonCvrefT>()) {
		//ret = NonCvrefT();
		NonCvrefT to_move;

		//for (size_t i=1; i<bv.size(); ++i)
		auto iter = ret.begin();

		for (size_t i=0; i<bv.size(); ++i) {
			if constexpr (is_vec_like_std_container<NonCvrefT>()) {
				using ValueT = typename NonCvrefT::value_type;
				ValueT temp;

				//val_from_bv(temp, bv.at(i), func_umap);
				BINSER_VAL_FROM_BV_COPY_EX_STUFF_AND_CALL_VFBV(
					ValueT, temp, *iter, bv.at(i)
				);

				BINSER_VAL_FROM_BV_FINAL_INSERT_ETC(
					ValueT, temp, to_move.push_back, to_move.push_back
				);
			} else // if constexpr (is_set_like_std_container<NonCvrefT>())
			{
				using KeyT = typename NonCvrefT::key_type;
				KeyT temp;

				//val_from_bv(temp, bv.at(i), func_umap);
				BINSER_VAL_FROM_BV_COPY_EX_STUFF_AND_CALL_VFBV(
					KeyT, temp, *iter, bv.at(i)
				);

				BINSER_VAL_FROM_BV_FINAL_INSERT_ETC(
					KeyT, temp, to_move.insert, to_move.insert
				);
			}
			//++iter;
			_val_from_bv_inc_iter(iter, ret.end());
		}
		ret = std::move(to_move);
	} else if constexpr (is_map_like_std_container<NonCvrefT>()) {
		//ret = NonCvrefT();
		NonCvrefT to_move;
		using KeyT = typename NonCvrefT::key_type;
		using MappedT = typename NonCvrefT::mapped_type;

		auto iter = ret.begin();

		//for (size_t i=1; i<bv.size(); ++i)
		for (size_t i=0; i<bv.size(); i+=2) {
			KeyT key;
			//val_from_bv(key, bv.at(i), func_umap);
			BINSER_VAL_FROM_BV_COPY_EX_STUFF_AND_CALL_VFBV(
				KeyT, key, iter->first, bv.at(i)
			);

			MappedT value;
			//val_from_bv(value, bv.at(i + 1), func_umap);
			BINSER_VAL_FROM_BV_COPY_EX_STUFF_AND_CALL_VFBV(
				MappedT, value, iter->second, bv.at(i + 1)
			);

			BINSER_VAL_FROM_BV_FINAL_INSERT_ETC(
				MappedT, value,
				[&](const MappedT& some_value) -> void
					{ to_move[key] = some_value; },
				[&](MappedT&& some_value) -> void
					{ to_move[key] = std::move(some_value); }
			);

			//++iter;
			_val_from_bv_inc_iter(iter, ret.end());
		}

		ret = std::move(to_move);
	}
	//--------
	else if constexpr (HasBvDeserializeFunc<NonCvrefT>) {
		ret.deserialize(bv);
	} else if constexpr (std::is_constructible<NonCvrefT, Value>()) {
		ret = NonCvrefT(bv);
	} else {
		// Assume a static member function called `from_bv` exists
		ret = NonCvrefT::from_bv(bv);
	}
	//--------
	#undef BINSER_VAL_FROM_BV_COPY_EX_STUFF_AND_CALL_VFBV
	#undef BINSER_VAL_FROM_BV_FINAL_INSERT_ETC
	//--------
}


template<typename T>
inline void val_from_bv(
	T& ret, const Value& bv, const std::nullopt_t& some_nullopt
) {
	val_from_bv<T, void>(ret, bv, nullptr);
}

template<typename T, typename BaseT>
inline void get_bv_memb(
	T& ret, const Value& bv, const std::string& name,
	FromBvFactoryFuncUmap<BaseT>* func_umap
) {
	val_from_bv(ret, bv.at(name), func_umap);
}
template<typename T>
inline void get_bv_memb(
	T& ret, const Value& bv, const std::string& name,
	const std::nullopt_t& some_nullopt
) {
	//FromBvFactoryFuncUmap<void> func_umap;
	//get_bv_memb(ret, bv, name, func_umap);
	//val_from_bv(ret, bv.at(name), std::nullopt);
	val_from_bv<T, void>(ret, bv.at(name), nullptr);
}

template<typename TempT, typename RetT, typename BaseT>
inline void get_bv_memb_w_stat_cast(
	RetT& ret, const Value& bv, const std::string& name,
	FromBvFactoryFuncUmap<BaseT>* func_umap
) {
	TempT temp;
	get_bv_memb(temp, bv, name, func_umap);
	ret = static_cast<RetT>(temp);
}
template<typename TempT, typename RetT>
inline void get_bv_memb_w_stat_cast(
	RetT& ret, const Value& bv, const std::string& name,
	const std::nullopt_t& some_nullopt
) {
	TempT temp;
	get_bv_memb(temp, bv, name, some_nullopt);
	ret = static_cast<RetT>(temp);
}

template<typename T>
inline void set_bv(Value& bv, const T& val);

template<typename T>
inline void set_bv_sptr_w_rst(ValueSptr& bv_sptr, const T& val) {
	Value bv;
	set_bv(bv, val);
	bv_sptr.reset(new Value(std::move(bv)));
}

template<MapLikeStdContnr T>
inline void set_bv_map_like_std_container(
	Value& bv, const T& val,
	const std::function<bool(const typename T::value_type&)>& skip_func
) {
	//--------
	bv = ValueDarr();
	//--------
	for (const auto& pair: val) {
		if (!skip_func(pair)) {
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
inline void set_bv_map_like_std_container(Value& bv, const T& val) {
	set_bv_map_like_std_container
		(bv, val,
		[](const typename T::value_type& pair) -> bool
			{ return false; });
}

//template<containers::MapLikeStdContnr T>
//inline void set_bv_map_like_std_container(
//	Value& bv, const T& val, const std::nullopt_t& some_nullopt
//) {
//	set_bv_map_like_std_container(bv, val, nullptr);
//}

template<typename T>
inline void set_bv(Value& bv, const T& val) {
	using NonCvrefT = std::remove_cvref_t<T>;

	bv = Value();

	//static_assert(!std::is_same<T, int64_t>()
	//	&& !std::is_same<T, uint64_t>());
	//--------
	if constexpr (std::is_same<NonCvrefT, char>()) {
		std::string temp_str;
		temp_str += val;
		bv = std::move(temp_str);
	} else if constexpr (std::is_enum<NonCvrefT>()) {
		set_bv(bv, std::underlying_type_t<NonCvrefT>(val));
	}
	//--------
	else if constexpr (is_scalar_ex<NonCvrefT>()) {
		set_bv(bv, val.data);
	}
	//--------
	else if constexpr (is_vec2<NonCvrefT>()) {
		bv = vec2_to_bv(val);
	}
	else if constexpr (is_vec3<NonCvrefT>()) {
		bv = vec3_to_bv(val);
	}
	else if constexpr (
		is_vec2_ex<NonCvrefT>()
		|| is_vec3_ex<NonCvrefT>()
		|| is_line_seg2_ex<NonCvrefT>()
		|| is_rect2_ex<NonCvrefT>()
	) {
		set_bv(bv, val.data);
	}
	else if constexpr (
		is_prev_curr_pair<NonCvrefT>()
		//|| is_move_only_prev_curr_pair<NonCvrefT>()
	) {
		ValueUmap map;

		set_bv_sptr_w_rst(map["_prev"], val.prev());
		set_bv_sptr_w_rst(map["_curr"], val.curr());

		bv = std::move(map);
	}
	//--------
	else if constexpr (
		is_std_unique_ptr_to_non_arr<NonCvrefT>()
		|| is_std_shared_ptr_to_non_arr<NonCvrefT>()
		|| is_std_weak_ptr_to_non_arr<NonCvrefT>()
	) {
		//bv = ValueUmap();
		ValueUmap map;

		//map["obj"] = *val;
		set_bv_sptr_w_rst(map["obj"], *val);
		using ElemT = typename NonCvrefT::element_type;
		//if constexpr (concepts::HasStaticKindStr<T>) {
		//	map["has_kind_str"] = true;
		//	map["kind_str"] = T::KIND_STR;
		//} else
		if constexpr (concepts::HasKindStrMbrFunc<ElemT>) {
			//map["has_kind_str"] = true;
			//map["kind_str"] = ValueSptr(new Value(val->kind_str()));
			map["kind_str"] = Value::to_sptr(val->kind_str());
		}
		//else {
		//	map["has_kind_str"] = false;
		//}
		bv = std::move(map);
	}
	else if constexpr (
		is_vector_ex<NonCvrefT>()
		|| is_deque_ex<NonCvrefT>()
		|| is_ind_circ_link_list_ex<NonCvrefT>()
	) {
		set_bv(bv, val.data);
	}
	else if constexpr (
		is_arr_like_std_container<NonCvrefT>()
		|| is_ind_circ_link_list<NonCvrefT>()
	) {
		ValueDarr vec;

		for (const auto& item: val) {
			Value inner_bv;
			set_bv(inner_bv, item);
			vec.push_back(Value::to_sptr(std::move(inner_bv)));
		}
		bv = std::move(vec);
	} else if constexpr (is_set_like_std_container<NonCvrefT>()) {
		ValueDarr vec;

		for (const auto& key: val) {
			Value inner_bv = ValueUmap();
			set_bv(inner_bv, key);
			vec.push_back(Value::to_sptr(std::move(inner_bv)));
		}
		bv = std::move(vec);
	} else if constexpr (is_map_like_std_container<NonCvrefT>()) {
		set_bv_map_like_std_container(bv, val);
	}
	//--------
	else {
		bv = val;
	}
	//--------
}

template<typename T>
inline void set_bv_memb(Value& bv, const std::string& name, const T& val) {
	//--------
	//if constexpr (
	//	std::is_same<T, int>()
	//	|| std::is_same<T, uint>()
	//	|| std::is_same<T, float>()
	//	|| std::is_same<T, double>()
	//)
	//if constexpr (
	//	std::is_same<T, int64_t>()
	//	|| std::is_same<T, uint64_t>()
	//) {
	//	bv[sconcat(name, ".high")] 
	//		= uint32_t(uint64_t(val)
	//			>> uint64_t(32u));
	//	bv[sconcat(name, ".low")]
	//		= uint32_t(uint64_t(val)
	//			& uint64_t(0xffffffffu));
	//} else {
	//	set_bv(bv[name], val);
	//}

	Value temp;
	set_bv(temp, val);
	bv.insert(name, std::move(temp));
}

inline void parse_binser(std::istream& is, binser::Value& root) {
	std::vector<char> vec;
	while (!is.eof()) {
		vec.push_back(is.get());
	}
	root = vec;
}
inline bool parse_binser(
	const std::string& input_file_name, binser::Value& root
) {
	if (
		auto file=std::fstream(input_file_name,
			std::ios_base::in | std::ios_base::binary);
		file.is_open()
	) {
		parse_binser(file, root);
		return true;
	} else {
		return false;
	}
}

inline void write_binser(std::ostream& os, const binser::Value& root) {
	const auto& ser_darr = std::vector<char>(root);
	for (const auto& c: ser_darr) {
		os.put(c);
	}
}
inline bool write_binser(
	const std::string& output_file_name, const binser::Value& root
) {
	if (
		auto file=std::fstream(output_file_name,
			std::ios_base::out | std::ios_base::binary);
		file.is_open()
	) {
		write_binser(file, root);
		return true;
	} else {
		return false;
	}
}

//class BlankValue final {
//public:		// functions
//	constexpr inline BlankValue() = default;
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(BlankValue);
//	constexpr inline BlankValue(const Value& bv) {
//	}
//
//	inline operator Value () const {
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
