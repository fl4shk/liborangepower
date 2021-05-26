#ifndef liborangepower_sdl2_keyboard_classes_hpp
#define liborangepower_sdl2_keyboard_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <functional>

#include <SDL.h>
#include <SDL_keyboard.h>

namespace liborangepower
{

namespace sdl
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
			: _sym_mod_pair(s_sym, s_mod), _down(s_down)
		{
		}
		inline ~KeyStatus() = default;
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(KeyStatus);

		inline SDL_Keycode sym() const
		{
			return _sym_mod_pair.sym();
		}
		inline SDL_Keycode set_sym(SDL_Keycode n_sym)
		{
			return _sym_mod_pair.set_sym(n_sym);
		}
		inline Uint16 mod() const
		{
			return _sym_mod_pair.mod();
		}
		inline Uint16 set_mod(Uint16 n_mod)
		{
			return _sym_mod_pair.set_mod(n_mod);
		}
		GEN_GETTER_AND_SETTER_BY_CON_REF(sym_mod_pair);
		GEN_GETTER_AND_SETTER_BY_VAL(down);
	};
} // namespace sdl2

} // namespace liborangepower

namespace std
{
	template<>
	struct hash<liborangepower::sdl::KeycModPair>
	{
		std::size_t operator () 
			(const liborangepower::sdl::KeycModPair& kmp) const noexcept
		{
			std::size_t h0 = std::hash<SDL_Keycode>{}(kmp.sym());
			std::size_t h1 = std::hash<Uint16>{}(kmp.mod());
			return (h0 ^ (h1 << static_cast<std::size_t>(1)));
		}
	};

	template<>
	struct hash<liborangepower::sdl::KeyStatus>
	{
		std::size_t operator ()
			(const liborangepower::sdl::KeyStatus& ks) const noexcept
		{
			std::size_t h0 = std::hash<liborangepower::sdl::KeycModPair>{}
				(ks.sym_mod_pair());
			std::size_t h1 = std::hash<bool>{}(ks.down());
			return (h0 ^ (h1 << static_cast<std::size_t>(1)));
		}
	};
} // namespace std

#endif		// liborangepower_sdl2_keyboard_classes_hpp
