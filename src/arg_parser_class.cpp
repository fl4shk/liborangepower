#include "arg_parser_class.hpp"

namespace liborangepower {
//--------
using strings::sconcat;
//--------
namespace arg_parse {
//--------
ArgParser::ArgParser() {}
ArgParser::~ArgParser() {}

//ArgParser& ArgParser::add(Option&& to_add)
ArgParser& ArgParser::add(
	std::string&& s_name, std::optional<std::string>&& s_alt_name,
	HasArg s_has_arg, bool s_req_opt, bool s_singleton
) {
	switch (s_has_arg) {
	//--------
	case HasArg::None:
	case HasArg::Req:
	case HasArg::Opt:
		break;
	default:
		throw std::invalid_argument(sconcat
			("liborangepower::arg_parse::ArgParser::add(): ",
			"Error: invalid `s_has_arg`"));
		break;
	//--------
	}
	OptionKey to_insert
		{.name=std::move(s_name),
		.alt_name=std::move(s_alt_name),
		.has_arg=s_has_arg,
		.req_opt=s_req_opt,
		.singleton=s_singleton};

	if (to_insert.alt_name) {
		if (alt_name_to_name_umap().contains(*to_insert.alt_name)) {
			throw std::invalid_argument(sconcat
				("liborangepower::arg_parse::ArgParser::add(): ",
				"Error: already have `alt_name` of ",
				"\"", *to_insert.alt_name, "\""));
		}
		_alt_name_to_name_umap.insert(std::pair
			(*to_insert.alt_name, to_insert.name));
	}

	std::string temp_name(to_insert.name);

	//_option_umap.insert(std::pair(std::move(name), std::move(to_add)));
	_option_key_umap.insert(std::pair
		(std::move(temp_name), std::move(to_insert)));
	return *this;
}
//ArgParser& ArgParser::add(std::vector<Option>&& to_add_vec) {
//	for (auto& to_add: to_add_vec) {
//		add(std::move(to_add));
//	}
//	return *this;
//}
ArgParseRet ArgParser::parse(
	int argc, char** argv
) {
	_option_darr.clear();
	for (int i=1; i<argc; ++i) {
		if (contains(argv[i])) {
			OptionKey& key = _raw_key_at(argv[i]);
			if (key.singleton && key.ind_darr.size() >= 1) {
				return ArgParseRet
					{.index=i,
					.kind=ArgParseRet::Kind::TooManyInsts};
			}

			Option option;
			if (alt_name_to_name_umap().contains(key.name)) {
				option.name = alt_name_to_name_umap().at(key.name);
			} else {
				option.name = key.name;
			}

			switch (key.has_arg) {
			//--------
			case HasArg::None:
				option.val = std::string();
				break;
			case HasArg::Req:
				{
					if (i + 1 == argc) {
						return ArgParseRet
							{.index=i,
							.kind=ArgParseRet::Kind::MissingArg};
					} else if (contains(argv[i + 1])) {
						return ArgParseRet
							{.index=i,
							.kind=ArgParseRet::Kind::ArgIsOption};
					} else {
						option.val = argv[i + 1];
						++i;
					}
				}
				break;
			case HasArg::Opt:
				{
					if (
						i + 1 == argc
						|| contains(argv[i + 1])
					) {
						option.val = std::string();
					} else {
						option.val = argv[i + 1];
						++i;
					}
				}
				break;
			//--------
			}
			key.ind_darr.push_back(option_darr().size());
			_option_darr.push_back(std::move(option));
		} else {
			//return ArgParseRet
			//	{.index=i,
			//	.kind=ArgParseRet::Kind::NoOption};
			return ArgParseRet
				{.index=i,
				.kind=ArgParseRet::Kind::NoFail};
		}
	}
	if (ArgParseRet ret; true) { 
		ret.kind = ArgParseRet::Kind::MissingReqOpt;
		for (const auto& item: option_key_umap()) {
			if (item.second.req_opt && !item.second.is_active()) {
				ret.missing_req_uset.insert(item.second.name);
			}
		}
		if (ret.missing_req_uset.size() > 0) {
			return ret;
		}
	}
	return ArgParseRet
		{.index=argc,
		.kind=ArgParseRet::Kind::NoFail};
}

std::string ArgParser::help_msg(int argc, char** argv) const {
	std::string ret;
	ret += sconcat(argv[0], " valid options:\n");

	for (const auto& item: option_key_umap()) {
		const auto& key = item.second;
		ret += key.name;
		if (key.alt_name) {
			ret += sconcat(" (short name ", *key.alt_name, ")");
		}
		ret += ": ";

		switch (key.has_arg) {
		//--------
		case HasArg::None:
			ret += "takes no arguments; ";
			break;
		case HasArg::Req:
			ret += "requires an argument; ";
			break;
		case HasArg::Opt:
			ret += "optionaly takes an argument; ";
			break;
		default:
			throw std::runtime_error(sconcat
				("liborangepower::arg_parse::ArgParser::help_msg(): ",
				"Error: ",
				"Unknown `key.has_arg` (", size_t(key.has_arg), ")"));
			break;
		//--------
		}
		//const u32 flags
		//	= (u32(key.req_opt) << u32(1))
		//	|| u32(key.singleton);
		//if (key.req_opt) {
		//	ret += "; is a required option;.";
		//} else {
		//	ret += ".";
		//}
		if (key.req_opt || key.singleton) {
			//ret += "(Notes: ";
			if (key.req_opt) {
				ret += "required option; ";
				//if (key.singleton) {
				//	ret += "; "
				//}
			}
			if (key.singleton) {
				ret += "this argument can only appear once; ";
			}
			//ret += ")";
		}
		ret += "\n";
	}

	return ret;
}
//--------
} // namespace arg_parse
} // namespace liborangepower
