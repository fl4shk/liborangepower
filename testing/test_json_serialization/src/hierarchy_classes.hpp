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
	Base(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Base);
	virtual ~Base() = default;

	virtual operator Json::Value () const;

	virtual std::string kind_str() const;
};
//--------
class DerivedA: public Base
{
public:		// constants
	static const std::string KIND_STR;
public:		// variables
	#define MEMB_LIST_DERIVED_A(X) \
		X(a, std::nullopt)

	int a = 0;
public:		// functions
	DerivedA() = default;
	inline DerivedA(int s_a)
		: a(s_a)
	{
	}
	DerivedA(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DerivedA);
	virtual ~DerivedA() = default;

	virtual operator Json::Value () const;
	virtual std::string kind_str() const;
};
//--------
class DerivedB: public Base
{
public:		// constants
	static const std::string KIND_STR;
public:		// variables
	#define MEMB_LIST_DERIVED_B(X) \
		X(b, std::nullopt)

	std::string b = "asdf";
public:		// functions
	DerivedB() = default;
	inline DerivedB(const std::string& s_b)
		: b(s_b)
	{
	}
	DerivedB(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DerivedB);
	virtual ~DerivedB() = default;

	virtual operator Json::Value () const;
	virtual std::string kind_str() const;
};
//--------

#endif		// src_hierarchy_classes_hpp
