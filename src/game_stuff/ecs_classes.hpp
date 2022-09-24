#ifndef liborangepower_game_stuff_ecs_classes_hpp
#define liborangepower_game_stuff_ecs_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../strings/sconcat_etc.hpp"
#include "../math/vec2_classes.hpp"
#include "../containers/prev_curr_pair_classes.hpp"
#include "../binser/serialize_funcs.hpp"

#include <map>
#include <set>
#include <sstream>

namespace liborangepower
{

using namespace integer_types;

namespace game
{
namespace ecs
{
//--------
class Ent;
class Comp;
class Sys;
class Engine;

using FileNum = i64;

using EntId = u64;
static constexpr EntId 
	//ENT_NULL_ID = EntId(i64(-1));
	ENT_NULL_ID = -1;

using EntIdVec = std::vector<EntId>;
using EntIdVec2d = std::vector<EntIdVec>;
using EntIdMap = std::unordered_map<std::string, EntIdVec2d>;
using EntIdMapFullIndex = std::pair<std::string, math::Vec2<size_t>>;
using EntIdSet = std::unordered_set<EntId>;

using CompSptr = std::shared_ptr<Comp>;
using CompMap = std::unordered_map<std::string, CompSptr>;
//using CompMapSptr = std::shared_ptr<CompMap>;

using EngineCompMap = std::unordered_map<EntId, CompMap>;

using SysSptr = std::shared_ptr<Sys>;
using SysMap = std::unordered_map<std::string, SysSptr>;

using StrKeySet = std::unordered_set<std::string>;

using EngineInsertSearchMultiRet
	= std::pair<bool, std::unordered_map<std::string, bool>>;
using EngineEraseMultiRet
	= std::unordered_map<std::string, size_t>;
//--------
class Ent final
{
private:		// variables
	Engine* _engine = nullptr;
	EntId _id = ENT_NULL_ID;
	FileNum _file_num = 0;
public:		// functions
	inline Ent(Engine* s_engine, EntId s_id, FileNum s_file_num);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Ent);
	~Ent() = default;

	inline CompMap& comp_map_fn() const;

	inline bool insert_comp_fn(const std::string& key, CompSptr&& comp) const;
	inline bool insert_or_replace_comp_fn(const std::string& key,
		CompSptr&& comp) const;
	inline size_t erase_comp_fn(const std::string& key) const;

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

	virtual operator binser::Value () const;
};

// A `Comp`onent specifying that the entity shouldn't be serialized
class NonSerializable: public Comp
{
public:		// constants
	static const std::string KIND_STR;
//public:		// misc.
//	#define MEMB_LIST_ECS_COMP_NON_SERIALIZABLE(X)
public:		// functions
	NonSerializable() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(NonSerializable);
	virtual ~NonSerializable() = default;

	virtual std::string kind_str() const;
};

inline CompMap make_comp_map_ks(std::same_as<CompSptr> auto&&... args)
{
	CompMap ret;

	((ret[args->kind_str()] = std::move(args)), ...);

	return ret;
}
//--------
class Sys
{
public:		// serialization stuff
	/* #define MEMB_LIST_ECS_SYS(X) */ \
	/*	X(_did_init, std::nullopt) */ \
	/*	X(active, std::nullopt) */ \

private:		// variables
	bool _did_init = false;
public:		// variables
	containers::PrevCurrPair<bool>
		active = {false, false};
public:		// functions
	inline Sys()
	{
	}
	//Sys(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Sys);
	virtual ~Sys() = default;

	virtual std::string kind_str() const;

	//operator binser::Value () const;

	void prep_init();
protected:		// functions
	virtual void _init(Engine* ecs_engine);
public:		// functions
	virtual void tick(Engine* ecs_engine);

	GEN_GETTER_BY_VAL(did_init);
protected:		// functions
	// The derived class should call this function at the beginning of its
	// `_init()` implementation.
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
	= binser::IsValidFromBvFactoryT<T, Comp>;

template<typename T>
concept EngineDerivedFromSys
	= binser::IsValidFromBvFactoryT<T, Sys>;

class Engine
{
	friend class Ent;
public:		// constants
	static constexpr FileNum
		DEFAULT_NUM_FILES = 9,

		USE_CURR_FILE_NUM = -1,
		USE_SRC_FILE_NUM = -2,
		USE_COPY_DST_FILE_NUM = -3;
protected:		// serialized variables
	#define MEMB_AUTOSER_LIST_ECS_ENGINE(X) \
		X(_next_ent_id_vec, std::nullopt) \
		X(_to_destroy_set_vec, std::nullopt) \
		X(_num_files, std::nullopt) \
		/* X(_engine_comp_map_vec, &_comp_deser_func_map) */ \

	binser::VectorEx<EntId> _next_ent_id_vec;
	binser::VectorEx<EntIdSet> _to_destroy_set_vec;
	FileNum _num_files = DEFAULT_NUM_FILES;
	// All `EntId` are stored as just the keys of each `EngineCompMap`,
	// with no other storage for them.
	binser::VectorEx<EngineCompMap> _engine_comp_map_vec;
protected:		// non-serialized variables
	SysMap _sys_map;
private:		// non-serialized variables
	//binser::FromBvFactory<Comp>::FuncMap _comp_deser_func_map;
	binser::FromBvFactoryFuncMap<Comp> _comp_deser_func_map;
	//binser::FromBvFactory<Sys>::FuncMap _sys_deser_func_map;
public:		// non-serialized variables
	FileNum
		curr_file_num = 0,
		src_file_num = 0,
		copy_dst_file_num = 0;
public:		// functions
	//--------
	Engine(u64 s_num_files=DEFAULT_NUM_FILES);
	//GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Engine);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Engine);
	virtual ~Engine();
	//--------
	operator binser::Value () const;
	//--------
	void copy_file();
	void erase_file();
	//--------
	void deserialize(const binser::Value& bv);
	//{
	//	_autoser_deserialize(bv);
	//	_ent_deserialize(bv);
	//	//_sys_deserialize(bv);
	//}
	//--------
	template<EngineDerivedFromComp FirstCompT,
		EngineDerivedFromComp... RemCompTs>
	void init_comp_deserialize()
	{
		_comp_deser_func_map 
			= binser::FromBvFactory<Comp>::gen_func_map
				<FirstCompT, RemCompTs...>();
	}

	//template<EngineDerivedFromSys FirstSysT,
	//	EngineDerivedFromSys... RemSysTs>
	//void init_sys_deserialize()
	//{
	//	_sys_deser_func_map 
	//		= binser::FromBvFactory<Sys>::gen_func_map
	//			<FirstSysT, RemSysTs...>();
	//}
	//--------
private:		// functions
	//--------
	//void _autoser_deserialize(const binser::Value& bv);

	////template<EngineDerivedFromComp FirstCompT,
	////	EngineDerivedFromComp... RemCompTs>
	//void _ent_deserialize(const binser::Value& bv);

	////template<EngineDerivedFromSys FirstSysT,
	////	EngineDerivedFromSys... RemSysTs>
	//void _sys_deserialize(const binser::Value& bv);
	//--------
	//void _inner_create_fn(EntId id, FileNum file_num,
	//	bool mk_non_ser=false);
	void _inner_create_fn(EntId id, FileNum file_num,
		std::optional<CompMap>&& s_comp_map);
	//--------
public:		// functions
	//--------
	//EntId create(FileNum file_num, bool mk_non_ser=false);
	EntId create_fn(FileNum file_num,
		std::optional<CompMap>&& s_comp_map=std::nullopt);
	//inline EntId create(bool mk_non_ser=false)
	inline EntId create(std::optional<CompMap>&& s_comp_map=std::nullopt)
	{
		//return create(curr_file_num, mk_non_ser);
		return create_fn(curr_file_num, std::move(s_comp_map));
	}

	inline void sched_destroy_fn(EntId id, FileNum file_num)
	{
		to_destroy_set_fn(file_num).insert(id);
	}
	inline void sched_destroy(EntId id)
	{
		sched_destroy_fn(id, curr_file_num);
	}

	// Destroy now
	void destroy_fn(EntId id, FileNum file_num);
	void destroy_fn(FileNum file_num);

	inline void destroy(EntId id)
	{
		destroy_fn(id, curr_file_num);
	}
	inline void destroy()
	{
		destroy_fn(curr_file_num);
	}

	void destroy_all_fn(FileNum file_num);
	inline void destroy_all()
	{
		destroy_all_fn(USE_CURR_FILE_NUM);
	}
	void destroy_all_every_fn();
	//--------
	EntIdVec ent_id_vec_from_keys_any_fn(const StrKeySet& key_set,
		FileNum file_num=USE_CURR_FILE_NUM);
	inline EntIdVec ent_id_vec_from_keys_any_fn_v(FileNum file_num,
		const concepts::HasStdOstmOpLshift auto&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_vec_from_keys_any_fn(key_set, file_num);
	}
	inline EntIdVec ent_id_vec_from_keys_any_v
		(const concepts::HasStdOstmOpLshift auto&... args)
	{
		return ent_id_vec_from_keys_any_fn_v(curr_file_num, args...);
	}
	//--------
	EntIdSet ent_id_set_from_keys_any_fn(const StrKeySet& key_set,
		FileNum file_num=USE_CURR_FILE_NUM);
	inline EntIdSet ent_id_set_from_keys_any_fn_v(FileNum file_num,
		const concepts::HasStdOstmOpLshift auto&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_set_from_keys_any_fn(key_set, file_num);
	}
	inline EntIdSet ent_id_set_from_keys_any_v
		(const concepts::HasStdOstmOpLshift auto&... args)
	{
		return ent_id_set_from_keys_any_fn_v(curr_file_num, args...);
	}
	//--------
	EntIdVec ent_id_vec_from_keys_all_fn(const StrKeySet& key_set,
		FileNum file_num=USE_CURR_FILE_NUM);
	inline EntIdVec ent_id_vec_from_keys_all_fn_v(FileNum file_num,
		const concepts::HasStdOstmOpLshift auto&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_vec_from_keys_all_fn(key_set, file_num);
	}
	inline EntIdVec ent_id_vec_from_keys_all_v
		(const concepts::HasStdOstmOpLshift auto&... args)
	{
		return ent_id_vec_from_keys_all_fn_v(curr_file_num, args...);
	}
	//--------
	EntIdSet ent_id_set_from_keys_all_fn(const StrKeySet& key_set,
		FileNum file_num=USE_CURR_FILE_NUM);
	inline EntIdSet ent_id_set_from_keys_all_fn_v(FileNum file_num,
		const concepts::HasStdOstmOpLshift auto&... args)
	{
		StrKeySet key_set;

		(key_set.insert(strings::sconcat(args)), ...);

		return ent_id_set_from_keys_all_fn(key_set, file_num);
	}
	inline EntIdSet ent_id_set_from_keys_all_v
		(const concepts::HasStdOstmOpLshift auto&... args)
	{
		return ent_id_set_from_keys_all_fn_v(curr_file_num, args...);
	}
	//--------
	inline Ent ent_at_fn(EntId id, FileNum file_num)
	{
		return Ent(this, id, sel_file_num(file_num));
	}
	inline Ent ent_at(EntId id)
	{
		return ent_at_fn(id, curr_file_num);
	}
	//--------
	inline CompMap& comp_map_fn(EntId id, FileNum file_num)
	{
		return engine_comp_map_fn(file_num).at(id);
	}

	inline CompMap& comp_map(EntId id)
	{
		return comp_map_fn(id, curr_file_num);
	}
	//--------
	inline CompSptr& comp_at_fn(EntId id, const std::string& key,
		FileNum file_num)
	{
		return comp_map_fn(id, file_num).at(key);
	}
	template<EngineDerivedFromComp T>
	inline CompSptr& comp_at_fn(EntId id, FileNum file_num)
	{
		return comp_map_fn(id, file_num).at(T::KIND_STR);
	}

	inline CompSptr& comp_at(EntId id, const std::string& key)
	{
		return comp_at_fn(id, key, curr_file_num);
	}
	template<EngineDerivedFromComp T>
	inline CompSptr& comp_at(EntId id)
	{
		return comp_at_fn<T>(id, curr_file_num);
	}
	//--------
	template<EngineDerivedFromComp T>
	inline T* casted_comp_at_fn(EntId id, const std::string& key,
		FileNum file_num)
	{
		return static_cast<T*>(comp_at_fn(id, key, file_num).get());
	}
	template<EngineDerivedFromComp T>
	inline T* casted_comp_at_fn(EntId id, FileNum file_num)
	{
		return casted_comp_at_fn<T>(id, T::KIND_STR, file_num);
	}
	//--------
	template<EngineDerivedFromComp T>
	inline T* casted_comp_at(EntId id, const std::string& key)
	{
		return casted_comp_at_fn<T>(id, key, curr_file_num);
	}
	template<EngineDerivedFromComp T>
	inline T* casted_comp_at(EntId id)
	{
		return casted_comp_at_fn<T>(id, curr_file_num);
	}
	//--------
	bool insert_comp_fn(EntId id, const std::string& key, CompSptr&& comp,
		FileNum file_num);
	inline bool insert_comp_fn(EntId id, CompSptr&& comp, FileNum file_num)
	{
		const std::string& KIND_STR = comp->kind_str();
		return insert_comp_fn(id, KIND_STR, std::move(comp), file_num);
	}
	EngineInsertSearchMultiRet insert_multi_comp_fn(EntId id,
		CompMap&& some_comp_map, FileNum file_num);
	//--------
	inline bool insert_comp(EntId id, const std::string& key,
		CompSptr&& comp)
	{
		return insert_comp_fn(id, key, std::move(comp), curr_file_num);
	}
	inline bool insert_comp(EntId id, CompSptr&& comp)
	{
		return insert_comp_fn(id, std::move(comp), curr_file_num);
	}
	inline EngineInsertSearchMultiRet insert_multi_comp(EntId id,
		CompMap&& some_comp_map)
	{
		return insert_multi_comp_fn(id, std::move(some_comp_map),
			curr_file_num);
	}
	//--------
	bool insert_or_replace_comp_fn(EntId id, const std::string& key,
		CompSptr&& comp, FileNum file_num);
	inline bool insert_or_replace_comp_fn(EntId id, CompSptr&& comp,
		FileNum file_num)
	{
		const std::string& KIND_STR = comp->kind_str();
		return insert_or_replace_comp_fn(id, KIND_STR, std::move(comp),
			file_num);
	}
	EngineInsertSearchMultiRet insert_or_replace_multi_comp_fn(EntId id,
		CompMap&& some_comp_map, FileNum file_num);
	//--------
	inline bool insert_or_replace_comp_fn(EntId id,
		const std::string& key, CompSptr&& comp)
	{
		return insert_or_replace_comp_fn(id, key, std::move(comp),
			curr_file_num);
	}
	inline bool insert_or_replace_comp_fn(EntId id, CompSptr&& comp)
	{
		return insert_or_replace_comp_fn(id, std::move(comp),
			curr_file_num);
	}
	inline EngineInsertSearchMultiRet insert_or_replace_multi_comp
		(EntId id, CompMap&& some_comp_map)
	{
		return insert_or_replace_multi_comp_fn(id,
			std::move(some_comp_map), curr_file_num);
	}
	//--------
	size_t erase_comp_fn(EntId id, const std::string& key, FileNum file_num);
	template<EngineDerivedFromComp T>
	inline size_t erase_comp_fn(EntId id, FileNum file_num)
	{
		return erase_comp_fn(id, T::KIND_STR, file_num);
	}
	EngineEraseMultiRet erase_multi_comp_fn(EntId id,
		const StrKeySet& key_set, FileNum file_num);

	template<EngineDerivedFromComp... Ts>
	inline EngineEraseMultiRet erase_multi_comp_fn(EntId id,
		FileNum file_num)
	{
		StrKeySet key_set;
		(key_set.insert(Ts::KIND_STR), ...);
		return erase_multi_comp_fn(id, key_set, file_num);
	}
	//--------
	inline size_t erase_comp(EntId id, const std::string& key)
	{
		return erase_comp_fn(id, key, curr_file_num);
	}
	template<EngineDerivedFromComp T>
	inline size_t erase_comp(EntId id)
	{
		return erase_comp_fn<T>(id, curr_file_num);
	}

	inline EngineEraseMultiRet erase_multi_comp(EntId id,
		const StrKeySet& key_set)
	{
		return erase_multi_comp_fn(id, key_set, curr_file_num);
	}
	template<EngineDerivedFromComp... Ts>
	inline EngineEraseMultiRet erase_multi_comp(EntId id)
	{
		return erase_multi_comp_fn<Ts...>(id, curr_file_num);
	}
	//--------
	bool insert_sys(const std::string& key, SysSptr&& sys);
	inline bool insert_sys(SysSptr&& sys)
	{
		const std::string& KIND_STR = sys->kind_str();
		return insert_sys(KIND_STR, std::move(sys));
	}
	EngineInsertSearchMultiRet insert_multi_sys(SysMap&& some_sys_map);

	bool insert_or_replace_sys(const std::string& key, SysSptr&& sys);
	inline bool insert_or_replace_sys(SysSptr&& sys)
	{
		const std::string& KIND_STR = sys->kind_str();
		return insert_or_replace_sys(KIND_STR, std::move(sys));
	}
	EngineInsertSearchMultiRet insert_or_replace_multi_sys
		(SysMap&& some_sys_map);

	size_t erase_sys(const std::string& key);
	template<EngineDerivedFromSys T>
	inline size_t erase_sys()
	{
		return erase_sys(T::KIND_STR);
	}
	EngineEraseMultiRet erase_multi_sys(const StrKeySet& key_set);

	template<EngineDerivedFromSys... Ts>
	inline EngineEraseMultiRet erase_multi_sys()
	{
		StrKeySet key_set;
		(key_set.insert(Ts::KIND_STR), ...);
		return erase_multi_sys(key_set);
	}
	//--------
	inline bool has_ent_w_comp_fn(EntId id, const std::string& key,
		FileNum file_num)
	{
		return (engine_comp_map_fn(file_num).contains(id)
			&& comp_map_fn(id, file_num).contains(key));
	}
	template<EngineDerivedFromComp T>
	inline bool has_ent_w_comp_fn(EntId id, FileNum file_num)
	{
		return has_ent_w_comp_fn(id, T::KIND_STR, file_num);
	}

	EngineInsertSearchMultiRet has_ent_w_multi_comp_fn(EntId id,
		const StrKeySet& key_set, FileNum file_num);
	template<EngineDerivedFromComp... Ts>
	inline EngineInsertSearchMultiRet has_ent_w_multi_comp_fn(EntId id,
		FileNum file_num)
	{
		StrKeySet key_set;
		(key_set.insert(Ts::KIND_STR), ...);
		return has_ent_w_multi_comp_fn(id, key_set, file_num);
	}
	//--------
	inline bool has_ent_w_comp(EntId id, const std::string& key)
	{
		return has_ent_w_comp_fn(id, key, curr_file_num);
	}
	template<EngineDerivedFromComp T>
	inline bool has_ent_w_comp(EntId id)
	{
		return has_ent_w_comp_fn<T>(id, curr_file_num);
	}

	inline EngineInsertSearchMultiRet has_ent_w_multi_comp(EntId id,
		const StrKeySet& key_set)
	{
		return has_ent_w_multi_comp_fn(id, key_set, curr_file_num);
	}
	template<EngineDerivedFromComp... Ts>
	inline EngineInsertSearchMultiRet has_ent_w_multi_comp(EntId id)
	{
		return has_ent_w_multi_comp_fn<Ts...>(id, curr_file_num);
	}
	//--------
	void tick();
	//--------
	inline EntId& next_ent_id_fn(FileNum file_num)
	{
		return _next_ent_id_vec.data.at(sel_file_num(file_num));
	}
	inline const EntId& next_ent_id_fn(FileNum file_num) const
	{
		return _next_ent_id_vec.data.at(sel_file_num(file_num));
	}

	inline EntId& next_ent_id()
	{
		return next_ent_id_fn(curr_file_num);
	}
	inline const EntId& next_ent_id() const
	{
		return next_ent_id_fn(curr_file_num);
	}
	//--------
	inline EntIdSet& to_destroy_set_fn(FileNum file_num)
	{
		return _to_destroy_set_vec.data.at(sel_file_num(file_num));
	}
	inline const EntIdSet& to_destroy_set_fn(FileNum file_num) const
	{
		return _to_destroy_set_vec.data.at(sel_file_num(file_num));
	}

	inline EntIdSet& to_destroy_set()
	{
		return to_destroy_set_fn(curr_file_num);
	}
	inline const EntIdSet& to_destroy_set() const
	{
		return to_destroy_set_fn(curr_file_num);
	}
	//--------
	inline EngineCompMap& engine_comp_map_fn(FileNum file_num)
	{
		return _engine_comp_map_vec.data.at(sel_file_num(file_num));
	}
	inline const EngineCompMap& engine_comp_map_fn(FileNum file_num) const
	{
		return _engine_comp_map_vec.data.at(sel_file_num(file_num));
	}

	inline EngineCompMap& engine_comp_map()
	{
		return engine_comp_map_fn(curr_file_num);
	}
	inline const EngineCompMap& engine_comp_map() const
	{
		return engine_comp_map_fn(curr_file_num);
	}
	//--------
	inline FileNum sel_file_num(FileNum some_file_num) const
	{
		//return (some_file_num == USE_CURR_FILE_NUM)
		//	? curr_file_num
		//	: some_file_num;
		switch (some_file_num)
		{
		//--------
		case USE_CURR_FILE_NUM:
			return curr_file_num;
			break;
		case USE_SRC_FILE_NUM:
			return src_file_num;
			break;
		case USE_COPY_DST_FILE_NUM:
			return copy_dst_file_num;
		default:
			return some_file_num;
			break;
		//--------
		}
	}
	//--------
	GEN_GETTER_BY_VAL(next_ent_id_vec);
	GEN_GETTER_BY_CON_REF(to_destroy_set_vec);
	GEN_GETTER_BY_VAL(num_files);
	GEN_GETTER_BY_CON_REF(engine_comp_map_vec);
	GEN_GETTER_BY_CON_REF(sys_map);
	//--------
//pubic:		// functions
//	inline FileNum sel_file_num(FileNum some_file_num) const
//	{
//		//return (some_file_num == USE_CURR_FILE_NUM)
//		//	? curr_file_num
//		//	: some_file_num;
//	}
};
//--------
inline Ent::Ent(Engine* s_engine=nullptr, EntId s_id=ENT_NULL_ID,
	FileNum s_file_num=Engine::USE_CURR_FILE_NUM)
	: _engine(s_engine), _id(s_id), _file_num(s_file_num)
{
}
inline CompMap& Ent::comp_map_fn() const
{
	return _engine->comp_map_fn(id(), file_num());
}
inline bool Ent::insert_comp_fn(const std::string& key, CompSptr&& comp)
	const
{
	return _engine->insert_comp_fn(id(), key, std::move(comp), file_num());
}
inline bool Ent::insert_or_replace_comp_fn(const std::string& key,
	CompSptr&& comp) const
{
	return _engine->insert_or_replace_comp_fn(id(), key, std::move(comp),
		file_num());
}
inline size_t Ent::erase_comp_fn(const std::string& key) const
{
	return _engine->erase_comp_fn(id(), key, file_num());
}
//--------
} // namespace ecs
} // namespace game
} // namespace liborangepower

#endif		// liborangepower_game_stuff_ecs_classes_hpp
