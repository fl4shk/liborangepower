#include "misc_includes.hpp"

int main(int argc, char** argv) {
	ArgParse ap;
	ap.add("--compile", std::nullopt, HasArg::None);
	ap.add("--debug", "-d", HasArg::None);
	ap.add("--flags", "-f", HasArg::Req);
	ap.add("--build", "-b", HasArg::Opt);

	if (const auto& fail=ap.parse(argc, argv); fail) {
		printerr("Bad argument ", fail->index, " ",
			"\"", argv[fail->index], "\" ",
			static_cast<i32>(fail->kind),
			"\n");
	}

	return 0;
}
