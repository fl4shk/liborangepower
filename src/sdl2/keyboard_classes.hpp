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

		inline bool operator < (const KeycModPair& to_cmp) const
		{
			if (_sym < to_cmp._sym)
			{
				return true;
			}
			else if (_sym == to_cmp._sym)
			{
				return (_mod < to_cmp._mod);
			}
			else
			{
				return false;
			}
		}
		inline bool operator == (const KeycModPair& to_cmp) const
		{
			return ((_sym == to_cmp._sym) && (_mod == to_cmp._mod));
		}

		GEN_GETTER_AND_SETTER_BY_VAL(sym);
		GEN_GETTER_AND_SETTER_BY_VAL(mod);
	};

	class KeyStatus final
	{
	private:		// variables
		KeycModPair _kmp;
		bool _down = false;
	public:		// functions
		inline KeyStatus() = default;
		inline KeyStatus(const KeycModPair& s_kmp,
			bool s_down=false)
			: _kmp(s_kmp), _down(s_down)
		{
		}
		inline KeyStatus(SDL_Keycode s_sym, Uint16 s_mod,
			bool s_down=false)
			: _kmp(s_sym, s_mod), _down(s_down)
		{
		}
		inline ~KeyStatus() = default;
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(KeyStatus);

		inline bool operator < (const KeyStatus& to_cmp) const
		{
			if (_kmp < to_cmp._kmp)
			{
				return true;
			}
			else if (_kmp == to_cmp._kmp)
			{
				return ((!_down) && (to_cmp._down));
			}
			else
			{
				return false;
			}
		}
		inline bool operator == (const KeyStatus& to_cmp) const
		{
			return ((_kmp == to_cmp._kmp) && (_down == to_cmp._down));
		}

		inline SDL_Keycode sym() const
		{
			return _kmp.sym();
		}
		inline SDL_Keycode set_sym(SDL_Keycode n_sym)
		{
			return _kmp.set_sym(n_sym);
		}
		inline Uint16 mod() const
		{
			return _kmp.mod();
		}
		inline Uint16 set_mod(Uint16 n_mod)
		{
			return _kmp.set_mod(n_mod);
		}
		GEN_GETTER_AND_SETTER_BY_CON_REF(kmp);
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
				(ks.kmp());
			std::size_t h1 = std::hash<bool>{}(ks.down());
			return (h0 ^ (h1 << static_cast<std::size_t>(1)));
		}
	};
} // namespace std

#endif		// liborangepower_sdl2_keyboard_classes_hpp
