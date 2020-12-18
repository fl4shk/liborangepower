#ifndef liborangepower_sdl2_sdl_haptic_hpp
#define liborangepower_sdl2_sdl_haptic_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_haptic.h>

namespace liborangepower
{

namespace sdl
{

class Haptic final
{
private:		// variables
	SDL_Haptic* _self = nullptr;

public:		// functions
	inline Haptic(SDL_Haptic* s_self)
		: _self(s_self)
	{
	}
	inline Haptic(const Haptic& to_copy) = delete;
	inline Haptic(Haptic&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~Haptic()
	{
		if (_self != nullptr)
		{
			SDL_HapticClose(_self);
		}
	}
	inline Haptic& operator = (const Haptic& to_copy)
		= delete;
	inline Haptic& operator = (Haptic&& to_move)
	{
		std::swap(_self, to_move._self);

		return *this;
	}
	inline operator SDL_Haptic* ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_haptic_hpp
