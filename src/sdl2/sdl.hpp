#ifndef liborangepower_sdl2_sdl_hpp
#define liborangepower_sdl2_sdl_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <algorithm>
#include <SDL.h>

namespace liborangepower
{

namespace sdl
{

//template<typename T>
//class StructWrapper
//{
//public:		// typedefs
//	using Dtor = void (*)(T* self);
//private:		// variables
//	T* _self;
//	Dtor _dtor;
//public:		// functions
//	inline StructWrapper(T* self, Dtor dtor)
//		: _self(self), _dtor(dtor)
//	{
//	}
//	virtual inline ~StructWrapper()
//	{
//		_dtor(_self);
//	}
//};

class QuitUponDtor final
{
private:		// variables
	bool _valid;
public:		// functions
	inline QuitUponDtor(bool s_valid=true)
		: _valid(s_valid)
	{
	}
	inline QuitUponDtor(const QuitUponDtor& to_copy) = delete;
	inline QuitUponDtor(QuitUponDtor&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~QuitUponDtor()
	{
		SDL_Quit();
	}
	inline QuitUponDtor& operator = (const QuitUponDtor& to_copy)
		= delete;
	inline QuitUponDtor& operator = (QuitUponDtor&& to_move)
	{
		std::swap(_valid, to_move._valid);

		return *this;
	}
};

} // namespace sdl

} // namespace liborangepower

#endif		// liborangepower_sdl2_sdl_hpp
