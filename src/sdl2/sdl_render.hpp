#ifndef liborangepower_sdl2_sdl_render_hpp
#define liborangepower_sdl2_sdl_render_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

namespace liborangepower
{

namespace sdl
{

class Renderer final
{
private:		// variables
	SDL_Renderer* _self = nullptr;

public:		// functions
	inline Renderer(SDL_Renderer* s_self)
		: _self(s_self)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Renderer);
	inline ~Renderer()
	{
		if (_self != nullptr)
		{
			SDL_DestroyRenderer(_self);
		}
	}
	inline operator SDL_Renderer* ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

class Texture final
{
private:		// variables
	SDL_Texture* _self = nullptr;

public:		// functions
	inline Texture(SDL_Texture* s_self)
		: _self(s_self)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Texture);
	inline ~Texture()
	{
		if (_self != nullptr)
		{
			SDL_DestroyTexture(_self);
		}
	}
	inline operator SDL_Texture* ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_render_hpp
