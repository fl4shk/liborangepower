#ifndef liborangepower_game_stuff_engine_key_status_class_hpp
#define liborangepower_game_stuff_engine_key_status_class_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"
#include "../containers/prev_curr_pair_classes.hpp"

namespace liborangepower {
//--------
using liborangepower::containers::PrevCurrPair;
//--------
namespace game {
//--------
class EngineKeyStatus final {
public:		// types
	using State = PrevCurrPair<bool>;
	using StateDarr = std::vector<State>;
	using StateDarrSizeT = typename StateDarr::size_type;
private:		// variables
	//std::map<KeyKind, State> state_map;
	StateDarr _state_darr;
public:		// functions
	inline EngineKeyStatus() = default;
	inline EngineKeyStatus(StateDarrSizeT state_vec_size)
		: _state_darr(state_vec_size, State(false, false)) {
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(EngineKeyStatus);
	inline ~EngineKeyStatus() = default;

	inline State& at(const auto& key_kind) {
		return _state_darr.at(static_cast<StateDarrSizeT>(key_kind));
	}
	inline const State& at(const auto& key_kind) const {
		return _state_darr.at(static_cast<StateDarrSizeT>(key_kind));
	}
	//--------
	inline bool key_up_prev(const auto& key_kind) const {
		return !at(key_kind).prev();
	}
	inline bool key_down_prev(const auto& key_kind) const {
		return at(key_kind).prev();
	}

	inline bool key_up_now(const auto& key_kind) const {
		return !at(key_kind)();
	}
	inline bool key_down_now(const auto& key_kind) const {
		return at(key_kind)();
	}

	inline bool key_just_went_up(const auto& key_kind) const {
		//return (at(key_kind).prev() && !at(key_kind)());
		return (key_down_prev(key_kind) && key_up_now(key_kind));
	}
	inline bool key_just_went_down(const auto& key_kind) const {
		//return (!at(key_kind).prev() && at(key_kind)());
		return (key_up_prev(key_kind) && key_down_now(key_kind));
	}
	//--------
public:		// types
	//--------
	template<typename T>
	using KeyUset = std::unordered_set<T>;

	template<typename T, typename... RemTs>
	using KeyUsetR = std::unordered_set<T, RemTs...>;
	//--------
public:		// functions
	//--------
	template<typename T>
	static inline bool generic_key_uset_func(
		const KeyUset<T>& key_uset,
		const std::function<bool(const T&)>& func
	) {
		for (const auto& key_kind: key_uset) {
			if (!func(key_kind)) {
				return false;
			}
		}
		return true;
	}
	template<typename T>
	inline bool key_uset_up_prev(const KeyUset<T>& key_uset) const {
		return generic_key_uset_func<T>(key_uset,
			//std::bind(&EngineKeyStatus::key_up_prev<T>, this)
			[this](const T& key_kind) -> bool {
				return key_up_prev<T>(key_kind);
			});
	}
	template<typename T>
	inline bool key_uset_down_prev(const KeyUset<T>& key_uset) const {
		return generic_key_uset_func<T>(key_uset,
			//std::bind(&EngineKeyStatus::key_down_prev<T>, this)
			[this](const T& key_kind) -> bool {
				return key_down_prev<T>(key_kind);
			});
	}

	template<typename T>
	inline bool key_uset_up_now(const KeyUset<T>& key_uset) const {
		return generic_key_uset_func<T>(key_uset,
			//std::bind(&EngineKeyStatus::key_up_now<T>, this)
			[this](const T& key_kind) -> bool {
				return key_up_now<T>(key_kind);
			});
	}
	template<typename T>
	inline bool key_uset_down_now(const KeyUset<T>& key_uset) const {
		return generic_key_uset_func<T>(key_uset,
			//std::bind(&EngineKeyStatus::key_down_now<T>, this)
			[this](const T& key_kind) -> bool {
				return key_down_now<T>(key_kind);
			});
	}

	//template<typename T, typename... RemTs>
	//inline bool key_uset_jw_down_and_up_now(
	//	const KeyUset<T, RemTs...>& key_down_set,
	//	const KeyUset<T, RemTs...>& key_up_set
	//) const {
	//	return (key_uset_just_went_down(key_down_set)
	//		&& key_uset_up_now(key_up_set));
	//}
	//template<typename T, typename... RemTs>
	//inline bool key_uset_jw_up_and_down_now(
	//	const KeyUset<T, RemTs...>& key_down_set,
	//	const KeyUset<T, RemTs...>& key_up_set
	//) const {
	//	return (key_uset_down_now(key_down_set)
	//		&& key_uset_just_went_up(key_up_set));
	//}

	template<typename T>
	inline bool key_uset_just_went_up(
		const KeyUset<T>& key_uset
	) const {
		//for (const auto& key_kind: key_uset) {
		//	if (!(at(key_kind).prev() && (!at(key_kind)()))) {
		//		return false;
		//	}
		//}
		//return true;
		return generic_key_uset_func(key_uset,
			//std::bind(&EngineKeyStatus::key_just_went_up<T>,
			//	this)
			[this](const T& key_kind) -> bool {
				return key_just_went_up<T>(key_kind);
			});
	}
	template<typename T>
	inline bool key_uset_just_went_down(
		const KeyUset<T>& key_uset
	) const {
		//for (const auto& key_kind: grp) {
		//	if (!((!at(key_kind).prev()) && at(key_kind)())) {
		//		return false;
		//	}
		//}
		//return true;
		return generic_key_uset_func(key_uset,
			//std::bind(&EngineKeyStatus::key_just_went_down<T>, this)
			[this](const T& key_kind) -> bool {
				return key_just_went_down<T>(key_kind);
			});
	}


	template<typename T, typename... RemTs>
	static inline bool generic_key_uset_r_func(
		const KeyUsetR<T, RemTs...>& key_uset_r,
		const std::function<bool(const T&)>& func
	) {
		for (const auto& key_kind: key_uset_r) {
			if (!func(key_kind)) {
				return false;
			}
		}
		return true;
	}
	template<typename T, typename... RemTs>
	inline bool key_uset_r_up_prev(
		const KeyUsetR<T, RemTs...>& key_uset_r
	) const {
		return generic_key_uset_r_func(key_uset_r,
			//std::bind(&EngineKeyStatus::key_up_prev<T>, this)
			[this](const T& key_kind) -> bool {
				return key_up_prev<T>(key_kind);
			});
	}
	template<typename T, typename... RemTs>
	inline bool key_uset_r_down_prev(
		const KeyUsetR<T, RemTs...>& key_uset_r
	) const {
		return generic_key_uset_r_func(key_uset_r,
			//std::bind(&EngineKeyStatus::key_down_prev<T>, this)
			[this](const T& key_kind) -> bool {
				return key_down_prev<T>(key_kind);
			});
	}

	template<typename T, typename... RemTs>
	inline bool key_uset_r_up_now(
		const KeyUsetR<T, RemTs...>& key_uset_r
	) const {
		return generic_key_uset_r_func(key_uset_r,
			//std::bind(&EngineKeyStatus::key_up_now<T>, this)
			[this](const T& key_kind) -> bool {
				return key_up_now<T>(key_kind);
			});
	}
	template<typename T, typename... RemTs>
	inline bool key_uset_r_down_now(
		const KeyUsetR<T, RemTs...>& key_uset_r
	) const {
		return generic_key_uset_r_func(key_uset_r,
			//std::bind(&EngineKeyStatus::key_down_now<T>, this)
			[this](const T& key_kind) -> bool {
				return key_down_now<T>(key_kind);
			});
	}
	template<typename T, typename... RemTs>
	inline bool key_uset_r_just_went_up(
		const KeyUsetR<T, RemTs...>& key_uset_r
	) const {
		//for (const auto& key_kind: key_uset_r) {
		//	if (!(at(key_kind).prev() && (!at(key_kind)()))) {
		//		return false;
		//	}
		//}
		//return true;
		return generic_key_uset_r_func(key_uset_r,
			//std::bind(&EngineKeyStatus::key_just_went_up<T>, this)
			[this](const T& key_kind) -> bool {
				return key_just_went_up<T>(key_kind);
			});
	}
	template<typename T, typename... RemTs>
	inline bool key_uset_r_just_went_down(
		const KeyUsetR<T, RemTs...>& key_uset_r
	) const {
		//for (const auto& key_kind: grp) {
		//	if (!((!at(key_kind).prev()) && at(key_kind)())) {
		//		return false;
		//	}
		//}
		//return true;
		return generic_key_uset_r_func(key_uset_r,
			//std::bind(&EngineKeyStatus::key_just_went_down<T>, this)
			[this](const T& key_kind) -> bool {
				return key_just_went_down<T>(key_kind);
			});
	}
	//--------
	inline bool generic_any_key_func(
		const std::function<bool(const State&)> func
	) const {
		for (const auto& item: _state_darr) {
			if (func(item)) {
				return true;
			}
		}
		return false;
	}
	inline bool any_key_just_went_up() const {
		return generic_any_key_func
			([](const State& item) -> bool
				{ return (item.prev() && !item()); });
	}
	inline bool any_key_just_went_down() const {
		return generic_any_key_func
			([](const State& item) -> bool
				{ return (!item.prev() && item()); });
	}
	inline bool has_changed() const {
		return generic_any_key_func
			([](const State& item) -> bool
				{ return item.has_changed(); });
	}
	//--------
	// mainly intended for use with SDL
	template<typename KeyKind, typename KeycT, typename KeyStatusT>
	inline void update(
		const std::unordered_map<KeycT, KeyStatusT>& key_status_umap,
		const std::unordered_map<KeyKind, KeycT>& keyc_umap
	) {
		for (const auto& pair: keyc_umap) {
			const auto& key_kind = pair.first;
			const auto& sym = pair.second;

			//const auto& sym = keyc_darr.at(key_kind);

			if (key_status_umap.contains(sym)) {
				at(key_kind).back_up_and_update
					(key_status_umap.at(sym).down());
			}
		}
	}
	//--------
	GEN_GETTER_BY_CON_REF(state_darr);
	//--------
}; 

} // namespace game
} // namespace liborangepower

#endif		// liborangepower_game_stuff_engine_key_status_class_hpp
