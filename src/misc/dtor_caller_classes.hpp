#ifndef liborangepower_misc_dtor_call_class_hpp
#define liborangepower_misc_dtor_call_class_hpp

#include <algorithm>

#include "misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

namespace liborangepower
{

namespace misc_util
{

template<typename Type>
class DtorCaller
{
public:		// typedefs
	using Dtor = void (*)(Type* self);

protected:		// variables
	Type* _self = nullptr;
	Dtor _dtor = nullptr;

public:		// functions
	inline DtorCaller(Type* s_self, Dtor s_dtor)
		: _self(s_self), _dtor(s_dtor)
	{
	}
	inline DtorCaller(const DtorCaller& to_copy) = delete;
	inline DtorCaller(DtorCaller&& to_move)
	{
		*this = std::move(to_move);
	}
	virtual inline ~DtorCaller()
	{
		if (_self != nullptr)
		{
			_dtor(_self);
		}
	}

	inline DtorCaller& operator = (const DtorCaller& to_copy)
		= delete;
	inline DtorCaller& operator = (DtorCaller&& to_move)
	{
		std::swap(_self, to_move._self);
		std::swap(_dtor, to_move._dtor);

		return *this;
	}

	GEN_GETTER_BY_VAL(self);
	GEN_GETTER_BY_VAL(dtor);
};

//template<typename Type>
//class DtorCallerNoObj
//{
//public:		// typedefs
//public:		// functions
//};

} // namespace misc_util

} // namespace liborangepower
#endif		// liborangepower_misc_dtor_call_class_hpp
