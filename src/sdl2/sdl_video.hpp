#ifndef liborangepower_sdl2_sdl_video_hpp
#define liborangepower_sdl2_sdl_video_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

namespace liborangepower
{

namespace sdl
{

class Window final
{
private:		// variables
	SDL_Window* _self = nullptr;

public:		// functions
	inline Window(SDL_Window* s_self)
		: _self(s_self)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Window);
	inline ~Window()
	{
		if (_self != nullptr)
		{
			SDL_DestroyWindow(_self);
		}
	}
	inline operator SDL_Window* ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_video_hpp
