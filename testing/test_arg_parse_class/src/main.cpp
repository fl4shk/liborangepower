#include "misc_includes.hpp"

int main(int argc, char** argv) {
	ArgParser ap;
	ap.add("--compile", std::nullopt, HasArg::None, false, true);
	ap.add("--debug", "-d", HasArg::None, false, true);
	ap.add("--flags", "-f", HasArg::Req, false, true);
	//ap.add("--build", "-b", HasArg::Opt, false, true);
	ap.add("--build", "-b", HasArg::Req, false, true);

	const auto& ap_ret=ap.parse(argc, argv);
	if (ap_ret.fail()) {
		//printerr("Bad argument ", ap_ret.index, " ",
		//	"\"", argv[ap_ret.index], "\" ",
		//	static_cast<i32>(ap_ret.kind),
		//	"\n");
		printerr(ap.help_msg(argc, argv), "\n");
	}
	if (ap.has_opts("-b")) {
		printout(ap.at("-b", 0).val, "\n");
	}

	return 0;
}
