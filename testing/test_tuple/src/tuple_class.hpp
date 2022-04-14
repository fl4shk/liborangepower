#ifndef src_tuple_class_hpp
#define src_tuple_class_hpp

#include "misc_includes.hpp"

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


#endif		// src_tuple_class_hpp
