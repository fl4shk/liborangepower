#include "misc_includes.hpp"

int main(int argc, char** argv) {
	ArgParser ap;
	ap
		.add_singleton("--compile", std::nullopt, HasArg::None, false, "")
		.add_singleton("--debug", "-d", HasArg::None, false, "")
		.add_singleton("--flags", "-f", HasArg::Req, false, "")
		//.add_singleton("--build", "-b", HasArg::Opt, false, "")
		.add_singleton("--build", "-b", HasArg::Req, false,
			"Build the program.");

	const auto& ap_ret=ap.parse(argc, argv);
	if (ap_ret.fail() || ap_ret.index != argc || argc == 1) {
		//printerr("Bad argument ", ap_ret.index, " ",
		//	"\"", argv[ap_ret.index], "\" ",
		//	static_cast<i32>(ap_ret.kind),
		//	"\n");
		printerr(ap.help_msg(argc, argv), "\n");
		exit(1);
	}
	if (ap.has_opts("-b")) {
		printout(ap.at("-b", 0).val, "\n");
	}

	return 0;
}
