#include "misc_includes.hpp"
//#include <vector>
//#include <string>
//#include <iostream>
//#include <cstdint>

template<bool have_mbr, typename T>
class MaybeMbr
{
public:		// variables
	T mbr;
};

template<typename T>
class MaybeMbr<false, T>
{
};

template<bool have_mbr, size_t _index, typename... Ts>
class TupleHelper
{
};

template<size_t _index, typename FirstT, typename... RemTs>
class TupleHelper<true, _index, FirstT, RemTs...>
	: public TupleHelper<(sizeof...(RemTs) > 0), _index + 1, RemTs...>
{
public:		// types
	using Base
		= TupleHelper<(sizeof...(RemTs) > 0), _index + 1, RemTs...>;
public:		// constants
	static constexpr size_t INDEX = _index;
public:		// variables
	FirstT mbr;
	//TupleHelper<(sizeof...(RemTs) > 0), RemTs...> super;
public:		// functions
	inline TupleHelper()
	{
	}
	inline TupleHelper(const FirstT& s_mbr, const RemTs&... rem_mbrs)
		: Base(rem_mbrs...), mbr(s_mbr)
	{
	}
	inline TupleHelper(FirstT&& s_mbr, RemTs&&... rem_mbrs)
		: Base(std::move(rem_mbrs)...), mbr(std::move(s_mbr))
	{
		//std::cout << "TupleHelper(): " << typeid(mbr).name() << "\n";
		printout("TupleHelper(): ", typeid(mbr).name(), "\n");
	}
	inline TupleHelper(const TupleHelper&) = default;
	inline TupleHelper(TupleHelper&&) = default;
	virtual ~TupleHelper() = default;

	inline TupleHelper& operator = (const TupleHelper&) = default;
	inline TupleHelper& operator = (TupleHelper&&) = default;

	inline Base& base()
	{
		return *this;
	}
	inline const Base& base() const
	{
		return *this;
	}
};

template<typename FirstT, typename... RemTs>
class Tuple: public TupleHelper<true, 0, FirstT, RemTs...>
{
public:		// types
	using Base = TupleHelper<true, 0, FirstT, RemTs...>;
public:		// functions
	inline Tuple()
	{
	}
	inline Tuple(const FirstT& s_mbr, const RemTs&... rem_mbrs)
		: Base(s_mbr, rem_mbrs...)
	{
	}
	inline Tuple(FirstT&& s_mbr, RemTs&&... rem_mbrs)
		: Base(std::move(s_mbr), std::move(rem_mbrs)...)
	{
	}
	inline Tuple(const Tuple&) = default;
	inline Tuple(Tuple&&) = default;
	virtual ~Tuple() = default;

	inline Tuple& operator = (const Tuple&) = default;
	inline Tuple& operator = (Tuple&&) = default;
};

int main(int argc, char** argv)
{
	//Tuple<int, int> tup(3, 5);

	Tuple<std::vector<int>, std::string> tup({3, 5}, "asdf");
	//Tuple<std::vector<int>, std::string> tup;
	//tup.mbr = {3, 5};
	//tup.mbr = 3;
	//tup.base().mbr = 5;
	//std::cout << tup.mbr << " " << tup.base().mbr << "\n";
	//printout(tup.mbr, " ", tup.base().mbr, "\n");

	for (size_t i=0; i<tup.mbr.size(); ++i)
	{
		//printout(tup.mbr.at(i), " ");

		printout(tup.mbr.at(i));
		if (i + 1 < tup.mbr.size())
		{
			printout(" ");
		}
	}
	printout("\n");

	printout(tup.base().mbr, "\n");

	return 0;
}
