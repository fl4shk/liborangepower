#ifndef liborangepower_sdl2_sdl_surface_hpp
#define liborangepower_sdl2_sdl_surface_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>

namespace liborangepower
{

namespace sdl
{

class Surface final
{
private:		// variables
	SDL_Surface* _self = nullptr;

public:		// functions
	inline Surface(SDL_Surface* s_self)
		: _self(s_self)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Surface);
	inline ~Surface()
	{
		if (_self != nullptr)
		{
			SDL_FreeSurface(_self);
		}
	}
	inline operator SDL_Surface* ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_surface_hpp
