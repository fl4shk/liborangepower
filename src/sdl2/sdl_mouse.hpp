#ifndef liborangepower_sdl2_sdl_mouse_hpp
#define liborangepower_sdl2_sdl_mouse_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

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
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Cursor);
	inline ~Cursor()
	{
		if (_self != nullptr)
		{
			SDL_FreeCursor(_self);
		}
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
