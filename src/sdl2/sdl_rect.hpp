#ifndef liborangepower_sdl2_sdl_render_hpp
#define liborangepower_sdl2_sdl_render_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <algorithm>
#include <SDL.h>
#include <SDL_rect.h>

namespace liborangepower
{

namespace sdl
{

class Rect final
{
private:		// variables
	SDL_Rect _self;

public:		// functions
	inline Rect() = default;
	inline Rect(int s_x, int s_y, int s_w, int s_h)
	{
		_self.x = s_x;
		_self.y = s_y;
		_self.w = s_w;
		_self.h = s_h;
	}
	inline Rect(const SDL_Rect& s_self)
		: _self(s_self)
	{
	}
	inline ~Rect() = default;

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Rect);
	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower
