#ifndef liborangepower_game_stuff_ecs_classes_hpp
#define liborangepower_game_stuff_ecs_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../strings/sconcat_etc.hpp"
#include "../containers/vec2_classes.hpp"
#include "../containers/prev_curr_pair_classes.hpp"
#include "../json_stuff/json_stuff.hpp"

#include <map>
#include <set>
#include <sstream>
#include <concepts>

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
	#define MEMB_LIST_ECS_COMP(X, sep)
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
public:		// variables
	#define MEMB_LIST_ECS_SYS(X, sep) \
	EVAL(MAP(X, sep, \
		did_init, \
		active))

	bool did_init = false;
	containers::PrevCurrPair<bool> active;
public:		// functions
	inline Sys()
	{
		active.back_up_and_update(false);
		active.back_up();
	}
	Sys(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Sys);
	virtual ~Sys() = default;

	operator Json::Value () const;

	virtual std::string kind_str() const;
	virtual void init(Engine* ecs_engine);
	virtual void tick(Engine* ecs_engine);
};
//--------
template<typename Type>
concept HasConstKindStr = requires(Type c)
{
	{ Type::KIND_STR } -> std::same_as<static const std::string>;
};

template<typename Type>
concept EngineDerivedFromComp 
	= std::derived_from<Type, Comp> && HasConstKindStr<Type>;

template<typename Type>
concept EngineDerivedFromSys
	= std::derived_from<Type, Sys> && HasConstKindStr<Type>;

class Engine
{
	friend class Ent;
protected:		// variables
	#define MEMB_AUTOSER_LIST_ECS_ENGINE(X, sep) \
		EVAL(MAP(X, sep, \
			_next_ent_id, \
			_to_destroy_set))
	EntId _next_ent_id = 0;

	EntIdSet _to_destroy_set;

	// All `EntId` are stored as just the keys of `_engine_comp_map`, with
	// no other storage for them.
	EngineCompMap _engine_comp_map;

	SysMap _sys_map;
public:		// functions
	//--------
	Engine();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Engine);
	virtual ~Engine();
	//--------
	operator Json::Value () const;
	//--------
	void _autoser_deserialize(const Json::Value& jv);
	//--------
private:		// functions
	//--------
	template<EngineDerivedFromComp FirstCompType,
		EngineDerivedFromComp... RemCompTypes>
	inline void _inner_ent_deserialize(EntId id,
		const Json::Value& comp_jv, const Json::String& comp_name)
	{
		if (comp_name == FirstCompType::KIND_STR)
		{
			insert_comp(id, comp_name, CompUptr(new
				FirstCompType(comp_jv)));
		}
		// Cut off the search early if we found it, hence the use of the
		// `else if` statement
		else if constexpr (sizeof...(RemCompTypes) > 0)
		{
			_inner_ent_deserialize<RemCompTypes...>(id, comp_jv,
				comp_name);
		}
	}

	template<EngineDerivedFromSys FirstSysType,
		EngineDerivedFromSys... RemSysTypes>
	inline void _inner_sys_deserialize(const Json::Value& sys_jv,
		const Json::String& sys_name)
	{
		if (sys_name == FirstSysType::KIND_STR)
		{
			insert_sys(sys_name, SysUptr(new FirstSysType(sys_jv)));
		}
		// Cut off the search early if we found it, hence the use of the
		// `else if` statement
		else if constexpr (sizeof...(RemSysTypes) > 0)
		{
			_inner_sys_deserialize<RemSysTypes...>(sys_jv, sys_name);
		}
	}
	//--------
public:		// functions
	//--------
	template<EngineDerivedFromComp FirstCompType,
		EngineDerivedFromComp... RemCompTypes>
	void ent_deserialize(const Json::Value& jv)
	{
		_engine_comp_map.clear();
		const auto& ent_name_vec
			= jv["_engine_comp_map"].getMemberNames();
		for (const auto& ent_name: ent_name_vec)
		{
			EntId id = 0;

			std::stringstream sstm;
			sstm << ent_name;
			sstm >> id;

			_inner_create(id);

			const Json::Value& comp_jv = jv["_engine_comp_map"][ent_name];
			const auto& comp_name_vec
				= comp_jv.getMemberNames();

			for (const auto& comp_name: comp_name_vec)
			{
				_inner_ent_deserialize<FirstCompType, RemCompTypes...>
					(id, comp_jv, comp_name);
			}
		}
	}

	template<EngineDerivedFromSys FirstSysType,
		EngineDerivedFromSys... RemSysTypes>
	void sys_deserialize(const Json::Value& jv)
	{
		_sys_map.clear();
		const auto& sys_name_vec = jv["_sys_map"].getMemberNames();
		for (const auto& sys_name: sys_name_vec)
		{
			_inner_sys_deserialize<FirstSysType, RemSysTypes...>
				(jv["_sys_map"][sys_name], sys_name);
		}
	}
	//--------
private:		// functions
	void _inner_create(EntId id);
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
		return *_engine_comp_map.at(id);
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
	GEN_GETTER_BY_VAL(next_ent_id);
	GEN_GETTER_BY_CON_REF(to_destroy_set);
	GEN_GETTER_BY_CON_REF(engine_comp_map);
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
