#include <fstream>

#include "hierarchy_classes.hpp"
#include "test_class.hpp"

int main(int argc, char** argv)
{
	std::array<Test, 2> test_arr;

	//if (auto file=std::fstream("test_0.json.ignore", std::ios_base::out);
	//	true)
	//{
	//	test_arr.at(0).data.reset(new DerivedB(std::string
	//		("this is my silly string!")));
	//	Json::Value root = test_arr.at(0);

	//	write_json(file, &root);
	//}

	if (auto file=std::fstream("test_0.json.ignore", std::ios_base::in);
		true)
	{
		Json::Value root;
		std::string errs;

		if (!parse_json(file, &root, &errs))
		{
			printerr("parse_json() errs: ", errs, "\n");
			exit(1);
		}

		test_arr.at(0).deserialize(root);

		printout(static_cast<DerivedB*>(test_arr.at(0).data.get())->b,
			"\n");
	}

	return 0;
}
