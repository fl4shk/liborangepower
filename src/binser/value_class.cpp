#include "value_class.hpp"

namespace liborangepower {

using strings::sconcat;
using namespace misc_output;

namespace binser {
//--------
void Value::_inner_init(const std::vector<char>& to_cast, u64& i) {
	//--------
	//if (i == 0) {
	//	printout("<BEGIN>\n");
	//	osprint_hexdump(std::cout, to_cast, 20);
	//	printout("<END>\n\n");
	//}
	//--------
	if (i >= to_cast.size()) {
		throw std::invalid_argument(sconcat(
			"Value::_inner_init(): i >= to_cast.size() - 1: ",
			i, " ", to_cast.size(), "."
		));
	}
	const Tag& tag = static_cast<Tag>(to_cast.at(i));
	++i;
	//--------
	//auto do_memcpy
	//	= [&to_cast, &i, &tag]<typename T>() -> T {
	//	T temp_ret;

	//	if (i + sizeof(T) >= to_cast.size()) {
	//		throw std::invalid_argument(sconcat(
	//			"Value::_inner_init(): ",
	//			"do_memcpy(): i + sizeof(T) >= to_cast.size(): ",
	//			static_cast<int>(tag), " ", i, " ", sizeof(T), " ",
	//			to_cast.size(), "."
	//		));
	//	}

	//	std::memcpy(&temp_ret, to_cast.data() + i, sizeof(T));
	//	i += sizeof(T);

	//	return temp_ret;
	//};
	//--------
	auto get_str
		= [this, &to_cast, &i, &tag]() -> std::string {
		const auto old_i = i;
		const u64 str_size = _inner_init_do_memcpy<u64>(to_cast, i, tag);

		std::string temp_ret;

		if (old_i + str_size >= to_cast.size()) {
			throw std::invalid_argument(sconcat(
				"Value::_inner_init(): ",
				"get_str(): old_i + size >= to_cast.size(): ",
				old_i, " ", str_size, " ", to_cast.size(), "."
			));
		}

		for (u64 j=0; j<str_size; ++j) {
			temp_ret += to_cast.at(i);
			++i;
		}

		return temp_ret;
	};
	//--------
	switch (tag) {
	//--------
	case Tag::Null:
		*this = std::monostate();
		break;
	case Tag::UInt8:
		*this = _inner_init_do_memcpy<u8>(to_cast, i, tag);
		break;
	case Tag::Int8:
		*this = _inner_init_do_memcpy<i8>(to_cast, i, tag);
		break;
	case Tag::UInt16:
		*this = _inner_init_do_memcpy<u16>(to_cast, i, tag);
		break;
	case Tag::Int16:
		*this = _inner_init_do_memcpy<i16>(to_cast, i, tag);
		break;
	case Tag::UInt32:
		*this = _inner_init_do_memcpy<u32>(to_cast, i, tag);
		break;
	case Tag::Int32:
		*this = _inner_init_do_memcpy<i32>(to_cast, i, tag);
		break;
	case Tag::UInt64:
		*this = _inner_init_do_memcpy<u64>(to_cast, i, tag);
		break;
	case Tag::Int64:
		*this = _inner_init_do_memcpy<i64>(to_cast, i, tag);
		break;
	case Tag::Float:
		*this = _inner_init_do_memcpy<float>(to_cast, i, tag);
		break;
	case Tag::Double:
		*this = _inner_init_do_memcpy<double>(to_cast, i, tag);
		break;
	case Tag::Bool:
		*this = _inner_init_do_memcpy<bool>(to_cast, i, tag);
		break;
	case Tag::Str:
		*this = get_str();
		break;
	case Tag::Vec: {
		const u64 vec_size = _inner_init_do_memcpy<u64>(to_cast, i, tag);

		ValueVec n_data;

		for (u64 j=0; j<vec_size; ++j) {
			//Value temp;
			//temp._inner_init(to_cast, i);
			//n_data.push_back(std::move(temp));

			Value to_push;
			to_push._inner_init(to_cast, i);
			n_data.push_back(
				ValueSptr(new Value(std::move(to_push)))
			);
		}

		*this = std::move(n_data);
	}
		break;
	case Tag::Map: {
		const u64 map_size = _inner_init_do_memcpy<u64>(to_cast, i, tag);

		ValueMap n_data;

		for (u64 j=0; j<map_size; ++j) {
			const std::string& temp_str = get_str();

			Value to_insert;
			to_insert._inner_init(to_cast, i);

			n_data.insert(typename ValueMap::value_type(
				temp_str, ValueSptr(new Value(std::move(to_insert)))
			));
		}

		*this = std::move(n_data);
	}
		break;
	default:
		throw std::invalid_argument(sconcat(
			"Value::_inner_init(): ",
			" Unknown `Tag` ", static_cast<int>(tag), " at index ", i,
			"."
		));
		break;
	//--------
	}
}

Value::operator std::vector<char> () const {
	std::vector<char> ret;

	auto do_memcpy
		= [this, &ret]<typename T>(T& value) -> void {
		const auto OLD_SIZE = ret.size();

		//for (size_t i=0; i<sizeof(T); ++i) {
		//	ret.push_back(0u);
		//}

		ret.resize(ret.size() + sizeof(T));

		std::memcpy(ret.data() + OLD_SIZE, &value, sizeof(T));
	};

	if (holds_alternative<std::monostate>()) {
		ret.push_back(static_cast<char>(Tag::Null));
	} else if (holds_alternative<u8>()) {
		ret.push_back(static_cast<char>(Tag::UInt8));
		do_memcpy(get<u8>());
	} else if (holds_alternative<i8>()) {
		ret.push_back(static_cast<char>(Tag::Int8));
		do_memcpy(get<i8>());
	} else if (holds_alternative<u16>()) {
		ret.push_back(static_cast<char>(Tag::UInt16));
		do_memcpy(get<u16>());
	} else if (holds_alternative<i16>()) {
		ret.push_back(static_cast<char>(Tag::Int16));
		do_memcpy(get<i16>());
	} else if (holds_alternative<u32>()) {
		ret.push_back(static_cast<char>(Tag::UInt32));
		do_memcpy(get<u32>());
	} else if (holds_alternative<i32>()) {
		ret.push_back(static_cast<char>(Tag::Int32));
		do_memcpy(get<i32>());
	} else if (holds_alternative<u64>()) {
		ret.push_back(static_cast<char>(Tag::UInt64));
		do_memcpy(get<u64>());
	} else if (holds_alternative<i64>()) {
		ret.push_back(static_cast<char>(Tag::Int64));
		do_memcpy(get<i64>());
	} else if (holds_alternative<float>()) {
		ret.push_back(static_cast<char>(Tag::Float));
		do_memcpy(get<float>());
	} else if (holds_alternative<double>()) {
		ret.push_back(static_cast<char>(Tag::Double));
		do_memcpy(get<double>());
	} else if (holds_alternative<bool>()) {
		ret.push_back(static_cast<char>(Tag::Bool));
		do_memcpy(get<bool>());
	} else if (holds_alternative<std::string>()) {
		ret.push_back(static_cast<char>(Tag::Str));

		const auto& str = get<std::string>();

		if (u64 size=str.size(); true) {
			do_memcpy(size);
		}

		for (const auto& c: str) {
			ret.push_back(c);
		}
	} else if (holds_alternative<ValueVec>()) {
		ret.push_back(static_cast<char>(Tag::Vec));

		const auto& vec = get<ValueVec>();

		if (u64 vec_size=vec.size(); true) {
			do_memcpy(vec_size);
		}

		for (auto& item: vec) {
			//ret.push_back(static_cast<std::vector<char>>(item));
			const std::vector<char>& temp_vec
				= static_cast<std::vector<char>>(*item);
			ret.insert(ret.end(), temp_vec.cbegin(), temp_vec.cend());
		}
	} else { // if (holds_alternative<ValueMap>())
		ret.push_back(static_cast<char>(Tag::Map));

		const auto& map = get<ValueMap>();

		if (u64 size=map.size(); true) {
			do_memcpy(size);
		}

		for (const auto& item: map) {
			// Copy the `std::string` first
			if (u64 size=item.first.size(); true) {
				do_memcpy(size);
			}
			for (const auto& c: item.first) {
				ret.push_back(c);
			}

			// Then copy the casted-to-`std::vector<char>` form of the
			// contained `binser::Value`.
			const std::vector<char> temp_vec(
				static_cast<std::vector<char>>(*item.second)
			);
			ret.insert(ret.end(), temp_vec.cbegin(), temp_vec.cend());
		}
	}

	return ret;
}

size_t Value::size() const {
	if (holds_alternative<ValueVec>()) {
		return get<ValueVec>().size();
	} else if (holds_alternative<ValueMap>()) {
		return get<ValueMap>().size();
	} else {
		throw std::runtime_error(sconcat(
			"Wrong type held by the `binser::Value`. ",
			"It must be `binser::ValueVec` or `binser::ValueMap`."
		));
	}
}
//--------
} // namespace binser
} // namespace liborangepower
