#ifndef src_hierarchy_classes_hpp
#define src_hierarchy_classes_hpp

// src/hierarchy_classes.hpp

#include "misc_includes.hpp"

//--------
class Base
{
public:		// defines
	#define MEMB_LIST_BASE(X)
public:		// functions
	Base() = default;
	Base(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Base);
	virtual ~Base() = default;

	virtual operator binser::Value () const;

	virtual std::string kind_str() const;
};
//--------
class DerivedA: public Base
{
public:		// constants
	static const std::string KIND_STR;
public:		// variables
	#define MEMB_LIST_DERIVED_A(X) \
		X(asdf, std::nullopt) \
		X(ghdl, std::nullopt) \

	int asdf = 0;
	double ghdl = 9.3f;
public:		// functions
	DerivedA() = default;
	inline DerivedA(int s_asdf, double s_ghdl)
		: asdf(s_asdf), ghdl(s_ghdl)
	{
	}
	DerivedA(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DerivedA);
	virtual ~DerivedA() = default;

	virtual operator binser::Value () const;
	virtual std::string kind_str() const;
};
//--------
class DerivedB: public Base
{
public:		// constants
	static const std::string KIND_STR;
public:		// variables
	#define MEMB_LIST_DERIVED_B(X) \
		X(spunk, std::nullopt)

	std::string spunk = "asdf";
public:		// functions
	DerivedB() = default;
	inline DerivedB(const std::string& s_spunk)
		: spunk(s_spunk)
	{
	}
	DerivedB(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DerivedB);
	virtual ~DerivedB() = default;

	virtual operator binser::Value () const;
	virtual std::string kind_str() const;
};
//--------
class DerivedC: public Base
{
public:		// constants
	static const std::string KIND_STR;
public:		// variables
	#define MEMB_LIST_DERIVED_C(X) \
		X(c_darr, std::nullopt)

	std::vector<char> c_darr;
public:		// functions
	DerivedC() = default;
	inline DerivedC(const std::vector<char>& s_c_darr)
		: c_darr(s_c_darr)
	{
	}
	DerivedC(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DerivedC);
	virtual ~DerivedC() = default;

	virtual operator binser::Value () const;
	virtual std::string kind_str() const;
};

#endif		// src_hierarchy_classes_hpp
