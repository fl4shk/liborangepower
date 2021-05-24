#ifndef liborangepower_sdl2_sdl_mutex_hpp
#define liborangepower_sdl2_sdl_mutex_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <algorithm>
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
	inline Cond(SDL_cond* s_self=nullptr)
		: _self(s_self)
	{
	}
	inline Cond(const Cond& to_copy) = delete;
	inline Cond(Cond&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~Cond()
	{
		if (_self != nullptr)
		{
			SDL_DestroyCond(_self);
		}
	}
	inline Cond& operator = (const Cond& to_copy)
		= delete;
	inline Cond& operator = (Cond&& to_move)
	{
		std::swap(_self, to_move._self);

		return *this;
	}
	inline operator SDL_cond* ()
	{
		return _self;
	}
	inline operator -> ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

class Mutex final
{
private:		// variables
	SDL_mutex* _self = nullptr;

public:		// functions
	inline Mutex(SDL_mutex* s_self=nullptr)
		: _self(s_self)
	{
	}
	inline Mutex(const Mutex& to_copy) = delete;
	inline Mutex(Mutex&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~Mutex()
	{
		if (_self != nullptr)
		{
			SDL_DestroyMutex(_self);
		}
	}
	inline Mutex& operator = (const Mutex& to_copy)
		= delete;
	inline Mutex& operator = (Mutex&& to_move)
	{
		std::swap(_self, to_move._self);

		return *this;
	}
	inline operator SDL_mutex* ()
	{
		return _self;
	}
	inline operator -> ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

class Semaphore final
{
private:		// variables
	SDL_sem* _self = nullptr;

public:		// functions
	inline Semaphore(SDL_sem* s_self=nullptr)
		: _self(s_self)
	{
	}
	inline Semaphore(const Semaphore& to_copy) = delete;
	inline Semaphore(Semaphore&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~Semaphore()
	{
		if (_self != nullptr)
		{
			SDL_DestroySemaphore(_self);
		}
	}
	inline Semaphore& operator = (const Semaphore& to_copy)
		= delete;
	inline Semaphore& operator = (Semaphore&& to_move)
	{
		std::swap(_self, to_move._self);

		return *this;
	}
	inline operator SDL_sem* ()
	{
		return _self;
	}
	inline operator -> ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_mutex_hpp
