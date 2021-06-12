#ifndef liborangepower_game_stuff_ecs_classes_hpp
#define liborangepower_game_stuff_ecs_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../strings/sconcat_etc.hpp"

#include <map>
#include <set>

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
	= static_cast<EntId>(static_cast<i64>(-1));

using EntIdVec = std::vector<EntId>;
using EntIdVec2d = std::vector<EntIdVec>;
using EntIdMap = std::map<std::string, EntIdVec2d>;
//using EntIdMapFullIndex = std::pair<std::string, PosVec2>;

using CompUptr = std::unique_ptr<Comp>;
using CompMap = std::map<std::string, CompUptr>;
using CompMapUptr = std::unique_ptr<CompMap>;
using EngineCompMap = std::map<EntId, CompMapUptr>;

using SysUptr = std::unique_ptr<Sys>;
using SysMap = std::map<std::string, SysUptr>;
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
	const CompMap& comp_map() const;

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

	virtual void tick(Engine* engine);
};
//--------
class Engine
{
	friend class Ent;
public:		// types
	using Ent
protected:		// variables
	EntId _next_ent_id = 0;

	std::set<EntId> _to_destroy_set;

	EngineCompMap _engine_comp_map;

	SysMap _sys_map;
public:		// functions
	Engine();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Engine);
	virtual ~Engine();

	EntId create();
	inline void sched_destroy(EntId id)
	{
		_to_destroy_set.add(id);
	}
	void destroy();

	std::map<

	template<typename... ArgTypes>
	inline EntIdVec ent_id_vec_from_keys(ArgTypes&&... args)
	{
		std::vector<std::string> key_vec;

		(key_vec.push_back(strings::sconcat(args)), ...);

		return ent_id_vec_from_keys(key_vec);
	}
	EntIdVec ent_id_vec_from_keys
		(const std::vector<std::string>& key_vec) const;

	inline Ent ent_at(EntId id) const
	{
		return Ent(this, id);
	}
	inline CompMap& comp_map(EntId id) const
	{
		return *_engine_comp_map.at(id);
	}
	inline const CompMap& comp_map(EntId id) const
	{
		return *_engine_comp_map.at(id);
	}
	bool insert_comp(EntId id, const std::string& key, CompUptr&& comp);
	bool insert_or_replace_comp(EntId id, const std::string& key,
		CompUptr&& comp);
	size_t erase_comp(EntId id, const std::string& key);

	bool insert_sys(const std::string& key, SysUptr&& sys);
	bool insert_or_replace_sys(const std::string& key, SysUptr&& sys);
	size_t erase_sys(const std::string& key);

	void tick();

	GEN_GETTER_BY_VAL(next_ent_id);
	GEN_GETTER_BY_CON_REF(to_destroy_set);
	GEN_GETTER_BY_CON_REF(engine_comp_map);
	GEN_GETTER_BY_CON_REF(sys_map);
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
