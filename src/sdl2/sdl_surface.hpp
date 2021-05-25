#ifndef liborangepower_sdl2_sdl_surface_hpp
#define liborangepower_sdl2_sdl_surface_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <algorithm>
#include <SDL.h>
#include <SDL_surface.h>

namespace liborangepower
{

namespace sdl
{

class Surface final
{
private:		// variables
	SDL_Surface* _self = nullptr;

public:		// functions
	inline Surface(SDL_Surface* s_self=nullptr)
		: _self(s_self)
	{
	}
	inline Surface(const Surface& to_copy) = delete;
	inline Surface(Surface&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~Surface()
	{
		if (_self != nullptr)
		{
			SDL_FreeSurface(_self);
		}
	}
	inline Surface& operator = (const Surface& to_copy)
		= delete;
	inline Surface& operator = (Surface&& to_move)
	{
		std::swap(_self, to_move._self);

		return *this;
	}
	inline operator SDL_Surface* ()
	{
		return _self;
	}
	inline SDL_Surface* operator -> ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_surface_hpp
