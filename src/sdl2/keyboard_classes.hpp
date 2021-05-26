#ifndef liborangepower_sdl2_keyboard_classes_hpp
#define liborangepower_sdl2_keyboard_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <SDL.h>
#include <SDL_keyboard.h>

namespace liborangepower
{

namespace sdl2
{
	class KeycModPair final
	{
	private:		// variables
		SDL_Keycode _sym;
		Uint16 _mod;
	public:		// function
		inline KeycModPair() = default;
		inline KeycModPair(SDL_Keycode s_sym, Uint16 s_mod)
			: _sym(s_sym), _mod(s_mod)
		{
		}
		inline ~KeycModPair() = default;
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(KeycModPair);

		GEN_GETTER_AND_SETTER_BY_VAL(sym);
		GEN_GETTER_AND_SETTER_BY_VAL(mod);
	};
	class KeyStatus final
	{
	private:		// variables
		KeycModPair _sym_mod_pair;
		bool _down = false;
	public:		// functions
		inline KeyStatus() = default;
		inline KeyStatus(const KeycModPair& s_sym_mod_pair,
			bool s_down=false)
			: _sym_mod_pair(s_sym_mod_pair), _down(s_down)
		{
		}
		inline KeyStatus(SDL_Keycode s_sym, Uint16 s_mod,
			bool s_down=false)
			: _sym(s_sym_mod_pair.sym()), _mod(s_sym_mod_pair.mod()),
			_down(s_down)
		{
		}
		inline ~KeyStatus() = default;
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(KeyStatus);

		inline SDL_Keycode sym() const
		{
			return _sym_mod_pair.sym();
		}
		inline SDL_Keycode& set_sym(SDL_Keycode n_sym)
		{
			return _sym_mod_pair.set_sym(n_sym);
		}
		inline Uint16 mod() const
		{
			return _sym_mod_pair.mod();
		}
		inline SDL_Keycode& set_mod(Uint16 n_mod)
		{
			return _sym_mod_pair.set_mod(n_mod);
		}
		GEN_GETTER_AND_SETTER_BY_CON_REF(sym_mod_pair);
		GEN_GETTER_AND_SETTER_BY_VAL(down);
	};
} // namespace sdl2

} // namespace liborangepower

#endif		// liborangepower_sdl2_keyboard_classes_hpp
