#include "test_class.hpp"

Test::Test()
{
	_data_func_map
		= FromJvFactory<Base>::gen_func_map
		<
			DerivedA,
			DerivedB
		>
		();
}

void Test::deserialize(const Json::Value& jv)
{
	//MEMB_LIST_TEST(JSON_MEMB_DESERIALIZE);
	//get_jv_memb(test, jv, "test", &_test_func_map);
	//get_jv_memb<decltype(test), Base>(test, jv, "test", _test_func_map);
	MEMB_LIST_TEST(JSON_MEMB_DESERIALIZE);
}
Test::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_TEST(JSON_MEMB_SERIALIZE);

	return ret;
}
