#ifndef liborangepower_sdl2_sdl_sensor_hpp
#define liborangepower_sdl2_sdl_sensor_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <algorithm>
#include <SDL.h>
#include <SDL_sensor.h>

namespace liborangepower
{

namespace sdl
{

class Sensor final
{
private:		// variables
	SDL_Sensor* _self = nullptr;

public:		// functions
	inline Sensor(SDL_Sensor* s_self=nullptr)
		: _self(s_self)
	{
	}
	inline Sensor(const Sensor& to_copy) = delete;
	inline Sensor(Sensor&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~Sensor()
	{
		if (_self != nullptr)
		{
			SDL_SensorClose(_self);
		}
	}
	inline Sensor& operator = (const Sensor& to_copy)
		= delete;
	inline Sensor& operator = (Sensor&& to_move)
	{
		std::swap(_self, to_move._self);

		return *this;
	}
	inline operator SDL_Sensor* ()
	{
		return _self;
	}
	inline SDL_Sensor* operator -> ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_sensor_hpp
