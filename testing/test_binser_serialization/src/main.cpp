#include <fstream>

#include "hierarchy_classes.hpp"
#include "test_class.hpp"

class IcllTest final
{
public:		// variables
	#define MEMB_LIST_ICLL_TEST(X) \
		X(x, std::nullopt) \
		X(str, std::nullopt) \

	u32 x;
	std::string str;
public:		// functions
	static inline IcllTest from_bv(const binser::Value& bv)
	{
		IcllTest ret;

		MEMB_LIST_ICLL_TEST(BINSER_MEMB_FROM_BV_DESERIALIZE);

		return ret;
	}

	inline operator binser::Value () const
	{
		binser::Value ret;

		MEMB_LIST_ICLL_TEST(BINSER_MEMB_SERIALIZE);

		return ret;
	}
};

std::ostream& operator << (std::ostream& os, const IcllTest& icll_test)
{
	return osprintout(os,
		"x: ", icll_test.x, ", ",
		"str: ", icll_test.str);
}

inline void test_write_binser_file(const std::string& bv_file_name,
	const binser::Value& bv)
{
	if (auto bv_file=std::fstream(bv_file_name,
		std::ios_base::out | std::ios_base::binary); true)
	{
		binser::write_binser(bv_file, bv);
	}
}
inline void test_write_json_file(const std::string& jv_file_name,
	const binser::Value& bv)
{
	if (auto jv_file=std::fstream(jv_file_name, std::ios_base::out); true)
	{
		Json::Value jv_root = binser::bv_to_jv(bv);
		json::write_json(jv_file, &jv_root);
	}
}
int main(int argc, char** argv)
{
	//--------
	//IndCircLinkList<IcllTest> cll;
	//cll.push_back({.x=42, .str="The answer to everything"});
	//cll.push_back({.x=9001, .str="It's over nine thousand!"});
	//cll.push_back({.x=420, .str="smoave"});

	//for (const auto& item: cll)
	//{
	//	printout(item, "\n");
	//}

	//binser::Value bv;
	//binser::set_bv(bv, cll);

	//if (auto jv_file=std::fstream("cll.json.ignore",
	//	std::ios_base::out); true)
	//{
	//	Json::Value jv_root = binser::bv_to_jv(bv);
	//	json::write_json(jv_file, &jv_root);
	//}
	//--------
	binser::VectorEx<IcllTest> oracle_darr;
	oracle_darr.data.push_back({.x=42, .str="The answer to everything"});
	oracle_darr.data.push_back({.x=9001, .str="It's over nine thousand!"});
	oracle_darr.data.push_back({.x=420, .str="smoave"});

	binser::VectorEx<IcllTest> test_darr;
	test_darr.checked_size = 3;
	test_darr.cs_is_max = false;
	test_darr.min_size = 3;

	//for (size_t i=0; i<vec.data.size(); ++i)
	//{
	//	printout(item, ", ");
	//}
	//for (const auto& item: vec)
	//if (std::vector<std::string> temp_str_darr; true)
	//{
	//	for (const auto& item: vec.data)
	//	{
	//		temp_str_darr.push_back(sconcat(item));
	//	}

	//	printout("{\n\t", strjoin2("\n\t", temp_str_darr), "\n}\n");
	//}

	//binser::Value bv;
	//binser::set_bv(bv, vec);

	//test_write_binser_file("test_darr.binser.ignore", bv);
	//test_write_json_file("test_darr.json.ignore", bv);

	if (auto bv_file=std::fstream("test_darr.binser.ignore",
		std::ios_base::in | std::ios_base::binary); true)
	{
		binser::Value bv;
		binser::parse_binser(bv_file, bv);
		binser::val_from_bv(test_darr, bv, std::nullopt);
	}
	//--------
	//std::vector<std::string> test_darr;
	//test_darr.push_back("asdf");
	//test_darr.push_back("jkl;");

	//binser::Value bv;
	//binser::set_bv(bv, test_darr);

	//if (auto jv_file=std::fstream("test_darr.json.ignore",
	//	std::ios_base::out); true)
	//{
	//	Json::Value jv_root = binser::bv_to_jv(bv);
	//	json::write_json(jv_file, &jv_root);
	//}
	//--------
	//binser::Value val = binser::ValueMap();
	//val.insert("0", binser::Value(std::string("asdf")));
	//val.insert("1", binser::Value(std::string("GGGGG")));
	////printout(val.at("0").get<std::string>(), "\n");

	//osprint_hexdump(std::cout, val);

	////--------
	//std::array<Test, 2> test_arr;
	////--------
	//if (auto file=std::fstream("test_0.binser.ignore", 
	//	std::ios_base::out | std::ios_base::binary);
	//	true)
	//{
	//	//test_arr.at(0).data.reset(new DerivedB(std::string
	//	//	("this is my silly string!")));

	//	test_arr.at(0).data[DerivedA::KIND_STR]
	//		= std::unique_ptr<Base>(new DerivedA(3, 5.9));
	//	test_arr.at(0).data[DerivedB::KIND_STR]
	//		= std::unique_ptr<Base>(new DerivedB
	//			(std::string("hello test_0!")));

	//	if (auto bv=binser::Value(); true)
	//	{
	//		//binser::set_bv_memb(bv, "a", );
	//		//bv.insert("a", double(3.0));
	//		//bv.insert("b", u32(69));

	//		if (auto bv1=binser::Value(); true)
	//		{
	//			//set_bv_memb(bv, "c", bv1);
	//			//bv1.push_back(i32(326));
	//			bv1.push_back(std::string("bananas"));
	//			bv1.push_back(u64(326));
	//			bv1.push_back(i64(-326));
	//			bv1.push_back(std::monostate());
	//			bv.insert("c", std::move(bv1));
	//		}
	//		//c.c_darr = std::vector<char>(bv);
	//		test_arr.at(0).data[DerivedC::KIND_STR]
	//			= std::unique_ptr<Base>(new DerivedC
	//				(std::vector<char>(bv)));
	//	}
	//	//test_arr.at(0).data
	//	//= {
	//	//	{DerivedA::KIND_STR, std::unique_ptr<Base>(new DerivedA(3))},
	//	//	{DerivedB::KIND_STR, std::unique_ptr<Base>(new DerivedB
	//	//		(std::string("hello test_0!")))},
	//	//};
	//	binser::Value bv_root = test_arr.at(0);
	//	//osprint_hexdump(std::cout, root, 20);

	//	//const auto& ser_darr = static_cast<std::vector<char>>(bv_root);
	//	//for (const auto& c: ser_darr)
	//	//{
	//	//	file.put(c);
	//	//}
	//	binser::write_binser(file, bv_root);

	//	if (auto jv_file=std::fstream("test_0.json.ignore",
	//		std::ios_base::out); true)
	//	{
	//		Json::Value jv_root = binser::bv_to_jv(bv_root);
	//		json::write_json(jv_file, &jv_root);
	//	}

	//	//write_json(file, &root);
	//	//file.sync();
	//}
	////--------
	//if (auto file=std::fstream("test_0.binser.ignore",
	//	std::ios_base::in | std::ios_base::binary);
	//	true)
	//{
	//	binser::Value bv_root;

	//	binser::parse_binser(file, bv_root);

	//	//{
	//	//	std::vector<char> vec;
	//	//	while (!file.eof())
	//	//	{
	//	//		vec.push_back(file.get());
	//	//	}
	//	//	bv_root = vec;
	//	//}

	//	if (auto jv_file=std::fstream("test_1.json.ignore",
	//		std::ios_base::out);
	//		true)
	//	{
	//		Json::Value jv_root = binser::bv_to_jv(bv_root);
	//		json::write_json(jv_file, &jv_root);
	//	}

	//	//std::string errs;

	//	//if (!parse_json(file, &root, &errs))
	//	//{
	//	//	printerr("parse_json() errs: ", errs, "\n");
	//	//	exit(1);
	//	//}

	//	test_arr.at(1).deserialize(bv_root);

	//	for (const auto& pair: test_arr.at(1).data)
	//	{
	//		printout("\"", pair.first, "\": ");

	//		auto& p2 = pair.second;

	//		if (p2->kind_str() == DerivedA::KIND_STR)
	//		{
	//			auto a = static_cast<DerivedA*>(p2.get());
	//			printout(a->asdf, " ", a->ghdl);
	//		}
	//		else if (p2->kind_str() == DerivedB::KIND_STR)
	//		{
	//			auto b = static_cast<DerivedB*>(p2.get());
	//			printout(b->spunk);
	//		}
	//		else if (p2->kind_str() == DerivedC::KIND_STR)
	//		{
	//			printout("\n");
	//			auto c = static_cast<DerivedC*>(p2.get());
	//			osprint_hexdump(std::cout, c->c_darr, 20);

	//			if (auto jv_file=std::fstream("test_2.json.ignore",
	//				std::ios_base::out);
	//				true)
	//			{
	//				Json::Value jv_root = binser::bv_to_jv
	//					(binser::Value(c->c_darr));
	//				json::write_json(jv_file, &jv_root);
	//			}
	//		}
	//		else
	//		{
	//			printerr("Error: Invalid `pair.first`\n");
	//			exit(1);
	//		}
	//		printout("\n");
	//	}

	//	//printout(static_cast<DerivedB*>(test_arr.at(0).data.get())->b,
	//	//	"\n");
	//}
	//--------

	return 0;
}
