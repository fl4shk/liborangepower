#ifndef liborangepower_game_stuff_engine_key_status_class_hpp
#define liborangepower_game_stuff_engine_key_status_class_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"
#include "../containers/prev_curr_pair_classes.hpp"

#include <map>

namespace liborangepower
{

using liborangepower::containers::PrevCurrPair;

namespace game
{

class EngineKeyStatus final
{
public:		// types
	using StateVec = std::vector<PrevCurrPair<bool>>;
	using StateVecSizeType = typename StateVec::size_type;
private:		// variables
	//std::map<KeyKind, PrevCurrPair<bool>> state_map;
	StateVec _state_vec;
public:		// functions
	inline EngineKeyStatus() = default;
	EngineKeyStatus(StateVecSizeType state_vec_size)
		: _state_vec(state_vec_size, PrevCurrPair<bool>(false, false))
	{
		//for (StateVecSizeType i=0; i<state_vec_size; ++i)
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
		return _state_vec.at(static_cast<StateVecSizeType>(key_kind));
	}
	inline const PrevCurrPair<bool>& at(const auto& key_kind) const
	{
		return _state_vec.at(static_cast<StateVecSizeType>(key_kind));
	}

	inline bool key_went_up_just_now(const auto& key_kind) const
	{
		return (at(key_kind).prev() && (!at(key_kind)()));
	}
	inline bool key_went_down_just_now(const auto& key_kind) const
	{
		return ((!at(key_kind).prev()) && at(key_kind)());
	}

	inline bool any_key_went_up_just_now() const
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
	inline bool any_key_went_down_just_now() const
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

	template<typename KeyKind, typename KeycType, typename KeyStatusType>
	inline void update
		(const std::map<KeycType, KeyStatusType>& key_status_map,
		const std::map<KeyKind, KeycType>& keyc_map)
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
		//for (StateVecSizeType key_kind=0;
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

	GEN_GETTER_BY_CON_REF(state_vec);
}; 

} // namespace game
} // namespace liborangepower

#endif		// liborangepower_game_stuff_engine_key_status_class_hpp
