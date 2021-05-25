#ifndef liborangepower_sdl2_sdl_gamecontroller_hpp
#define liborangepower_sdl2_sdl_gamecontroller_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_gamecontroller.h>

namespace liborangepower
{

namespace sdl
{

class GameController final
{
private:		// variables
	SDL_GameController* _self = nullptr;

public:		// functions
	inline GameController(SDL_GameController* s_self=nullptr)
		: _self(s_self)
	{
	}
	inline GameController(const GameController& to_copy) = delete;
	inline GameController(GameController&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~GameController()
	{
		if (_self != nullptr)
		{
			SDL_GameControllerClose(_self);
		}
	}
	inline GameController& operator = (const GameController& to_copy)
		= delete;
	inline GameController& operator = (GameController&& to_move)
	{
		std::swap(_self, to_move._self);

		return *this;
	}
	inline operator SDL_GameController* ()
	{
		return _self;
	}
	inline SDL_GameController* operator -> ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_gamecontroller_hpp
