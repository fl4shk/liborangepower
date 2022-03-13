#include <fstream>

#include "hierarchy_classes.hpp"
#include "test_class.hpp"

int main(int argc, char** argv)
{
	std::array<Test, 2> test_arr;

	//if (auto file=std::fstream("test_0.json.ignore", std::ios_base::out);
	//	true)
	//{
	//	//test_arr.at(0).data.reset(new DerivedB(std::string
	//	//	("this is my silly string!")));

	//	test_arr.at(0).data[DerivedA::KIND_STR]
	//		= std::unique_ptr<Base>(new DerivedA(3));
	//	test_arr.at(0).data[DerivedB::KIND_STR]
	//		= std::unique_ptr<Base>(new DerivedB
	//			(std::string("hello test_0!")));
	//	//test_arr.at(0).data
	//	//= {
	//	//	{DerivedA::KIND_STR, std::unique_ptr<Base>(new DerivedA(3))},
	//	//	{DerivedB::KIND_STR, std::unique_ptr<Base>(new DerivedB
	//	//		(std::string("hello test_0!")))},
	//	//};
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

		test_arr.at(1).deserialize(root);

		for (const auto& pair: test_arr.at(1).data)
		{
			printout("\"", pair.first, "\": ");

			auto& p2 = pair.second;

			if (p2->kind_str() == DerivedA::KIND_STR)
			{
				printout(static_cast<DerivedA*>(p2.get())->a);
			}
			else if (p2->kind_str() == DerivedB::KIND_STR)
			{
				printout(static_cast<DerivedB*>(p2.get())->b);
			}
			else
			{
				printerr("Error: Invalid `pair.first`\n");
				exit(1);
			}
			printout("\n");
		}

		//printout(static_cast<DerivedB*>(test_arr.at(0).data.get())->b,
		//	"\n");
	}

	return 0;
}
