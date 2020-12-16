#ifndef liborangepower_sdl2_sdl_gamecontroller_hpp
#define liborangepower_sdl2_sdl_gamecontroller_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <SDL2/SDL.h>
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
	inline GameController(SDL_GameController* s_self)
		: _self(s_self)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(GameController);
	inline ~GameController()
	{
		if (_self != nullptr)
		{
			SDL_GameControllerClose(_self);
		}
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_gamecontroller_hpp
