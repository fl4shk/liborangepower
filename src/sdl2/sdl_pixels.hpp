#ifndef liborangepower_sdl2_sdl_pixels_hpp
#define liborangepower_sdl2_sdl_pixels_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>

namespace liborangepower
{

namespace sdl
{

class Palette final
{
private:		// variables
	SDL_Palette* _self = nullptr;

public:		// functions
	inline Palette(SDL_Palette* s_self)
		: _self(s_self)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Palette);
	inline ~Palette()
	{
		if (_self != nullptr)
		{
			SDL_FreePalette(_self);
		}
	}
	inline operator SDL_Palette* ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_pixels_hpp
