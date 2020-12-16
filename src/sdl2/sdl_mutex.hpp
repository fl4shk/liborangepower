#ifndef liborangepower_sdl2_sdl_mutex_hpp
#define liborangepower_sdl2_sdl_mutex_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mutex.h>

namespace liborangepower
{

namespace sdl
{

class Cond final
{
private:		// variables
	SDL_cond* _self = nullptr;

public:		// functions
	inline Cond(SDL_cond* s_self)
		: _self(s_self)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Cond);
	inline ~Cond()
	{
		if (_self != nullptr)
		{
			SDL_DestroyCond(_self);
		}
	}

	GEN_GETTER_BY_REF(self);
};

class Mutex final
{
private:		// variables
	SDL_mutex* _self = nullptr;

public:		// functions
	inline Mutex(SDL_mutex* s_self)
		: _self(s_self)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Mutex);
	inline ~Mutex()
	{
		if (_self != nullptr)
		{
			SDL_DestroyMutex(_self);
		}
	}

	GEN_GETTER_BY_REF(self);
};

class Semaphore final
{
private:		// variables
	SDL_sem* _self = nullptr;

public:		// functions
	inline Semaphore(SDL_sem* s_self)
		: _self(s_self)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Semaphore);
	inline ~Semaphore()
	{
		if (_self != nullptr)
		{
			SDL_DestroySemaphore(_self);
		}
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_mutex_hpp
