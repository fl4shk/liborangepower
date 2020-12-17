#ifndef liborangepower_sdl2_sdl_hpp
#define liborangepower_sdl2_sdl_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <SDL2/SDL.h>

namespace liborangepower
{

namespace sdl
{

//template<typename Type>
//class StructWrapper
//{
//public:		// typedefs
//	using Dtor = void (*)(Type* self);
//private:		// variables
//	Type* _self;
//	Dtor _dtor;
//public:		// functions
//	inline StructWrapper(Type* self, Dtor dtor)
//		: _self(self), _dtor(dtor)
//	{
//	}
//	virtual inline ~StructWrapper()
//	{
//		_dtor(_self);
//	}
//};

class QuitUponDtor final
{
public:		// functions
	inline QuitUponDtor()
	{
	}
	inline ~QuitUponDtor()
	{
		SDL_Quit();
	}
};

} // namespace sdl

} // namespace liborangepower

#endif		// liborangepower_sdl2_sdl_hpp
