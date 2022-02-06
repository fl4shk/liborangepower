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
//class EntId final
//{
//public:		// types
//	class CtorArgs final
//	{
//	public:		// variables
//		int file_num;
//		integer_types::u64 val;
//	};
//public:		// variables
//	int file_num;
//	integer_types::u64 val;
//public:		// functions
//	constexpr inline EntId();
//	constexpr inline EntId(const CtorArgs& ctor_args)
//		: file_num(ctor_args.file_num), val(ctor_args.val)
//	{
//	}
//	constexpr inline EntId(int s_file_num, integer_types::u64 s_val)
//		: file_num(s_file_num), val(s_val)
//	{
//	}
//	constexpr inline EntId(integer_types::u64 s_val)
//		: file_num(-1), val(s_val)
//	{
//	}
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(EntId);
//
//	constexpr inline EntId operator + (integer_types::u64 other) const
//	{
//		return {.file_num=file_num, .val=val + other};
//	}
//	constexpr inline EntId operator - (integer_types::u64 other) const
//	{
//		return {.file_num=file_num, .val=val - other};
//	}
//	constexpr inline EntId& operator += (integer_types::u64 other)
//	{
//		*this = *this + other;
//		return *this;
//	}
//	constexpr inline EntId& operator -= (integer_types::u64 other)
//	{
//		*this = *this - other;
//		return *this;
//	}
//	constexpr inline EntId& operator ++ ()
//	{
//		*this += 1;
//		return *this;
//	}
//	constexpr inline EntId& operator -- ()
//	{
//		*this -= 1;
//		return *this;
//	}
//
//	constexpr inline auto operator <=> (const EntId& other) const
//		= default;
//	//constexpr inline auto operator <=> (integer_types::u64 other) const
//	//{
//	//	return *this <=> EntId{.file_num=file_num, .val=other};
//	//}
//};
//static constexpr EntId ENT_NULL_ID
//	= {
//		.file_num=-1,
//		.val=static_cast<integer_types::u64>
//			(static_cast<integer_types::i64>(-1))
//	};
//
//constexpr inline EntId::EntId()
//{
//	*this = ENT_NULL_ID;
//}

using EntIdVec = std::vector<EntId>;
using EntIdVec2d = std::vector<EntIdVec>;
using EntIdMap = std::map<std::string, EntIdVec2d>;
using EntIdMapFullIndex = std::pair<std::string, containers::Vec2<size_t>>;
using EntIdSet = std::set<EntId>;

using CompUptr = std::unique_ptr<Comp>;
using CompMap = std::map<std::string, CompUptr>;
using CompMapUptr = std::unique_ptr<CompMap>;

//class EngineCompMapValue final
//{
//public:		// variables
//	int file_num = -1;
//	CompMapUptr comp_map_uptr;
//public:		// functions
//	EngineCompMapValue();
//	EngineCompMapValue(int s_file_num, CompMapUptr&& s_comp_map_uptr);
//	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(EngineCompMapValue);
//	~EngineCompMapValue();
//};
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
public:		// functions
	inline Ent(Engine* s_engine=nullptr, EntId s_id=ENT_NULL_ID)
		: _engine(s_engine), _id(s_id)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Ent);
	~Ent() = default;

	CompMap& comp_map() const;

	inline bool insert_comp(const std::string& key, CompUptr&& comp) const;
	inline bool insert_or_replace_comp(const std::string& key,
		CompUptr&& comp) const;
	inline size_t erase_comp(const std::string& key) const;

	GEN_GETTER_AND_SETTER_BY_VAL(id);
	GEN_GETTER_AND_SETTER_BY_VAL(engine);
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
	{
		game_mode_active.back_up_and_update(false);
		game_mode_active.back_up();
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
template<typename Type>
concept EngineDerivedFromComp 
	= json::IsValidFromJvFactoryType<Type, Comp>;

template<typename Type>
concept EngineDerivedFromSys
	= json::IsValidFromJvFactoryType<Type, Sys>;

class Engine
{
	friend class Ent;
public:		// constants
	static constexpr size_t
		DEFAULT_NUM_FILES = 9;
protected:		// auto-serialized variables
	#define MEMB_AUTOSER_LIST_ECS_ENGINE(X) \
		X(_next_ent_id_vec) \
		X(_to_destroy_set_vec) \

	std::vector<EntId> _next_ent_id_vec;

	std::vector<EntIdSet> _to_destroy_set_vec;
protected:		// non-auto-serialized serialized variables
	size_t _num_files = DEFAULT_NUM_FILES;

	// All `EntId` are stored as just the keys of `_engine_comp_map`, with
	// no other storage for them.
	std::vector<EngineCompMap> _engine_comp_map_vec;

	SysMap _sys_map;
private:		// variables
	json::FromJvFactory<Comp>::FuncMap _comp_deser_func_map;
	//json::FromJvFactory<Sys>::FuncMap _sys_deser_func_map;
public:		// variables
	int curr_file_num = 0;
public:		// functions
	//--------
	Engine(size_t s_num_files=DEFAULT_NUM_FILES);
	//GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Engine);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Engine);
	virtual ~Engine();
	//--------
	operator Json::Value () const;
	//--------
	inline void deserialize(const Json::Value& jv)
	{
		_autoser_deserialize(jv);
		_ent_deserialize(jv);
		//_sys_deserialize(jv);
	}
	//--------
	template<EngineDerivedFromComp FirstCompType,
		EngineDerivedFromComp... RemCompTypes>
	void init_comp_deserialize()
	{
		_comp_deser_func_map 
			= json::FromJvFactory<Comp>::gen_func_map
				<FirstCompType, RemCompTypes...>();
	}

	//template<EngineDerivedFromSys FirstSysType,
	//	EngineDerivedFromSys... RemSysTypes>
	//void init_sys_deserialize()
	//{
	//	_sys_deser_func_map 
	//		= json::FromJvFactory<Sys>::gen_func_map
	//			<FirstSysType, RemSysTypes...>();
	//}
	//--------
private:		// functions
	//--------
	void _autoser_deserialize(const Json::Value& jv);

	//template<EngineDerivedFromComp FirstCompType,
	//	EngineDerivedFromComp... RemCompTypes>
	void _ent_deserialize(const Json::Value& jv);

	////template<EngineDerivedFromSys FirstSysType,
	////	EngineDerivedFromSys... RemSysTypes>
	//void _sys_deserialize(const Json::Value& jv);
	//--------
	void _inner_create(EntId id);
	//--------
public:		// functions
	EntId create();
	inline void sched_destroy(EntId id)
	{
		_to_destroy_set.insert(id);
	}
	// Destroy now
	void destroy(EntId id);
	void destroy();
	//--------
	template<typename... ArgTypes>
	inline EntIdVec ent_id_vec_from_keys_any_v(ArgTypes&&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_vec_from_keys_any(key_set);
	}
	EntIdVec ent_id_vec_from_keys_any(const StrKeySet& key_set)
		const;

	inline EntIdSet ent_id_set_from_keys_any_v(auto&&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_set_from_keys_any(key_set);
	}
	EntIdSet ent_id_set_from_keys_any(const StrKeySet& key_set) const;

	inline EntIdVec ent_id_vec_from_keys_all_v(auto&&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_vec_from_keys_all(key_set);
	}
	EntIdVec ent_id_vec_from_keys_all(const StrKeySet& key_set)
		const;

	inline EntIdSet ent_id_set_from_keys_all_v(auto&&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_set_from_keys_all(key_set);
	}
	EntIdSet ent_id_set_from_keys_all(const StrKeySet& key_set) const;
	//--------
	inline Ent ent_at(EntId id)
	{
		return Ent(this, id);
	}
	inline CompMap& comp_map(EntId id) const
	{
		return *engine_comp_map().at(id);
	}

	inline CompUptr& comp_at(EntId id, const std::string& key) const
	{
		return comp_map(id).at(key);
	}
	template<EngineDerivedFromComp Type>
	inline CompUptr& comp_at(EntId id) const
	{
		return comp_map(id).at(Type::KIND_STR);
	}
	template<EngineDerivedFromComp Type>
	inline Type* casted_comp_at(EntId id, const std::string& key)
		const
	{
		return static_cast<Type*>(comp_at(id, key).get());
	}
	template<EngineDerivedFromComp Type>
	inline Type* casted_comp_at(EntId id) const
	{
		return casted_comp_at<Type>(id, Type::KIND_STR);
	}

	bool insert_comp(EntId id, const std::string& key, CompUptr&& comp);
	inline bool insert_comp(EntId id, CompUptr&& comp)
	{
		const std::string& KIND_STR = comp->kind_str();
		return insert_comp(id, KIND_STR, std::move(comp));
	}
	bool insert_or_replace_comp(EntId id, const std::string& key,
		CompUptr&& comp);
	inline bool insert_or_replace_comp(EntId id, CompUptr&& comp)
	{
		const std::string& KIND_STR = comp->kind_str();
		return insert_or_replace_comp(id, KIND_STR, std::move(comp));
	}
	size_t erase_comp(EntId id, const std::string& key);
	template<EngineDerivedFromComp Type>
	inline size_t erase_comp(EntId id)
	{
		return erase_comp(id, Type::KIND_STR);
	}

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
	template<EngineDerivedFromSys Type>
	inline size_t erase_sys()
	{
		return erase_sys(Type::KIND_STR);
	}
	//--------
	inline bool has_ent_with_comp(EntId id, const std::string& key)
		const
	{
		return (engine_comp_map().contains(id)
			&& comp_map(id).contains(key));
	}
	template<EngineDerivedFromComp Type>
	inline bool has_ent_with_comp(EntId id) const
	{
		return has_ent_with_comp(id, Type::KIND_STR);
	}
	//--------
	void tick();
	//--------
	inline EntId& next_ent_id()
	{
		return _next_ent_id_vec.at(curr_file_num);
	}
	inline EntId next_ent_id() const
	{
		return _next_ent_id_vec.at(curr_file_num);
	}

	inline EntIdSet& to_destroy_set()
	{
		return _to_destroy_set_vec.at(curr_file_num);
	}
	inline const EntIdSet& to_destroy_set() const
	{
		return _to_destroy_set_vec.at(curr_file_num);
	}

	inline EngineCompMap& engine_comp_map()
	{
		return _engine_comp_map_vec.at(curr_file_num);
	}
	inline const EngineCompMap& engine_comp_map() const
	{
		return _engine_comp_map_vec.at(curr_file_num);
	}
	//--------
	GEN_GETTER_BY_VAL(next_ent_id_vec);
	GEN_GETTER_BY_CON_REF(to_destroy_set_vec);
	GEN_GETTER_BY_VAL(num_files);
	GEN_GETTER_BY_CON_REF(engine_comp_map_vec);
	GEN_GETTER_BY_CON_REF(sys_map);
	//--------
};
//--------
inline bool Ent::insert_comp(const std::string& key, CompUptr&& comp) const
{
	return _engine->insert_comp(id(), key, std::move(comp));
}
inline bool Ent::insert_or_replace_comp(const std::string& key,
	CompUptr&& comp) const
{
	return _engine->insert_or_replace_comp(id(), key, std::move(comp));
}
inline size_t Ent::erase_comp(const std::string& key) const
{
	return _engine->erase_comp(id(), key);
}
//--------
} // namespace ecs
} // namespace game
} // namespace liborangepower

#endif		// liborangepower_game_stuff_ecs_classes_hpp
