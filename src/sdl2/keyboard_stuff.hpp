#ifndef liborangepower_sdl2_keyboard_stuff_hpp
#define liborangepower_sdl2_keyboard_stuff_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"
#include "../containers/prev_curr_pair_classes.hpp"

#include <functional>
#include <string>
#include <map>
#include <concepts>

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_keyboard.h>

namespace liborangepower
{

using liborangepower::containers::PrevCurrPair;

namespace sdl
{

inline std::string get_key_name(SDL_Keycode sym)
{
	return std::string(SDL_GetKeyName(sym));
}

class KeycModPair final
{
private:		// variables
	SDL_Keycode _sym;
	Uint16 _mod;
public:		// functions
	inline KeycModPair() = default;
	inline KeycModPair(SDL_Keycode s_sym, Uint16 s_mod)
		: _sym(s_sym), _mod(s_mod)
	{
	}
	inline ~KeycModPair() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(KeycModPair);

	//inline bool operator < (const KeycModPair& to_cmp) const
	//{
	//	if (_sym < to_cmp._sym)
	//	{
	//		return true;
	//	}
	//	else if (_sym == to_cmp._sym)
	//	{
	//		return (_mod < to_cmp._mod);
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}
	//inline bool operator == (const KeycModPair& to_cmp) const
	//{
	//	return ((_sym == to_cmp._sym) && (_mod == to_cmp._mod));
	//}
	inline auto operator <=> (const KeycModPair& to_cmp) const = default;

	GEN_GETTER_AND_SETTER_BY_VAL(sym);
	GEN_GETTER_AND_SETTER_BY_VAL(mod);
};

class KeyStatus
{
private:		// variables
	KeycModPair _kmp;
public:		// variables
	PrevCurrPair<bool> down;
public:		// functions
	inline KeyStatus() = default;
	inline KeyStatus(const KeycModPair& s_kmp, bool s_down_curr=false)
		: _kmp(s_kmp)
	{
		down() = false;
		down.back_up();
		down() = s_down_curr;
	}
	inline KeyStatus(SDL_Keycode s_sym, Uint16 s_mod,
		bool s_down_curr=false)
		: _kmp(s_sym, s_mod)
	{
		down() = false;
		down.back_up();
		down() = s_down_curr;
	}
	inline ~KeyStatus() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(KeyStatus);

	//inline bool operator < (const KeyStatus& to_cmp) const
	//{
	//	if (_kmp < to_cmp._kmp)
	//	{
	//		return true;
	//	}
	//	else if (_kmp == to_cmp._kmp)
	//	{
	//		return (down < to_cmp.down);
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}
	//inline bool operator == (const KeyStatus& to_cmp) const
	//{
	//	return ((_kmp == to_cmp._kmp) && (down == to_cmp.down));
	//}
	inline auto operator <=> (const KeyStatus& to_cmp) const = default;

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
};

using KeyStatusMap = std::map<SDL_Keycode, KeyStatus>;

template<typename KeyKind>
using EngineKeycMap = std::map<KeyKind, SDL_Keycode>;
//using KeycVec = std::vector<SDL_Keycode>;


// Set `perf_total_back_up` to `true` before the loop that polls SDL
// events.
inline bool handle_key_events(SDL_Event& e, KeyStatusMap& key_status_map,
	bool& perf_total_back_up)
{
	if (perf_total_back_up)
	{
		for (const auto& item: key_status_map)
		{
			//if (item.first == SDLK_s)
			//{
			//	fprintf(stdout, "handle_key_events() before: %i %i\n",
			//		key_status_map.at(item.first).down.prev(),
			//		key_status_map.at(item.first).down());
			//}

			key_status_map.at(item.first).down.back_up();

			//if (item.first == SDLK_s)
			//{
			//	fprintf(stdout, "handle_key_events() after: %i %i\n",
			//		key_status_map.at(item.first).down.prev(),
			//		key_status_map.at(item.first).down());
			//}
		}
	}

	perf_total_back_up = false;

	if ((e.type == SDL_KEYDOWN) || (e.type == SDL_KEYUP))
	{
		const auto& keysym = e.key.keysym;
		const KeycModPair kmp(keysym.sym, keysym.mod);

		if (!key_status_map.contains(keysym.sym))
		{
			key_status_map[keysym.sym] = KeyStatus(kmp);
			key_status_map.at(keysym.sym).down() = false;
			key_status_map.at(keysym.sym).down.back_up();
		}
		//else
		//{
		//	key_status_map.at(keysym.sym).down.back_up();
		//}

		key_status_map.at(keysym.sym).set_kmp(kmp);
		key_status_map.at(keysym.sym).down() = (e.type == SDL_KEYDOWN);

		return true;
	}

	return false;
}

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

#endif		// liborangepower_sdl2_keyboard_stuff_hpp
