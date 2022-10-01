#ifndef src_test_tuple_class_hpp
#define src_test_tuple_class_hpp

#include "misc_includes.hpp"

template<typename T>
class TestTuple final
{
public:		// variables
	std::string name;
	Vec2<T> p0, p1, tlc, brc;
public:		// functions
	//--------
	inline void cmp_to_oracle(const Rect2<T>& uut) const
	{
		const bool
			tlc_eq = uut.tl_corner() == this->tlc,
			brc_eq = uut.br_corner() == this->brc;

		printout
			(this->name, uut, "\n"
			"\t(", "uut.tlc", uut.tl_corner(), " ",
				"this->tlc", this->tlc, ": ",
				(tlc_eq ? "==" : "!="), ")\n"
			"\t(", "uut.brc", uut.br_corner(), " ",
				"this->brc", this->brc, ": ",
				(brc_eq ? "==" : "!="), ")\n",
			"\t", ((tlc_eq && brc_eq) ? "SUCCESS" : "FAILURE"), "\n");
	}
	//--------
};

template<typename T>
using TestTupleAndRect2 = std::pair<TestTuple<T>, Rect2<T>>;

#endif		// src_test_tuple_class_hpp
