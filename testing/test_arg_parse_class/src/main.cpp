#include "misc_includes.hpp"

int main(int argc, char** argv) {
	ArgParser ap;
	ap.add("--compile", std::nullopt, HasArg::None, false);
	ap.add("--debug", "-d", HasArg::None, false);
	ap.add("--flags", "-f", HasArg::Req, false);
	ap.add("--build", "-b", HasArg::Opt, false);

	if (const auto& ap_ret=ap.parse(argc, argv); ap_ret.fail()) {
		printerr("Bad argument ", ap_ret.index, " ",
			"\"", argv[ap_ret.index], "\" ",
			static_cast<i32>(ap_ret.kind),
			"\n");
	}

	return 0;
}
