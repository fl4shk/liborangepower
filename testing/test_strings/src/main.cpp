#include "misc_includes.hpp"

int main(int argc, char** argv)
{
	//std::vector<std::string> vec;

	//for (int i=0; i<argc; ++i)
	//{
	//	vec.push_back(sconcat());
	//}
	//if (std::vector<std::string> vec; true)
	//{
	//	for (int i=0; i<argc; ++i)
	//	{
	//		vec.push_back(std::string(argv[i]));
	//	}

	//	printout(strjoin<decltype(vec), char, std::char_traits<char>,
	//	std::allocator<char>>(std::string("; "), vec));
	//}
	//printout(sconcat(argv[0]), "\n");
	//printout(strjoin2(std::string(";"),
	//	std::string("asdf"), std::string("gerbil"), std::string("car")),
	//	"\n");
	//printout("asdf", "gerbil", "car", "\n");
	printout(strjoin2(std::string("; "),
		std::vector<std::string>
		({
			std::string("asdf"),
			std::string("gerbil"),
			std::string("car"),
			sconcat(Vec2(3, 3))
			//(Vec2(3, 3))
		})),
		"\n");

	return 0;
}
