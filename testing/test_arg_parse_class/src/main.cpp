#include "misc_includes.hpp"

int main(int argc, char** argv) {
	ArgParser ap;
	ap.add("--compile", std::nullopt, HasArg::None, false);
	ap.add("--debug", "-d", HasArg::None, false);
	ap.add("--flags", "-f", HasArg::Req, false);
	ap.add("--build", "-b", HasArg::Opt, false);

	if (const auto& fail=ap.parse(argc, argv); fail) {
		printerr("Bad argument ", fail->index, " ",
			"\"", argv[fail->index], "\" ",
			static_cast<i32>(fail->kind),
			"\n");
	}

	return 0;
}
