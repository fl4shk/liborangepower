#ifndef liborangepower_game_stuff_ecs_classes_hpp
#define liborangepower_game_stuff_ecs_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../strings/sconcat_etc.hpp"
#include "../containers/vec2_classes.hpp"
#include "../containers/prev_curr_pair_classes.hpp"
#include "../json_stuff/json_stuff.hpp"
#include "../json_stuff/from_jv_factory_stuff.hpp"

#include <map>
#include <set>
#include <sstream>

namespace liborangepower
{
namespace game
{
namespace ecs
{
//--------
class Ent;
class Comp;
class Sys;
class Engine;

using EntId = integer_types::u64;
static constexpr EntId ENT_NULL_ID
	= static_cast<EntId>(static_cast<integer_types::i64>(-1));

using EntIdVec = std::vector<EntId>;
using EntIdVec2d = std::vector<EntIdVec>;
using EntIdMap = std::map<std::string, EntIdVec2d>;
using EntIdMapFullIndex = std::pair<std::string, containers::Vec2<size_t>>;
using EntIdSet = std::set<EntId>;

using CompUptr = std::unique_ptr<Comp>;
using CompMap = std::map<std::string, CompUptr>;
using CompMapUptr = std::unique_ptr<CompMap>;

using EngineCompMap = std::map<EntId, CompMapUptr>;

using SysUptr = std::unique_ptr<Sys>;
using SysMap = std::map<std::string, SysUptr>;

using StrKeySet = std::set<std::string>;
//--------
class Ent final
{
private:		// variables
	Engine* _engine = nullptr;
	EntId _id = ENT_NULL_ID;
	int _file_num = 0;
public:		// functions
	inline Ent(Engine* s_engine, EntId s_id, int s_file_num);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Ent);
	~Ent() = default;

	inline CompMap& comp_map() const;

	inline bool insert_comp(const std::string& key, CompUptr&& comp) const;
	inline bool insert_or_replace_comp(const std::string& key,
		CompUptr&& comp) const;
	inline size_t erase_comp(const std::string& key) const;

	GEN_GETTER_AND_SETTER_BY_VAL(id);
	GEN_GETTER_AND_SETTER_BY_VAL(engine);
	GEN_GETTER_AND_SETTER_BY_VAL(file_num);
};
//--------
class Comp
{
public:		// misc.
	#define MEMB_LIST_ECS_COMP(X)
public:		// functions
	Comp() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Comp);
	virtual ~Comp() = default;

	// This is used as the key for individual `CompMap` elements of an
	// `Ent`.
	virtual std::string kind_str() const;

	virtual operator Json::Value () const;
};
//--------
class Sys
{
public:		// serialization stuff
	#define MEMB_LIST_ECS_SYS(X) \
		X(_did_init) \
		X(game_mode_active) \

private:		// variables
	bool _did_init = false;
public:		// variables
	containers::PrevCurrPair<bool> game_mode_active;
public:		// functions
	inline Sys()
		: game_mode_active(false, false)
	{
	}
	//Sys(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Sys);
	virtual ~Sys() = default;

	virtual std::string kind_str() const;

	//operator Json::Value () const;

	void prep_init();
	virtual void init(Engine* ecs_engine);
	virtual void tick(Engine* ecs_engine);

	GEN_GETTER_BY_VAL(did_init);
protected:		// functions
	// The derived class should call this function at the beginning of its
	// `init()` implementation.
	inline void _init_start()
	{
		_did_init = true;
	}
	// Returns true when the derived class should run its unique `tick()`
	// functionality
	bool _tick_helper(Engine* ecs_engine, bool cond);
};
//--------
template<typename T>
concept EngineDerivedFromComp 
	= json::IsValidFromJvFactoryT<T, Comp>;

template<typename T>
concept EngineDerivedFromSys
	= json::IsValidFromJvFactoryT<T, Sys>;

class Engine
{
	friend class Ent;
public:		// constants
	static constexpr size_t
		DEFAULT_NUM_FILES = 9;
	static constexpr int
		USE_CURR_FILE_NUM = -1;
protected:		// auto-serialized variables
	#define MEMB_AUTOSER_LIST_ECS_ENGINE(X) \
		X(_next_ent_id_vec) \
		X(_to_destroy_set_vec) \

	std::vector<EntId> _next_ent_id_vec;

	std::vector<EntIdSet> _to_destroy_set_vec;
protected:		// non-auto-serialized serialized variables
	integer_types::u64 _num_files = DEFAULT_NUM_FILES;

	// All `EntId` are stored as just the keys of `_engine_comp_map`, with
	// no other storage for them.
	std::vector<EngineCompMap> _engine_comp_map_vec;
protected:		// non-serialized variables
	SysMap _sys_map;
private:		// non-serialized variables
	json::FromJvFactory<Comp>::FuncMap _comp_deser_func_map;
	//json::FromJvFactory<Sys>::FuncMap _sys_deser_func_map;
public:		// variables
	int curr_file_num = 0;
public:		// functions
	//--------
	Engine(integer_types::u64 s_num_files=DEFAULT_NUM_FILES);
	//GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Engine);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Engine);
	virtual ~Engine();
	//--------
	operator Json::Value () const;
	//--------
	void deserialize(const Json::Value& jv);
	//{
	//	_autoser_deserialize(jv);
	//	_ent_deserialize(jv);
	//	//_sys_deserialize(jv);
	//}
	//--------
	template<EngineDerivedFromComp FirstCompT,
		EngineDerivedFromComp... RemCompTs>
	void init_comp_deserialize()
	{
		_comp_deser_func_map 
			= json::FromJvFactory<Comp>::gen_func_map
				<FirstCompT, RemCompTs...>();
	}

	//template<EngineDerivedFromSys FirstSysT,
	//	EngineDerivedFromSys... RemSysTs>
	//void init_sys_deserialize()
	//{
	//	_sys_deser_func_map 
	//		= json::FromJvFactory<Sys>::gen_func_map
	//			<FirstSysT, RemSysTs...>();
	//}
	//--------
private:		// functions
	//--------
	void _autoser_deserialize(const Json::Value& jv);

	//template<EngineDerivedFromComp FirstCompT,
	//	EngineDerivedFromComp... RemCompTs>
	void _ent_deserialize(const Json::Value& jv);

	////template<EngineDerivedFromSys FirstSysT,
	////	EngineDerivedFromSys... RemSysTs>
	//void _sys_deserialize(const Json::Value& jv);
	//--------
	void _inner_create(EntId id, int file_num);
	//--------
public:		// functions
	EntId create(int file_num);
	inline EntId create_cfn()
	{
		return create(curr_file_num);
	}

	inline void sched_destroy(EntId id, int file_num)
	{
		to_destroy_set(file_num).insert(id);
	}
	inline void sched_destroy_cfn(EntId id)
	{
		sched_destroy(id, curr_file_num);
	}

	// Destroy now
	void destroy(EntId id, int file_num);
	void destroy(int file_num);

	inline void destroy_cfn(EntId id)
	{
		destroy(id, curr_file_num);
	}
	inline void destroy_cfn()
	{
		destroy(curr_file_num);
	}

	void destroy_all(int file_num);
	inline void destroy_all_cfn()
	{
		destroy_all(USE_CURR_FILE_NUM);
	}
	void destroy_all();
	//--------
	EntIdVec ent_id_vec_from_keys_any(const StrKeySet& key_set,
		int file_num=USE_CURR_FILE_NUM) const;
	inline EntIdVec ent_id_vec_from_keys_any_v(int file_num,
		auto&&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_vec_from_keys_any(key_set, file_num);
	}
	inline EntIdVec ent_id_vec_from_keys_any_cfn_v(auto&&... args)
	{
		return ent_id_vec_from_keys_any_v(curr_file_num, args...);
	}
	//--------
	EntIdSet ent_id_set_from_keys_any(const StrKeySet& key_set,
		int file_num=USE_CURR_FILE_NUM) const;
	inline EntIdSet ent_id_set_from_keys_any_v(int file_num,
		auto&&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_set_from_keys_any(key_set, file_num);
	}
	inline EntIdSet ent_id_set_from_keys_any_cfn_v(auto&&... args)
	{
		return ent_id_set_from_keys_any_v(curr_file_num, args...);
	}
	//--------
	EntIdVec ent_id_vec_from_keys_all(const StrKeySet& key_set,
		int file_num=USE_CURR_FILE_NUM) const;
	inline EntIdVec ent_id_vec_from_keys_all_v(int file_num,
		auto&&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_vec_from_keys_all(key_set, file_num);
	}
	inline EntIdVec ent_id_vec_from_keys_all_cfn_v(auto&&... args)
	{
		return ent_id_vec_from_keys_all_v(curr_file_num, args...);
	}
	//--------
	EntIdSet ent_id_set_from_keys_all(const StrKeySet& key_set,
		int file_num=USE_CURR_FILE_NUM) const;
	inline EntIdSet ent_id_set_from_keys_all_v(int file_num,
		auto&&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_set_from_keys_all(key_set, file_num);
	}
	inline EntIdSet ent_id_set_from_keys_all_cfn_v(auto&&... args)
	{
		return ent_id_set_from_keys_all_v(curr_file_num, args...);
	}
	//--------
	inline Ent ent_at(EntId id, int file_num)
	{
		return Ent(this, id, _sel_file_num(file_num));
	}
	inline Ent ent_at_cfn(EntId id)
	{
		return ent_at(id, curr_file_num);
	}
	//--------
	inline CompMap& comp_map(EntId id, int file_num) const
	{
		return *engine_comp_map(file_num).at(id);
	}

	inline CompMap& comp_map_cfn(EntId id) const
	{
		return comp_map(id, curr_file_num);
	}
	//--------
	inline CompUptr& comp_at(EntId id, const std::string& key,
		int file_num) const
	{
		return comp_map(id, file_num).at(key);
	}
	template<EngineDerivedFromComp T>
	inline CompUptr& comp_at(EntId id, int file_num) const
	{
		return comp_map(id, file_num).at(T::KIND_STR);
	}

	inline CompUptr& comp_at_cfn(EntId id, const std::string& key) const
	{
		return comp_at(id, key, curr_file_num);
	}
	template<EngineDerivedFromComp T>
	inline CompUptr& comp_at_cfn(EntId id) const
	{
		return comp_at<T>(id, curr_file_num);
	}
	//--------
	template<EngineDerivedFromComp T>
	inline T* casted_comp_at(EntId id, const std::string& key,
		int file_num) const
	{
		return static_cast<T*>(comp_at(id, key, file_num).get());
	}
	template<EngineDerivedFromComp T>
	inline T* casted_comp_at(EntId id, int file_num) const
	{
		return casted_comp_at<T>(id, T::KIND_STR, file_num);
	}

	template<EngineDerivedFromComp T>
	inline T* casted_comp_at_cfn(EntId id, const std::string& key) const
	{
		return casted_comp_at<T>(id, key, curr_file_num);
	}
	template<EngineDerivedFromComp T>
	inline T* casted_comp_at_cfn(EntId id) const
	{
		return casted_comp_at<T>(id, curr_file_num);
	}
	//--------
	bool insert_comp(EntId id, const std::string& key, CompUptr&& comp,
		int file_num);
	inline bool insert_comp(EntId id, CompUptr&& comp, int file_num)
	{
		const std::string& KIND_STR = comp->kind_str();
		return insert_comp(id, KIND_STR, std::move(comp), file_num);
	}

	inline bool insert_comp_cfn(EntId id, const std::string& key,
		CompUptr&& comp)
	{
		return insert_comp(id, key, std::move(comp), curr_file_num);
	}
	inline bool insert_comp_cfn(EntId id, CompUptr&& comp)
	{
		return insert_comp(id, std::move(comp), curr_file_num);
	}
	//--------
	bool insert_or_replace_comp(EntId id, const std::string& key,
		CompUptr&& comp, int file_num);
	inline bool insert_or_replace_comp(EntId id, CompUptr&& comp,
		int file_num)
	{
		const std::string& KIND_STR = comp->kind_str();
		return insert_or_replace_comp(id, KIND_STR, std::move(comp),
			file_num);
	}

	inline bool insert_or_replace_comp_cfn(EntId id,
		const std::string& key, CompUptr&& comp)
	{
		return insert_or_replace_comp(id, key, std::move(comp),
			curr_file_num);
	}
	inline bool insert_or_replace_comp_cfn(EntId id, CompUptr&& comp)
	{
		return insert_or_replace_comp(id, std::move(comp), curr_file_num);
	}
	//--------
	size_t erase_comp(EntId id, const std::string& key, int file_num);
	template<EngineDerivedFromComp T>
	inline size_t erase_comp(EntId id, int file_num)
	{
		return erase_comp(id, T::KIND_STR, file_num);
	}

	inline size_t erase_comp_cfn(EntId id, const std::string& key)
	{
		return erase_comp(id, key, curr_file_num);
	}
	template<EngineDerivedFromComp T>
	inline size_t erase_comp_cfn(EntId id)
	{
		return erase_comp<T>(id, curr_file_num);
	}
	//--------
	bool insert_sys(const std::string& key, SysUptr&& sys);
	inline bool insert_sys(SysUptr&& sys)
	{
		const std::string& KIND_STR = sys->kind_str();
		return insert_sys(KIND_STR, std::move(sys));
	}
	bool insert_or_replace_sys(const std::string& key, SysUptr&& sys);
	inline bool insert_or_replace_sys(SysUptr&& sys)
	{
		const std::string& KIND_STR = sys->kind_str();
		return insert_or_replace_sys(KIND_STR, std::move(sys));
	}

	size_t erase_sys(const std::string& key);
	template<EngineDerivedFromSys T>
	inline size_t erase_sys()
	{
		return erase_sys(T::KIND_STR);
	}
	//--------
	inline bool has_ent_with_comp(EntId id, const std::string& key,
		int file_num) const
	{
		return (engine_comp_map(file_num).contains(id)
			&& comp_map(id, file_num).contains(key));
	}
	template<EngineDerivedFromComp T>
	inline bool has_ent_with_comp(EntId id, int file_num) const
	{
		return has_ent_with_comp(id, T::KIND_STR, file_num);
	}

	inline bool has_ent_with_comp_cfn(EntId id, const std::string& key)
		const
	{
		return has_ent_with_comp(id, key, curr_file_num);
	}
	template<EngineDerivedFromComp T>
	inline bool has_ent_with_comp_cfn(EntId id) const
	{
		return has_ent_with_comp<T>(id, curr_file_num);
	}
	//--------
	void tick();
	//--------
	inline EntId& next_ent_id(int file_num)
	{
		return _next_ent_id_vec.at(_sel_file_num(file_num));
	}
	inline const EntId& next_ent_id(int file_num) const
	{
		return _next_ent_id_vec.at(_sel_file_num(file_num));
	}

	inline EntId& next_ent_id_cfn()
	{
		return next_ent_id(curr_file_num);
	}
	inline const EntId& next_ent_id_cfn() const
	{
		return next_ent_id(curr_file_num);
	}
	//--------
	inline EntIdSet& to_destroy_set(int file_num)
	{
		return _to_destroy_set_vec.at(_sel_file_num(file_num));
	}
	inline const EntIdSet& to_destroy_set(int file_num) const
	{
		return _to_destroy_set_vec.at(_sel_file_num(file_num));
	}

	inline EntIdSet& to_destroy_set_cfn()
	{
		return to_destroy_set(curr_file_num);
	}
	inline const EntIdSet& to_destroy_set_cfn() const
	{
		return to_destroy_set(curr_file_num);
	}
	//--------
	inline EngineCompMap& engine_comp_map(int file_num)
	{
		return _engine_comp_map_vec.at(_sel_file_num(file_num));
	}
	inline const EngineCompMap& engine_comp_map(int file_num) const
	{
		return _engine_comp_map_vec.at(_sel_file_num(file_num));
	}

	inline EngineCompMap& engine_comp_map_cfn()
	{
		return engine_comp_map(curr_file_num);
	}
	inline const EngineCompMap& engine_comp_map_cfn() const
	{
		return engine_comp_map(curr_file_num);
	}
	//--------
	GEN_GETTER_BY_VAL(next_ent_id_vec);
	GEN_GETTER_BY_CON_REF(to_destroy_set_vec);
	GEN_GETTER_BY_VAL(num_files);
	GEN_GETTER_BY_CON_REF(engine_comp_map_vec);
	GEN_GETTER_BY_CON_REF(sys_map);
	//--------
private:		// functions
	inline int _sel_file_num(int some_file_num) const
	{
		return (some_file_num == USE_CURR_FILE_NUM)
			? curr_file_num
			: some_file_num;
	}
};
//--------
inline Ent::Ent(Engine* s_engine=nullptr, EntId s_id=ENT_NULL_ID,
	int s_file_num=Engine::USE_CURR_FILE_NUM)
	: _engine(s_engine), _id(s_id), _file_num(s_file_num)
{
}
inline CompMap& Ent::comp_map() const
{
	return _engine->comp_map(id(), file_num());
}
inline bool Ent::insert_comp(const std::string& key, CompUptr&& comp) const
{
	return _engine->insert_comp(id(), key, std::move(comp), file_num());
}
inline bool Ent::insert_or_replace_comp(const std::string& key,
	CompUptr&& comp) const
{
	return _engine->insert_or_replace_comp(id(), key, std::move(comp),
		file_num());
}
inline size_t Ent::erase_comp(const std::string& key) const
{
	return _engine->erase_comp(id(), key, file_num());
}
//--------
} // namespace ecs
} // namespace game
} // namespace liborangepower

#endif		// liborangepower_game_stuff_ecs_classes_hpp
