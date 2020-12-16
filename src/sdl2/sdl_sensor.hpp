#ifndef liborangepower_sdl2_sdl_sensor_hpp
#define liborangepower_sdl2_sdl_sensor_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_sensor.h>

namespace liborangepower
{

namespace sdl
{

class Sensor final
{
private:		// variables
	SDL_Sensor* _self = nullptr;

public:		// functions
	inline Sensor(SDL_Sensor* s_self)
		: _self(s_self)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Sensor);
	inline ~Sensor()
	{
		if (_self != nullptr)
		{
			SDL_SensorClose(_self);
		}
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_sensor_hpp
