#ifndef liborangepower_sdl2_sdl_rect_hpp
#define liborangepower_sdl2_sdl_rect_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <algorithm>
#include <SDL.h>
#include <SDL_rect.h>

namespace liborangepower
{

namespace sdl
{

class Point final
{
private:		// variables
	SDL_Point _self;

public:		// functions
	inline Point() = default;
	inline Point(int s_x, int s_y)
	{
		_self.x = s_x;
		_self.y = s_y;
	}
	inline Point(const SDL_Point& s_self)
		: _self(s_self)
	{
	}
	inline ~Point() = default;

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Point);

	inline operator const SDL_Point* () const
	{
		return &_self;
	}
	inline operator SDL_Point* ()
	{
		return &_self;
	}
	inline const SDL_Point* operator -> () const
	{
		return &_self;
	}
	inline SDL_Point* operator -> ()
	{
		return &_self;
	}
	GEN_GETTERS_BY_CON_REF_AND_REF(self);
};

class FPoint final
{
private:		// variables
	SDL_FPoint _self;

public:		// functions
	inline FPoint() = default;
	inline FPoint(float s_x, float s_y)
	{
		_self.x = s_x;
		_self.y = s_y;
	}
	inline FPoint(const SDL_FPoint& s_self)
		: _self(s_self)
	{
	}
	inline ~FPoint() = default;

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(FPoint);

	inline operator const SDL_FPoint* () const
	{
		return &_self;
	}
	inline operator SDL_FPoint* ()
	{
		return &_self;
	}
	inline const SDL_FPoint* operator -> () const
	{
		return &_self;
	}
	inline SDL_FPoint* operator -> ()
	{
		return &_self;
	}
	GEN_GETTERS_BY_CON_REF_AND_REF(self);
};

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

	inline operator const SDL_Rect* () const
	{
		return &_self;
	}
	inline operator SDL_Rect* ()
	{
		return &_self;
	}
	inline const SDL_Rect* operator -> () const
	{
		return &_self;
	}
	inline SDL_Rect* operator -> ()
	{
		return &_self;
	}
	GEN_GETTERS_BY_CON_REF_AND_REF(self);
};

class FRect final
{
private:		// variables
	SDL_FRect _self;

public:		// functions
	inline FRect() = default;
	inline FRect(float s_x, float s_y, float s_w, float s_h)
	{
		_self.x = s_x;
		_self.y = s_y;
		_self.w = s_w;
		_self.h = s_h;
	}
	inline FRect(const SDL_FRect& s_self)
		: _self(s_self)
	{
	}
	inline ~FRect() = default;

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(FRect);

	inline operator const SDL_FRect* () const
	{
		return &_self;
	}
	inline operator SDL_FRect* ()
	{
		return &_self;
	}
	inline const SDL_FRect* operator -> () const
	{
		return &_self;
	}
	inline SDL_FRect* operator -> ()
	{
		return &_self;
	}
	GEN_GETTERS_BY_CON_REF_AND_REF(self);
};

} // namespace sdl

} // namespace liborangepower

#endif		// liborangepower_sdl2_sdl_rect_hpp