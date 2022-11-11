#ifndef liborangepower_arg_parser_class_hpp
#define liborangepower_arg_parser_class_hpp

#include "misc/misc_types.hpp"
#include "misc/misc_includes.hpp"
#include "misc/misc_output_funcs.hpp"
#include "gen_class_innards_defines.hpp"
#include "strings/sconcat_etc.hpp"
//#include <ctype.h>

namespace liborangepower {
//--------
using integer_types::u8;
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

class Option final {
public:		// variables
	std::string name;
	std::optional<std::string> alt_name;
	HasArg has_arg = HasArg::None;
	bool
		req_opt = false;

	// This has a value of `std::nullopt` when the option was not
	// triggered, or an `std::string` when the option *was* triggered.
	//
	// For `has_arg == HasArg::None`, if `this` is enabled, then `val` will
	// be set to `std::string()`.
	//
	// For `has_arg == HasArg::Req`, if `this` is enabled, then `val` will
	// be set to the argument.
	//
	// For `has_arg == HasArg::Opt`, if `this` is enabled, then `val` will
	// be set to `std::string()` if there was no argument, or to the
	// argument if there was one.
	std::optional<std::string> val = std::nullopt;
public:		// functions
	constexpr inline auto operator <=> (
		const Option& to_cmp
	) const = default;
	constexpr inline bool is_active() const {
		return static_cast<bool>(val);
	}

	//constexpr inline bool has_alt_name() const {
	//	return (alt_name.size() > 0);
	//}
	//constexpr inline bool has_val() const {
	//	//return (val.size() > 0);
	//	return static_cast<bool>(val);
	//}
};

class ArgParseRet final {
public:		// types
	enum class Kind: u8 {
		NoFail, // No fail
		//NoOption, // if an `Option` was *NOT* found at `argv[index]`
		MissingArg, // if we arg missing an argument to the `Option`
		ArgIsOption, // if the argument was an `Option`
		MissingReqOpt, // if the `Option` was missing, but we don't have it
	};
public:		// variables
	// Index into `argv`.
	// For `!(*this)`, it's the index of the first element of `argv` that
	// was 
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
private:		// variables
	//int _argc = 0;
	//char** _argv = nullptr;

	// This uses the `name`s of the `Option`s as the keys because
	// `name` is expected to always exist
	std::unordered_map<std::string, Option> _option_umap;
	// This maps short names to long names
	std::unordered_map<std::string, std::string> _alt_name_to_name_umap;
public:		// functions
	ArgParser();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ArgParser);
	~ArgParser();

	//ArgParser& add(Option&& to_add);
	ArgParser& add(
		std::string&& s_name, std::optional<std::string>&& s_alt_name,
		HasArg s_has_arg, bool s_req_opt
	);
	//inline ArgParser& add(const std::string& s_name, HasArg s_has_arg) {
	//	return add(s_name, std::string(), s_has_arg);
	//}
	//ArgParser& add(std::vector<Option>&& to_add_vec);

public:		// types
public:		// functions
	ArgParseRet parse(int argc, char** argv);
private:		// functions
	inline Option& _raw_at(const std::string& alt_name_or_name) {
		if (_alt_name_to_name_umap.contains(alt_name_or_name)) {
			return _option_umap.at(_alt_name_to_name_umap
				.at(alt_name_or_name));
		} else if (_option_umap.contains(alt_name_or_name)) {
			return _option_umap.at(alt_name_or_name);
		} else {
			throw std::invalid_argument(sconcat
				("liborangepower::arg_parse::ArgParser::_raw_at(): ",
				"Error: invalid `alt_name_or_name` of ",
				alt_name_or_name));
		}
	}
public:		// functions
	inline const Option& at(const std::string& alt_name_or_name) const {
		if (_alt_name_to_name_umap.contains(alt_name_or_name)) {
			return _option_umap.at(_alt_name_to_name_umap
				.at(alt_name_or_name));
		} else if (_option_umap.contains(alt_name_or_name)) {
			return _option_umap.at(alt_name_or_name);
		} else {
			throw std::invalid_argument(sconcat
				("liborangepower::arg_parse::ArgParser::at(): ",
				"Error: invalid `alt_name_or_name` of ",
				alt_name_or_name));
		}
	}
	inline bool contains(const std::string& alt_name_or_name) const {
		return
			(_alt_name_to_name_umap.contains(alt_name_or_name)
			|| _option_umap.contains(alt_name_or_name));
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

		bool ret = at(first_name).is_active();
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
			ret = ret && at(item).is_active();
		}
		return ret;
	}
	//inline std::optional<std::string> err_msg_when_missing_args(
	//) const {
	//}

	GEN_GETTER_BY_CON_REF(option_umap);
};
//--------
} // namespace arg_parse
} // namespace liborangepower

#endif		// liborangepower_arg_parser_class_hpp
