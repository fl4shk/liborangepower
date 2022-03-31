#include "hierarchy_classes.hpp"

//--------
Base::Base(const binser::Value& bv)
{
	MEMB_LIST_BASE(BINSER_MEMB_DESERIALIZE);
}
Base::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_BASE(BINSER_MEMB_SERIALIZE);

	return ret;
}
std::string Base::kind_str() const
{
	return "";
}
//--------
const std::string
	DerivedA::KIND_STR("DerivedA");

DerivedA::DerivedA(const binser::Value& bv)
{
	MEMB_LIST_DERIVED_A(BINSER_MEMB_DESERIALIZE);
}
DerivedA::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_DERIVED_A(BINSER_MEMB_SERIALIZE);

	return ret;
}
std::string DerivedA::kind_str() const
{
	return KIND_STR;
}
//--------
const std::string
	DerivedB::KIND_STR("DerivedB");

DerivedB::DerivedB(const binser::Value& bv)
{
	MEMB_LIST_DERIVED_B(BINSER_MEMB_DESERIALIZE);
}
DerivedB::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_DERIVED_B(BINSER_MEMB_SERIALIZE);

	return ret;
}
std::string DerivedB::kind_str() const
{
	return KIND_STR;
}
//--------
