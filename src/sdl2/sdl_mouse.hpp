#ifndef liborangepower_sdl2_sdl_mouse_hpp
#define liborangepower_sdl2_sdl_mouse_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>

namespace liborangepower
{

namespace sdl
{

class Cursor final
{
private:		// variables
	SDL_Cursor* _self = nullptr;

public:		// functions
	inline Cursor(SDL_Cursor* s_self)
		: _self(s_self)
	{
	}
	inline Cursor(const Cursor& to_copy) = delete;
	inline Cursor(Cursor&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~Cursor()
	{
		if (_self != nullptr)
		{
			SDL_FreeCursor(_self);
		}
	}
	inline Cursor& operator = (const Cursor& to_copy)
		= delete;
	inline Cursor& operator = (Cursor&& to_move)
	{
		std::swap(_self, to_move._self);

		return *this;
	}
	inline operator SDL_Cursor* ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_mouse_hpp
