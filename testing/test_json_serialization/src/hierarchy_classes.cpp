#include "hierarchy_classes.hpp"

//--------
Base::Base(const Json::Value& jv)
{
	MEMB_LIST_BASE(JSON_MEMB_DESERIALIZE);
}
Base::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_BASE(JSON_MEMB_SERIALIZE);

	return ret;
}
std::string Base::kind_str() const
{
	return "";
}
//--------
const std::string
	DerivedA::KIND_STR("DerivedA");

DerivedA::DerivedA(const Json::Value& jv)
{
	MEMB_LIST_DERIVED_A(JSON_MEMB_DESERIALIZE);
}
DerivedA::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_DERIVED_A(JSON_MEMB_SERIALIZE);

	return ret;
}
std::string DerivedA::kind_str() const
{
	return KIND_STR;
}
//--------
const std::string
	DerivedB::KIND_STR("DerivedB");

DerivedB::DerivedB(const Json::Value& jv)
{
	MEMB_LIST_DERIVED_B(JSON_MEMB_DESERIALIZE);
}
DerivedB::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_DERIVED_B(JSON_MEMB_SERIALIZE);

	return ret;
}
std::string DerivedB::kind_str() const
{
	return KIND_STR;
}
//--------
