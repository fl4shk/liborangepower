#ifndef liborangepower_sdl2_sdl_video_hpp
#define liborangepower_sdl2_sdl_video_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <algorithm>
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
	inline Window(SDL_Window* s_self=nullptr)
		: _self(s_self)
	{
	}
	inline Window(const Window& to_copy) = delete;
	inline Window(Window&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~Window()
	{
		if (_self != nullptr)
		{
			SDL_DestroyWindow(_self);
		}
	}
	inline Window& operator = (const Window& to_copy)
		= delete;
	inline Window& operator = (Window&& to_move)
	{
		std::swap(_self, to_move._self);

		return *this;
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
