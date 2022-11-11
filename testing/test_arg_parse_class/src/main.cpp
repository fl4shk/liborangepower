#include "misc_includes.hpp"

int main(int argc, char** argv) {
	ArgParser ap;
	ap.add("--compile", std::nullopt, HasArg::None, false);
	ap.add("--debug", "-d", HasArg::None, false);
	ap.add("--flags", "-f", HasArg::Req, false);
	//ap.add("--build", "-b", HasArg::Opt, false);
	ap.add("--build", "-b", HasArg::Req, false);

	const auto& ap_ret=ap.parse(argc, argv);
	if (ap_ret.fail()) {
		//printerr("Bad argument ", ap_ret.index, " ",
		//	"\"", argv[ap_ret.index], "\" ",
		//	static_cast<i32>(ap_ret.kind),
		//	"\n");
		printerr(ap.help_msg(argc, argv), "\n");
	}

	return 0;
}
