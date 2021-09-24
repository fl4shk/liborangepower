#ifndef liborangepower_game_stuff_ecs_classes_hpp
#define liborangepower_game_stuff_ecs_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../strings/sconcat_etc.hpp"
#include "../containers/vec2_classes.hpp"

#include <map>
#include <set>
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
public:		// functions
	Comp() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Comp);
	virtual ~Comp() = default;

	// This is used as the key for individual `CompMap` elements of an
	// `Ent`.
	virtual std::string kind_str() const;
};
//--------
class Sys
{
public:		// functions
	Sys() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Sys);
	virtual ~Sys() = default;

	virtual std::string kind_str() const;
	virtual void tick(Engine* ecs_engine);
};
//--------
class Engine
{
	friend class Ent;
protected:		// variables
	EntId _next_ent_id = 0;

	EntIdSet _to_destroy_set;

	EngineCompMap _engine_comp_map;

	SysMap _sys_map;
public:		// functions
	//--------
	Engine();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Engine);
	virtual ~Engine();
	//--------
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

	template<typename... ArgTypes>
	inline EntIdSet ent_id_set_from_keys_any_v(ArgTypes&&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_set_from_keys_any(key_set);
	}
	EntIdSet ent_id_set_from_keys_any(const StrKeySet& key_set) const;

	template<typename... ArgTypes>
	inline EntIdVec ent_id_vec_from_keys_all_v(ArgTypes&&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_vec_from_keys_all(key_set);
	}
	EntIdVec ent_id_vec_from_keys_all(const StrKeySet& key_set)
		const;

	template<typename... ArgTypes>
	inline EntIdSet ent_id_set_from_keys_all_v(ArgTypes&&... args)
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
	template<typename Type>
	inline CompUptr& comp_at(EntId id) const
	{
		return comp_map(id).at(Type::KIND_STR);
	}
	template<typename Type>
	inline Type* casted_comp_at(EntId id, const std::string& key)
		const
	{
		return static_cast<Type*>(comp_at(id, key).get());
	}
	template<typename Type>
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
	template<typename Type>
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
	template<typename Type>
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
	template<typename Type>
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
