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

		if (auto bv=binser::Value(); true)
		{
			//binser::set_bv_memb(bv, "a", );
			//bv.insert("a", double(3.0));
			//bv.insert("b", u32(69));

			if (auto bv1=binser::Value(); true)
			{
				//set_bv_memb(bv, "c", bv1);
				//bv1.push_back(i32(326));
				bv1.push_back(std::string("bananas"));
				bv1.push_back(u64(326));
				bv1.push_back(i64(-326));
				//bv1.push_back(std::monostate());
				bv.insert("c", std::move(bv1));
			}
			//c.c_vec = std::vector<char>(bv);
			test_arr.at(0).data[DerivedC::KIND_STR]
				= std::unique_ptr<Base>(new DerivedC
					(std::vector<char>(bv)));
		}
		//test_arr.at(0).data
		//= {
		//	{DerivedA::KIND_STR, std::unique_ptr<Base>(new DerivedA(3))},
		//	{DerivedB::KIND_STR, std::unique_ptr<Base>(new DerivedB
		//		(std::string("hello test_0!")))},
		//};
		binser::Value bv_root = test_arr.at(0);
		//osprint_hexdump(std::cout, root, 20);

		//const auto& ser_vec = static_cast<std::vector<char>>(bv_root);
		//for (const auto& c: ser_vec)
		//{
		//	file.put(c);
		//}
		binser::write_binser(file, bv_root);

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

		binser::parse_binser(file, bv_root);

		//{
		//	std::vector<char> vec;
		//	while (!file.eof())
		//	{
		//		vec.push_back(file.get());
		//	}
		//	bv_root = vec;
		//}

		if (auto jv_file=std::fstream("test_1.json.ignore",
			std::ios_base::out);
			true)
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
				auto a = static_cast<DerivedA*>(p2.get());
				printout(a->asdf, " ", a->ghdl);
			}
			else if (p2->kind_str() == DerivedB::KIND_STR)
			{
				auto b = static_cast<DerivedB*>(p2.get());
				printout(b->spunk);
			}
			else if (p2->kind_str() == DerivedC::KIND_STR)
			{
				printout("\n");
				auto c = static_cast<DerivedC*>(p2.get());
				osprint_hexdump(std::cout, c->c_vec, 20);
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
