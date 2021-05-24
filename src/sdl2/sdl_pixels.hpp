#ifndef liborangepower_sdl2_sdl_pixels_hpp
#define liborangepower_sdl2_sdl_pixels_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>

namespace liborangepower
{

namespace sdl
{

class Palette final
{
private:		// variables
	SDL_Palette* _self = nullptr;

public:		// functions
	inline Palette(SDL_Palette* s_self=nullptr)
		: _self(s_self)
	{
	}
	inline Palette(const Palette& to_copy) = delete;
	inline Palette(Palette&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~Palette()
	{
		if (_self != nullptr)
		{
			SDL_FreePalette(_self);
		}
	}
	inline Palette& operator = (const Palette& to_copy)
		= delete;
	inline Palette& operator = (Palette&& to_move)
	{
		std::swap(_self, to_move._self);

		return *this;
	}
	inline operator SDL_Palette* ()
	{
		return _self;
	}
	inline operator -> ()
	{
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};

class PixelFormat final
{
private:		// variables
	SDL_PixelFormat* _self = nullptr;

public:		// functions
	inline PixelFormat(SDL_PixelFormat* s_self=nullptr)
		: _self(s_self)
	{
	}
	inline PixelFormat(const PixelFormat& to_copy) = delete;
	inline PixelFormat(PixelFormat&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~PixelFormat()
	{
		if (_self != nullptr)
		{
			SDL_FreeFormat(_self);
		}
	}
	inline PixelFormat& operator = (const PixelFormat& to_copy)
		= delete;
	inline PixelFormat& operator = (PixelFormat&& to_move)
	{
		std::swap(_self, to_move._self);

		return *this;
	}
	inline operator SDL_PixelFormat* ()
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


#endif		// liborangepower_sdl2_sdl_pixels_hpp
