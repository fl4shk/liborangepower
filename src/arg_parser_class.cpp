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
	HasArg s_has_arg, bool s_req_opt
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
	Option to_insert
		{.name=std::move(s_name),
		.alt_name=std::move(s_alt_name),
		.has_arg=s_has_arg,
		.req_opt=s_req_opt};

	if (to_insert.alt_name) {
		if (_alt_name_to_name_umap.contains(*to_insert.alt_name)) {
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
	_option_umap.insert(std::pair
		(std::move(temp_name), std::move(to_insert)));
	return *this;
}
//ArgParser& ArgParser::add(std::vector<Option>&& to_add_vec) {
//	for (auto& to_add: to_add_vec) {
//		add(std::move(to_add));
//	}
//	return *this;
//}
auto ArgParser::parse(int argc, char** argv) -> std::optional<Fail> {
	for (int i=1; i<argc; ++i) {
		if (contains(argv[i])) {
			auto& option = _raw_at(argv[i]);

			switch (option.has_arg) {
			//--------
			case HasArg::None:
				option.val = std::string();
				break;
			case HasArg::Req:
				{
					if (i + 1 == argc) {
						return Fail
							{.index=i,
							.kind=FailKind::MissingArg};
					} else if (contains(argv[i + 1])) {
						return Fail
							{.index=i,
							.kind=FailKind::ArgIsOption};
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
		} else {
			return Fail
				{.index=i,
				.kind=FailKind::NoOption};
		}
	}
	if (Fail fail; true) { 
		fail.kind = FailKind::MissingReqOpt;
		for (const auto& item: option_umap()) {
			if (item.second.req_opt && !item.second.val) {
				fail.missing_req_uset.insert(item.second.name);
			}
		}
		if (fail.missing_req_uset.size() > 0) {
			return fail;
		}
	}
	return std::nullopt;
}
//--------
} // namespace arg_parse
} // namespace liborangepower
