#ifndef liborangepower_sdl2_sdl_render_hpp
#define liborangepower_sdl2_sdl_render_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <algorithm>
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
	inline Renderer(SDL_Renderer* s_self=nullptr)
		: _self(s_self)
	{
	}
	inline Renderer(const Renderer& to_copy) = delete;
	inline Renderer(Renderer&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~Renderer()
	{
		if (_self != nullptr)
		{
			SDL_DestroyRenderer(_self);
		}
	}
	inline Renderer& operator = (const Renderer& to_copy)
		= delete;
	inline Renderer& operator = (Renderer&& to_move)
	{
		std::swap(_self, to_move._self);

		return *this;
	}
	inline operator SDL_Renderer* ()
	{
		return _self;
	}
	inline SDL_Renderer* operator -> ()
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
	inline Texture(SDL_Texture* s_self=nullptr)
		: _self(s_self)
	{
	}
	inline Texture(const Texture& to_copy) = delete;
	inline Texture(Texture&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~Texture()
	{
		if (_self != nullptr)
		{
			SDL_DestroyTexture(_self);
		}
	}
	inline Texture& operator = (const Texture& to_copy)
		= delete;
	inline Texture& operator = (Texture&& to_move)
	{
		std::swap(_self, to_move._self);

		return *this;
	}
	inline operator SDL_Texture* ()
	{
		return _self;
	}
	inline SDL_Texture* operator -> ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_render_hpp
