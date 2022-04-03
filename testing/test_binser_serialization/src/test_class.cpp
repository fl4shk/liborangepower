#include "test_class.hpp"

Test::Test()
{
	_data_func_map
		= binser::FromBvFactory<Base>::gen_func_map
		<
			DerivedA,
			DerivedB,
			DerivedC
		>
		();
}

void Test::deserialize(const binser::Value& bv)
{
	//MEMB_LIST_TEST(JSON_MEMB_DESERIALIZE);
	//get_bv_memb(test, bv, "test", &_test_func_map);
	//get_bv_memb<decltype(test), Base>(test, bv, "test", _test_func_map);
	MEMB_LIST_TEST(BINSER_MEMB_DESERIALIZE);
}
Test::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_TEST(BINSER_MEMB_SERIALIZE);

	return ret;
}
