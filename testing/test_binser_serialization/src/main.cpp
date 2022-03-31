#include <fstream>

#include "hierarchy_classes.hpp"
#include "test_class.hpp"


int main(int argc, char** argv)
{
	//binser::Value val = binser::ValueMap();
	//val.insert("0", binser::Value(std::string("asdf")));
	//val.insert("1", binser::Value(std::string("GGGGG")));
	////printout(val.at("0").get<std::string>(), "\n");

	//osprint_hexdump(std::cout, val);

	//--------
	std::array<Test, 2> test_arr;
	//--------
	if (auto file=std::fstream("test_0.binser.ignore", 
		std::ios_base::out | std::ios_base::binary);
		true)
	{
		//test_arr.at(0).data.reset(new DerivedB(std::string
		//	("this is my silly string!")));

		test_arr.at(0).data[DerivedA::KIND_STR]
			= std::unique_ptr<Base>(new DerivedA(3, 5.9));
		test_arr.at(0).data[DerivedB::KIND_STR]
			= std::unique_ptr<Base>(new DerivedB
				(std::string("hello test_0!")));
		//test_arr.at(0).data
		//= {
		//	{DerivedA::KIND_STR, std::unique_ptr<Base>(new DerivedA(3))},
		//	{DerivedB::KIND_STR, std::unique_ptr<Base>(new DerivedB
		//		(std::string("hello test_0!")))},
		//};
		binser::Value bv_root = test_arr.at(0);
		//osprint_hexdump(std::cout, root, 20);
		const auto& ser_vec = static_cast<std::vector<char>>(bv_root);
		for (const auto& c: ser_vec)
		{
			file.put(c);
		}

		if (auto jv_file=std::fstream("test_0.json.ignore",
			std::ios_base::out); true)
		{
			Json::Value jv_root = binser::bv_to_jv(bv_root);
			json::write_json(jv_file, &jv_root);
		}

		//write_json(file, &root);
		//file.sync();
	}
	//--------
	if (auto file=std::fstream("test_0.binser.ignore",
		std::ios_base::in | std::ios_base::binary);
		true)
	{
		binser::Value bv_root;

		{
			std::vector<char> vec;
			while (!file.eof())
			{
				vec.push_back(file.get());
			}
			bv_root = vec;
		}

		if (auto jv_file=std::fstream("test_1.json.ignore",
			std::ios_base::out); true)
		{
			Json::Value jv_root = binser::bv_to_jv(bv_root);
			json::write_json(jv_file, &jv_root);
		}

		//std::string errs;

		//if (!parse_json(file, &root, &errs))
		//{
		//	printerr("parse_json() errs: ", errs, "\n");
		//	exit(1);
		//}

		test_arr.at(1).deserialize(bv_root);

		for (const auto& pair: test_arr.at(1).data)
		{
			printout("\"", pair.first, "\": ");

			auto& p2 = pair.second;

			if (p2->kind_str() == DerivedA::KIND_STR)
			{
				auto derived_a = static_cast<DerivedA*>(p2.get());
				printout(derived_a->asdf, " ", derived_a->ghdl);
			}
			else if (p2->kind_str() == DerivedB::KIND_STR)
			{
				printout(static_cast<DerivedB*>(p2.get())->spunk);
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
	//--------

	return 0;
}
