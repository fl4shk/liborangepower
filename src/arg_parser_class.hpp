#ifndef liborangepower_arg_parser_class_hpp
#define liborangepower_arg_parser_class_hpp

#include "misc/misc_types.hpp"
#include "misc/misc_includes.hpp"
#include "misc/misc_output_funcs.hpp"
#include "gen_class_innards_defines.hpp"
#include "strings/sconcat_etc.hpp"
#include "containers/std_hash_stuff.hpp"
//#include <ctype.h>

namespace liborangepower {
//--------
using integer_types::u8;
using integer_types::u16;
using integer_types::u32;
using integer_types::u64;
using strings::sconcat;
//--------
namespace arg_parse {
//--------
// old code here
//class OptArg final {
//private:		// variables
//	std::string _opt, _val;
//	bool _valid = true;
//public:		// functions
//	inline OptArg() {
//	}
//	inline OptArg(
//		const std::string& to_parse, size_t num_prefixes=2,
//		char prefix='-'
//	) {
//		bool left = true;
//
//		for (const auto& c: to_parse) {
//			if (left) {
//				if (_opt.size() < num_prefixes) {
//					if (c == prefix) {
//						_opt += c;
//					} else { // if (c != prefix)
//						_valid = false;
//						break;
//					}
//				} else { // if (_opt.size() >= num_prefixes)
//					if (isalnum(c) || (c == '_')) {
//						_opt += c;
//					} else {
//						if (
//							_opt.size() < (num_prefixes + 1)
//							|| c != '='
//						) {
//							_valid = false;
//							break;
//						} else {
//							left = false;
//						}
//					}
//				}
//			} else { // if (!left)
//				_val += c;
//			}
//		}
//
//		if (_opt.size() < (num_prefixes + 1)) {
//			_valid = false;
//		}
//	}
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(OptArg);
//	inline ~OptArg() = default;
//
//	inline std::string errwarn_msg_dup() const {
//		return strings::sconcat("Duplicate \"", opt(), "\" option.");
//	}
//	inline std::string errwarn_msg_has_val() const {
//		return strings::sconcat("Option \"", opt(),
//			"\" takes no value.");
//	}
//	inline std::string errwarn_msg_no_val() const {
//		return strings::sconcat("Option \"", opt(),
//			"\" requires a value.");
//	}
//
//	GEN_GETTER_BY_CON_REF(opt);
//	GEN_GETTER_BY_CON_REF(val);
//	GEN_GETTER_BY_VAL(valid);
//};

enum class HasArg {
	None,	// doesn't take an argument
	Req,	// required argument
	Opt,	// optional argument
};
class OptionKey final {
public:		// variables
	std::string name;
	std::optional<std::string> alt_name;
	HasArg has_arg = HasArg::None;
	std::vector<size_t> ind_darr;
	bool
		req_opt: 1 = false,
		singleton: 1 = true;
public:		// functions
	constexpr inline auto operator <=> (
		const OptionKey& to_cmp
	) const = default;
	constexpr inline bool is_active() const {
		//return static_cast<bool>(val);
		//return (val.size() > size_t(0));
		return (ind_darr.size() > size_t(0));
	}
	//constexpr inline bool has_alt_name() const {
	//	return (alt_name.size() > 0);
	//}
	//constexpr inline bool has_val() const {
	//	//return (val.size() > 0);
	//	return static_cast<bool>(val);
	//}
};

class Option final {
public:		// variables
	//--------
	std::string name; // long name
	//--------
	// old `val` notes start
	// `val` has a value of `std::nullopt` when the option was not
	// triggered, or an `std::string` when the option *was* triggered.
	//
	// For `has_arg == HasArg::None`, if `this` is enabled, then
	// `val.first` will be set to `std::string()`.
	//
	// For `has_arg == HasArg::Req`, if `this` is enabled, then `val.first`
	// will be set to the argument.
	//
	// For `has_arg == HasArg::Opt`, if `this` is enabled, then `val.first`
	// will be set to `std::string()` if there was no argument, or to the
	// argument if there was one.
	//std::optional<std::string> val = std::nullopt;
	// old `val` notes end
	//--------
	std::string val;
	//--------
public:		// functions
	constexpr inline auto operator <=> (
		const Option& to_cmp
	) const = default;
	//constexpr inline bool is_active() const {
	//	return static_cast<bool>(val);
	//	//return (val.size() > size_t(0));
	//}
};
//--------
} // namespace arg_parse
} // namespace liborangepower
namespace std {
//--------
template<>
struct hash<liborangepower::arg_parse::OptionKey> {
	std::size_t operator () (
		const liborangepower::arg_parse::OptionKey& option_key
	) const noexcept {
		return liborangepower::containers::hash_va(option_key.name);
	}
};
//--------
template<>
struct hash<liborangepower::arg_parse::Option> {
	std::size_t operator () (
		const liborangepower::arg_parse::Option& option
	) const noexcept {
		return liborangepower::containers::hash_va(option.name);
	}
};
//--------
} // namespace std
//--------
namespace liborangepower {
namespace arg_parse {
//--------
class ArgParseRet final {
public:		// types
	enum class Kind: u8 {
		NoFail,			// there is no fail, so `index` indicate
		//NoOption,		// if an option was *NOT* found at `argv[index]`
		MissingArg,		// if we arg missing an argument to the option
		ArgIsOption,	// if the argument was an option
		MissingReqOpt,	// if the option was required, but we don't have it
		TooManyInsts,	// if the option is a singleton, but it was
						// triggered more than once
	};
public:		// variables
	// Index into `argv`.
	//
	// For `!fail()`, this is equal to either `argc` (only if all of `argv`
	// mapped to particular `Option`s), or the index of the first element
	// of `argv` that was found to not map to a particular `OptionKey`.
	//
	// For `fail()`, this is equal to the index of the element that failed
	// to be parsed properly.
	int index = 0;

	Kind kind = Kind::NoFail;
	std::unordered_set<std::string> missing_req_uset;
public:		// functions
	constexpr inline bool fail() const {
		return (kind != Kind::NoFail);
	}
	//inline operator bool () const {
	//	return (kind != Kind::NoFail);
	//}
};

class ArgParser final {
public:		// types
	//using IndPair = std::pair<size_t, size_t>;
	//class IndPair final {
	//public:		// variables
	//	size_t
	//		argv_ind = 0, // index into `argv`
	//		oval_ind = 0, // index into `my_option.val`
	//};
private:		// variables
	//int _argc = 0;
	//char** _argv = nullptr;

	// This uses the `name`s of the `Option`s as the keys because
	// `name` is expected to always exist
	std::unordered_map<std::string, OptionKey> _option_key_umap;
	std::vector<Option> _option_darr;
	// This maps alt names to names
	std::unordered_map<std::string, std::string> _alt_name_to_name_umap;
public:		// functions
	ArgParser();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ArgParser);
	~ArgParser();

	//ArgParser& add(Option&& to_add);
	ArgParser& add(
		std::string&& s_name, std::optional<std::string>&& s_alt_name,
		HasArg s_has_arg, bool s_req_opt, bool s_singleton
	);
	inline ArgParser& add_singleton(
		std::string&& s_name, std::optional<std::string>&& s_alt_name,
		HasArg s_has_arg, bool s_req_opt
	) {
		return add
			(std::move(s_name), std::move(s_alt_name),
			s_has_arg,
			s_req_opt, true);
	}
	//inline ArgParser& add(const std::string& s_name, HasArg s_has_arg) {
	//	return add(s_name, std::string(), s_has_arg);
	//}
	//ArgParser& add(std::vector<Option>&& to_add_vec);

public:		// types
public:		// functions
	ArgParseRet parse(int argc, char** argv);
private:		// functions
	inline OptionKey& _raw_key_at(
		const std::string& alt_name_or_name
	) {
		if (_alt_name_to_name_umap.contains(alt_name_or_name)) {
			//return _option_umap.at(_alt_name_to_name_umap
			//	.at(alt_name_or_name));
			return _option_key_umap.at(_alt_name_to_name_umap
				.at(alt_name_or_name));
		} else if (_option_key_umap.contains(alt_name_or_name)) {
			//return _option_umap.at(alt_name_or_name);
			return _option_key_umap.at(alt_name_or_name);
		} else {
			throw std::invalid_argument(sconcat
				("liborangepower::arg_parse::ArgParser::_raw_key_at(): ",
				"Error: invalid `alt_name_or_name` of ",
				alt_name_or_name));
		}
	}
	inline Option& _raw_at(
		const OptionKey& key, size_t index
	) {
		if (index < key.ind_darr.size() - size_t(1)) {
			return _option_darr.at(key.ind_darr.at(index));
		} else {
			throw std::out_of_range(sconcat
				("liborangepower::arg_parse::ArgParser::_raw_at(): ",
				"Error: ",
				"`index` (", index, ") out of range for `key.ind_darr`. ",
				"`key.ind_darr.size() == ", key.ind_darr.size(), "`."));
		}
	}
	inline Option& _raw_at(
		const std::string& alt_name_or_name, size_t index
	) {
		return _raw_at(key_at(alt_name_or_name), index);
	}
public:		// functions
	inline const OptionKey& key_at(
		const std::string& alt_name_or_name
	) const {
		if (alt_name_to_name_umap().contains(alt_name_or_name)) {
			//return _option_umap.at(_alt_name_to_name_umap
			//	.at(alt_name_or_name));
			return option_key_umap().at(_alt_name_to_name_umap
				.at(alt_name_or_name));
		} else if (option_key_umap().contains(alt_name_or_name)) {
			//return _option_umap.at(alt_name_or_name);
			return option_key_umap().at(alt_name_or_name);
		} else {
			throw std::invalid_argument(sconcat
				("liborangepower::arg_parse::ArgParser::key_at(): ",
				"Error: invalid `alt_name_or_name` of ",
				alt_name_or_name));
		}
	}
	inline const Option& at(
		const OptionKey& key, size_t index
	) const {
		if (index < key.ind_darr.size() - size_t(1)) {
			return option_darr().at(key.ind_darr.at(index));
		} else {
			throw std::out_of_range(sconcat
				("liborangepower::arg_parse::ArgParser::at(): Error: ",
				"`index` (", index, ") out of range for `key.ind_darr`. ",
				"`key.ind_darr.size() == ", key.ind_darr.size(), "`."));
		}
	}
	inline const Option& at(
		const std::string& alt_name_or_name, size_t index
	) const {
		return at(key_at(alt_name_or_name), index);
	}
	inline bool contains(const std::string& alt_name_or_name) const {
		return
			(alt_name_to_name_umap().contains(alt_name_or_name)
			|| option_key_umap().contains(alt_name_or_name));
	}

	constexpr inline bool has_opts() {
		return false;
	}

	template<typename... RemTs>
	inline bool has_opts(
		const std::string& first_name,
		const RemTs&... rem_names
	) const {
		//if constexpr (sizeof...(names) == 0) {
		//	return false;
		//}

		bool ret = key_at(first_name).is_active();
		//((ret = ret && at(rem_names).is_active()), ...);
		if constexpr (sizeof...(rem_names) > 0) {
			ret = ret && has_opts(rem_names...);
		}
		return ret;
	}

	inline bool has_opts(
		const std::vector<std::string>& name_vec
	) const {
		if (name_vec.size() == 0) {
			return false;
		}

		bool ret = true;
		for (const auto& item: name_vec) {
			ret = ret && key_at(item).is_active();
		}
		return ret;
	}
	//inline std::optional<std::string> err_msg_when_missing_args(
	//) const {
	//}
	std::string help_msg(int argc, char** argv) const;

	GEN_GETTER_BY_CON_REF(option_key_umap);
	GEN_GETTER_BY_CON_REF(option_darr);
	GEN_GETTER_BY_CON_REF(alt_name_to_name_umap);
};
//--------
} // namespace arg_parse
} // namespace liborangepower

#endif		// liborangepower_arg_parser_class_hpp
