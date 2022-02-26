#ifndef liborangepower_game_stuff_engine_key_status_class_hpp
#define liborangepower_game_stuff_engine_key_status_class_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"
#include "../containers/prev_curr_pair_classes.hpp"

namespace liborangepower
{

using liborangepower::containers::PrevCurrPair;

namespace game
{

class EngineKeyStatus final
{
public:		// types
	using StateVec = std::vector<PrevCurrPair<bool>>;
	using StateVecSizeT = typename StateVec::size_type;
private:		// variables
	//std::map<KeyKind, PrevCurrPair<bool>> state_map;
	StateVec _state_vec;
public:		// functions
	inline EngineKeyStatus() = default;
	EngineKeyStatus(StateVecSizeT state_vec_size)
		: _state_vec(state_vec_size, PrevCurrPair<bool>(false, false))
	{
		//for (StateVecSizeT i=0; i<state_vec_size; ++i)
		//{
		//	//_state_vec[key_kind] = PrevCurrPair<bool>();
		//	//_state_vec.at(key_kind)() = false;
		//	//_state_vec.at(key_kind).back_up();
		//}
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(EngineKeyStatus);
	inline ~EngineKeyStatus() = default;

	inline PrevCurrPair<bool>& at(const auto& key_kind)
	{
		return _state_vec.at(static_cast<StateVecSizeT>(key_kind));
	}
	inline const PrevCurrPair<bool>& at(const auto& key_kind) const
	{
		return _state_vec.at(static_cast<StateVecSizeT>(key_kind));
	}
	//--------
	inline bool key_up_prev(const auto& key_kind) const
	{
		return !at(key_kind).prev();
	}
	inline bool key_down_prev(const auto& key_kind) const
	{
		return at(key_kind).prev();
	}

	inline bool key_up_now(const auto& key_kind) const
	{
		return !at(key_kind)();
	}
	inline bool key_down_now(const auto& key_kind) const
	{
		return at(key_kind)();
	}

	inline bool key_just_went_up(const auto& key_kind) const
	{
		//return (at(key_kind).prev() && !at(key_kind)());
		return (key_down_prev(key_kind) && key_up_now(key_kind));
	}
	inline bool key_just_went_down(const auto& key_kind) const
	{
		//return (!at(key_kind).prev() && at(key_kind)());
		return (key_up_prev(key_kind) && key_down_now(key_kind));
	}
	//--------
public:		// types
	template<typename T, typename... RemTs>
	using KeySet = std::set<T, RemTs...>;
public:		// functions
	//--------
	template<typename T, typename... RemTs>
	static inline bool generic_key_set_func
		(const KeySet<T, RemTs...>& key_set,
		const std::function<bool(const T&)>& func)
	{
		for (const auto& key_kind: key_set)
		{
			if (!func(self, key_kind))
			{
				return false;
			}
		}
		return true;
	}
	template<typename T, typename... RemTs>
	inline bool key_set_up_prev(const KeySet<T, RemTs...>& key_set) const
	{
		return generic_key_set_func(key_set,
			std::bind(&EngineKeyStatus::key_up_prev, this));
	}
	template<typename T, typename... RemTs>
	inline bool key_set_down_prev(const KeySet<T, RemTs...>& key_set) const
	{
		return generic_key_set_func(key_set,
			std::bind(&EngineKeyStatus::key_down_prev, this));
	}

	template<typename T, typename... RemTs>
	inline bool key_set_up_now(const KeySet<T, RemTs...>& key_set) const
	{
		return generic_key_set_func(key_set,
			std::bind(&EngineKeyStatus::key_up_now, this));
	}
	template<typename T, typename... RemTs>
	inline bool key_set_down_now(const KeySet<T, RemTs...>& key_set) const
	{
		return generic_key_set_func(key_set,
			std::bind(&EngineKeyStatus::key_down_now, this));
	}

	template<typename T, typename... RemTs>
	inline bool key_set_jw_down_and_up_now
		(const KeySet<T, RemTs...>& key_down_set,
		const KeySet<T, RemTs...>& key_up_set) const
	{
	}

	template<typename T, typename... RemTs>
	inline bool key_set_just_went_up(const KeySet<T, RemTs...>& key_set)
		const
	{
		//for (const auto& key_kind: key_set)
		//{
		//	if (!(at(key_kind).prev() && (!at(key_kind)())))
		//	{
		//		return false;
		//	}
		//}
		//return true;
		return generic_key_set_func(key_set,
			std::bind(&EngineKeyStatus::key_just_went_up, this));
	}
	template<typename T, typename... RemTs>
	inline bool key_set_just_went_down(const KeySet<T, RemTs...>& key_set)
		const
	{
		//for (const auto& key_kind: grp)
		//{
		//	if (!((!at(key_kind).prev()) && at(key_kind)()))
		//	{
		//		return false;
		//	}
		//}
		//return true;
		return generic_key_set_func(key_set,
			std::bind(&EngineKeyStatus::key_just_went_down, this));
	}
	//--------
	inline bool any_key_just_went_up() const
	{
		for (const auto& item: _state_vec)
		{
			if (item.prev() && (!item()))
			{
				return true;
			}
		}
		return false;
	}
	inline bool any_key_just_went_down() const
	{
		for (const auto& item: _state_vec)
		{
			if ((!item.prev()) && item())
			{
				return true;
			}
		}
		return false;
	}
	inline bool has_changed() const
	{
		for (const auto& item: _state_vec)
		{
			if (item.has_changed())
			{
				return true;
			}
		}
		return false;
	}
	//--------
	template<typename KeyKind, typename KeycT, typename KeyStatusT>
	inline void update
		(const std::map<KeycT, KeyStatusT>& key_status_map,
		const std::map<KeyKind, KeycT>& keyc_map)
	{
		//auto update_key_status
		//	= [](PrevCurrPair<bool>& key_status_down, SDL_Keycode sym)
		//	-> void
		//{
		//	if (key_status_map.contains(sym))
		//	{
		//		//key_status_down() = _key_status_map.at(sym).down.prev();
		//		key_status_down.back_up_and_update
		//			(key_status_map.at(sym).down());
		//	}
		//};
		for (const auto& pair: keyc_map)
		//for (StateVecSizeT key_kind=0;
		//	key_kind<keyc_vec.size();
		//	++key_kind)
		{
			const auto& key_kind = pair.first;
			const auto& sym = pair.second;

			//const auto& sym = keyc_vec.at(key_kind);

			if (key_status_map.contains(sym))
			{
				at(key_kind).back_up_and_update
					(key_status_map.at(sym).down());
			}
		}
	}
	//--------
	GEN_GETTER_BY_CON_REF(state_vec);
	//--------
}; 

} // namespace game
} // namespace liborangepower

#endif		// liborangepower_game_stuff_engine_key_status_class_hpp
