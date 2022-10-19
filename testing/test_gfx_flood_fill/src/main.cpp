#include "test_funcs.hpp"

int main(int argc, char** argv) {
	//--------
	//if (argc != 3) {
	//	printerr("Usage: ", argv[0], " ", );
	//	exit(1);
	//}
	//--------
	//std::vector<IntVec2> plot_dynarr
	pcg32 rng;
	if (argc == 1) {
		rng = pcg32(get_hrc_now_rng_seed());
	} else if (argc == 2) {
		i64 seed;
		std::stringstream sstm;
		sstm << argv[1];
		sstm >> seed;
		rng = pcg32(seed);
	} else {
		printerr("Usage 1: ", argv[0], "\n");
		printerr("Usage 2: ", argv[0], " seed\n");
		exit(1);
	}
	//--------
	//test_line(rng);
	test_tri2(rng);
	//--------
	return 0;
}
