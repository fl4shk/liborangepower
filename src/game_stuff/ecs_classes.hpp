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

namespace liborangepower {
//--------
using namespace integer_types;
//--------
namespace game {
namespace ecs {
//--------
class EntRef;
class Comp;
class Sys;
class Engine;

using FileNum = i64;

using EntId = u64;
static constexpr EntId 
	//ENT_NULL_ID = EntId(i64(-1));
	ENT_NULL_ID = -1;

using EntIdDarr = std::vector<EntId>;
using EntIdDa2d = std::vector<EntIdDarr>;
using EntIdUmap = std::unordered_map<std::string, EntIdDa2d>;
using EntIdUmapFullIndex = std::pair<std::string, math::Vec2<size_t>>;
using EntIdUset = std::unordered_set<EntId>;

using CompSptr = std::shared_ptr<Comp>;
using CompUmap = std::unordered_map<std::string, CompSptr>;
//using CompUmapSptr = std::shared_ptr<CompUmap>;

using EngineCompUmap = std::unordered_map<EntId, CompUmap>;

using SysSptr = std::shared_ptr<Sys>;
using SysUmap = std::unordered_map<std::string, SysSptr>;

using StrKeyUset = std::unordered_set<std::string>;

using EngineInsertSearchMultiRet
	= std::pair<bool, std::unordered_map<std::string, bool>>;
using EngineEraseMultiRet
	= std::unordered_map<std::string, size_t>;
//--------
class EntRef final {
private:		// variables
	Engine* _engine = nullptr;
	EntId _id = ENT_NULL_ID;
	FileNum _file_num = 0;
public:		// functions
	inline EntRef(Engine* s_engine, EntId s_id, FileNum s_file_num);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(EntRef);
	~EntRef() = default;

	inline CompUmap& comp_umap_fn() const;

	inline bool insert_comp_fn(const std::string& key, CompSptr&& comp)
	const;
	inline bool insert_or_replace_comp_fn(
		const std::string& key, CompSptr&& comp
	) const;
	inline size_t erase_comp_fn(const std::string& key) const;

	GEN_GETTER_AND_SETTER_BY_VAL(id);
	GEN_GETTER_AND_SETTER_BY_VAL(engine);
	GEN_GETTER_AND_SETTER_BY_VAL(file_num);
};
//--------
class Comp {
public:		// misc.
	#define MEMB_LIST_ECS_COMP(X)
public:		// functions
	Comp() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Comp);
	virtual ~Comp() = default;

	// This is used as the key for individual `CompUmap` elements of an
	// `EntRef`.
	virtual std::string kind_str() const;

	virtual operator binser::Value () const;
};

// A `Comp`onent specifying that the entity shouldn't be serialized
class NonSerializable: public Comp {
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

inline CompUmap make_comp_umap_ks(std::same_as<CompSptr> auto&&... args) {
	CompUmap ret;

	((ret[args->kind_str()] = std::move(args)), ...);

	return ret;
}
//--------
class Sys {
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
	inline Sys() {
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
	inline void _init_start() {
		_did_init = true;
	}
	// Returns true when the derived class should run its unique `tick()`
	// functionality
	bool _tick_helper(Engine* ecs_engine, bool cond);
};

inline SysUmap make_sys_umap_ks(std::same_as<SysSptr> auto&&... args) {
	SysUmap ret;

	((ret[args->kind_str()] = std::move(args)), ...);

	return ret;
}
//--------
template<typename T>
concept EngineDerivedFromComp 
	= binser::IsValidFromBvFactoryT<T, Comp>;

template<typename T>
concept EngineDerivedFromSys
	= binser::IsValidFromBvFactoryT<T, Sys>;

template<EngineDerivedFromComp... Ts>
inline StrKeyUset make_key_uset() {
	StrKeyUset ret;

	(ret.insert(Ts::KIND_STR), ...);

	return ret;
}
template<EngineDerivedFromSys... Ts>
inline StrKeyUset make_key_uset() {
	StrKeyUset ret;

	(ret.insert(Ts::KIND_STR), ...);

	return ret;
}

class Engine {
	friend class EntRef;
public:		// constants
	static constexpr FileNum
		DEFAULT_NUM_FILES = 9,

		USE_CURR_FILE_NUM = -1,
		USE_SRC_FILE_NUM = -2,
		USE_COPY_DST_FILE_NUM = -3;
protected:		// serialized variables
	#define MEMB_AUTOSER_LIST_ECS_ENGINE(X) \
		X(_next_ent_id_darr, std::nullopt) \
		X(_to_destroy_uset_darr, std::nullopt) \
		X(_num_files, std::nullopt) \
		/* X(_engine_comp_umap_darr, &_comp_deser_func_umap) */ \

	binser::VectorEx<EntId> _next_ent_id_darr;
	binser::VectorEx<EntIdUset> _to_destroy_uset_darr;
	FileNum _num_files = DEFAULT_NUM_FILES;
	// All `EntId` are stored as just the keys of each `EngineCompUmap`,
	// with no other storage for them.
	binser::VectorEx<EngineCompUmap> _engine_comp_umap_darr;
protected:		// non-serialized variables
	SysUmap _sys_umap;
private:		// non-serialized variables
	//binser::FromBvFactory<Comp>::FuncUmap _comp_deser_func_umap;
	binser::FromBvFactoryFuncUmap<Comp> _comp_deser_func_umap;
	//binser::FromBvFactory<Sys>::FuncUmap _sys_deser_func_umap;
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
	void init_comp_deserialize() {
		_comp_deser_func_umap 
			= binser::FromBvFactory<Comp>::gen_func_umap
				<FirstCompT, RemCompTs...>();
	}

	//template<EngineDerivedFromSys FirstSysT,
	//	EngineDerivedFromSys... RemSysTs>
	//void init_sys_deserialize()
	//{
	//	_sys_deser_func_umap 
	//		= binser::FromBvFactory<Sys>::gen_func_umap
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
	//void _inner_create_fn(
	//	EntId id, FileNum file_num, bool mk_non_ser=false
	//);
	void _inner_create_fn(
		EntId id, FileNum file_num, std::optional<CompUmap>&& s_comp_umap
	);
	//--------
public:		// functions
	//--------
	//EntId create(FileNum file_num, bool mk_non_ser=false);
	EntId create_fn(
		FileNum file_num,
		std::optional<CompUmap>&& s_comp_umap=std::nullopt
	);
	//inline EntId create(bool mk_non_ser=false)
	inline EntId create(
		std::optional<CompUmap>&& s_comp_umap=std::nullopt
	) {
		//return create(curr_file_num, mk_non_ser);
		return create_fn(curr_file_num, std::move(s_comp_umap));
	}
	//--------
	// These `throw` an `exception` if there is already an entity that has
	// been created with a particular collection of `Comp`s
	EntId create_singleton_any_fn(
		FileNum file_num, CompUmap&& s_comp_umap,
		const std::string& func_name
	);
	inline EntId create_singleton_any(
		CompUmap&& s_comp_umap, const std::string& func_name
	) {
		return create_singleton_any_fn(curr_file_num,
			std::move(s_comp_umap), func_name);
	}
	EntId create_singleton_all_fn(
		FileNum file_num, CompUmap&& s_comp_umap,
		const std::string& func_name
	);
	inline EntId create_singleton_all(
		CompUmap&& s_comp_umap, const std::string& func_name
	) {
		return create_singleton_all_fn(curr_file_num,
			std::move(s_comp_umap), func_name);
	}

	// These `throw` an `exception` if there is already an entity that has
	// been created with a particular collection of `Comp`s
	void force_singleton_any_fn(
		const StrKeyUset& key_uset, const std::string& func_name,
		FileNum file_num
	);
	inline void force_singleton_any(
		const StrKeyUset& key_uset, const std::string& func_name
	) {
		force_singleton_any_fn(key_uset, func_name, curr_file_num);
	}
	void force_singleton_all_fn(
		const StrKeyUset& key_uset, const std::string& func_name,
		FileNum file_num
	);
	inline void force_singleton_all(
		const StrKeyUset& key_uset, const std::string& func_name
	) {
		force_singleton_all_fn(key_uset, func_name, curr_file_num);
	}
	//--------
	inline void sched_destroy_fn(EntId id, FileNum file_num) {
		to_destroy_uset_fn(file_num).insert(id);
	}
	inline void sched_destroy(EntId id) {
		sched_destroy_fn(id, curr_file_num);
	}

	void destroy_now_fn(EntId id, FileNum file_num);
	//void destroy_now_fn(FileNum file_num);
	inline void destroy_now(EntId id) {
		destroy_now_fn(id, curr_file_num);
	}
	//inline void destroy_now() {
	//	destroy_now_fn(curr_file_num);
	//}

	//void destroy_scheduled_fn(EntId id, FileNum file_num);
	void destroy_scheduled_fn(FileNum file_num);

	//inline void destroy_scheduled(EntId id) {
	//	destroy_scheduled_fn(id, curr_file_num);
	//}
	inline void destroy_scheduled() {
		destroy_scheduled_fn(curr_file_num);
	}
	//inline void destroy_scheduled() {
	//	destroy_scheduled_fn(curr_file_num);
	//}

	void destroy_all_fn(FileNum file_num);
	inline void destroy_all() {
		destroy_all_fn(USE_CURR_FILE_NUM);
	}
	void destroy_all_every_fn();
	//--------
	// Search for entities with *any* of the keys in `key_uset`
	EntIdDarr ent_id_darr_from_keys_any_fn(
		const StrKeyUset& key_uset, FileNum file_num
	);
	inline EntIdDarr ent_id_darr_from_keys_any_fn_v(
		FileNum file_num, const concepts::HasStdOstmOpLshift auto&... args
	) {
		StrKeyUset key_uset;

		(key_uset.insert(strings::sconcat(args)), ...);

		return ent_id_darr_from_keys_any_fn(key_uset, file_num);
	}
	inline EntIdDarr ent_id_darr_from_keys_any(const StrKeyUset& key_uset) {
		return ent_id_darr_from_keys_any_fn(key_uset, curr_file_num);
	}
	inline EntIdDarr ent_id_darr_from_keys_any_v(
		const concepts::HasStdOstmOpLshift auto&... args
	) {
		return ent_id_darr_from_keys_any_fn_v(curr_file_num, args...);
	}
	//--------
	// Search for entities with *any* of the keys in `key_uset`
	EntIdUset ent_id_uset_from_keys_any_fn(
		const StrKeyUset& key_uset, FileNum file_num
	);
	inline EntIdUset ent_id_uset_from_keys_any_fn_v(
		FileNum file_num, const concepts::HasStdOstmOpLshift auto&... args
	) {
		StrKeyUset key_uset;

		(key_uset.insert(strings::sconcat(args)), ...);

		return ent_id_uset_from_keys_any_fn(key_uset, file_num);
	}
	inline EntIdUset ent_id_uset_from_keys_any(
		const StrKeyUset& key_uset
	) {
		return ent_id_uset_from_keys_any_fn(key_uset, curr_file_num);
	}
	inline EntIdUset ent_id_uset_from_keys_any_v(
		const concepts::HasStdOstmOpLshift auto&... args
	) {
		return ent_id_uset_from_keys_any_fn_v(curr_file_num, args...);
	}
	//--------
	// Search for entities with *all* of the keys in `key_uset`
	EntIdDarr ent_id_darr_from_keys_all_fn(
		const StrKeyUset& key_uset, FileNum file_num
	);
	inline EntIdDarr ent_id_darr_from_keys_all_fn_v(
		FileNum file_num, const concepts::HasStdOstmOpLshift auto&... args
	) {
		StrKeyUset key_uset;

		(key_uset.insert(strings::sconcat(args)), ...);

		return ent_id_darr_from_keys_all_fn(key_uset, file_num);
	}
	EntIdDarr ent_id_darr_from_keys_all(const StrKeyUset& key_uset) {
		return ent_id_darr_from_keys_all_fn(key_uset, curr_file_num);
	}
	inline EntIdDarr ent_id_darr_from_keys_all_v(
		const concepts::HasStdOstmOpLshift auto&... args
	) {
		return ent_id_darr_from_keys_all_fn_v(curr_file_num, args...);
	}
	//--------
	// Search for entities with *all* of the keys in `key_uset`
	EntIdUset ent_id_uset_from_keys_all_fn(
		const StrKeyUset& key_uset, FileNum file_num
	);
	inline EntIdUset ent_id_uset_from_keys_all_fn_v(
		FileNum file_num, const concepts::HasStdOstmOpLshift auto&... args
	) {
		StrKeyUset key_uset;

		(key_uset.insert(strings::sconcat(args)), ...);

		return ent_id_uset_from_keys_all_fn(key_uset, file_num);
	}
	EntIdUset ent_id_uset_from_keys_all(const StrKeyUset& key_uset) {
		return ent_id_uset_from_keys_all_fn(key_uset, curr_file_num);
	}
	inline EntIdUset ent_id_uset_from_keys_all_v(
		const concepts::HasStdOstmOpLshift auto&... args
	) {
		return ent_id_uset_from_keys_all_fn_v(curr_file_num, args...);
	}
	//--------
	inline EntRef ent_ref_at_fn(EntId id, FileNum file_num) {
		return EntRef(this, id, sel_file_num(file_num));
	}
	inline EntRef ent_ref_at(EntId id) {
		return ent_ref_at_fn(id, curr_file_num);
	}
	//--------
	inline CompUmap& comp_umap_fn(EntId id, FileNum file_num) {
		return engine_comp_umap_fn(file_num).at(id);
	}

	inline CompUmap& comp_umap(EntId id) {
		return comp_umap_fn(id, curr_file_num);
	}
	//--------
	inline CompSptr& comp_at_fn(
		EntId id, const std::string& key, FileNum file_num
	) {
		return comp_umap_fn(id, file_num).at(key);
	}
	template<EngineDerivedFromComp T>
	inline CompSptr& comp_at_fn(EntId id, FileNum file_num) {
		return comp_umap_fn(id, file_num).at(T::KIND_STR);
	}

	inline CompSptr& comp_at(EntId id, const std::string& key) {
		return comp_at_fn(id, key, curr_file_num);
	}
	template<EngineDerivedFromComp T>
	inline CompSptr& comp_at(EntId id) {
		return comp_at_fn<T>(id, curr_file_num);
	}
	//--------
	template<EngineDerivedFromComp T>
	inline T* casted_comp_at_fn(
		EntId id, const std::string& key, FileNum file_num
	) {
		return static_cast<T*>(comp_at_fn(id, key, file_num).get());
	}
	template<EngineDerivedFromComp T>
	inline T* casted_comp_at_fn(EntId id, FileNum file_num) {
		return casted_comp_at_fn<T>(id, T::KIND_STR, file_num);
	}
	//--------
	template<EngineDerivedFromComp T>
	inline T* casted_comp_at(EntId id, const std::string& key) {
		return casted_comp_at_fn<T>(id, key, curr_file_num);
	}
	template<EngineDerivedFromComp T>
	inline T* casted_comp_at(EntId id) {
		return casted_comp_at_fn<T>(id, curr_file_num);
	}
	//--------
	bool insert_comp_fn(
		EntId id, const std::string& key, CompSptr&& comp, FileNum file_num
	);
	inline bool insert_comp_fn(
		EntId id, CompSptr&& comp, FileNum file_num
	) {
		const std::string& KIND_STR = comp->kind_str();
		return insert_comp_fn(id, KIND_STR, std::move(comp), file_num);
	}
	EngineInsertSearchMultiRet insert_comp_fn(
		EntId id, CompUmap&& some_comp_umap, FileNum file_num
	);
	//--------
	inline bool insert_comp(
		EntId id, const std::string& key, CompSptr&& comp
	) {
		return insert_comp_fn(id, key, std::move(comp), curr_file_num);
	}
	inline bool insert_comp(EntId id, CompSptr&& comp) {
		return insert_comp_fn(id, std::move(comp), curr_file_num);
	}
	inline EngineInsertSearchMultiRet insert_comp(
		EntId id, CompUmap&& some_comp_umap
	) {
		return insert_comp_fn(id, std::move(some_comp_umap),
			curr_file_num);
	}
	//--------
	bool insert_or_replace_comp_fn(
		EntId id, const std::string& key, CompSptr&& comp, FileNum file_num
	);
	inline bool insert_or_replace_comp_fn(
		EntId id, CompSptr&& comp, FileNum file_num
	) {
		const std::string& KIND_STR = comp->kind_str();
		return insert_or_replace_comp_fn(id, KIND_STR, std::move(comp),
			file_num);
	}
	EngineInsertSearchMultiRet insert_or_replace_comp_fn(
		EntId id, CompUmap&& some_comp_umap, FileNum file_num
	);
	//--------
	inline bool insert_or_replace_comp_fn(
		EntId id, const std::string& key, CompSptr&& comp
	) {
		return insert_or_replace_comp_fn(id, key, std::move(comp),
			curr_file_num);
	}
	inline bool insert_or_replace_comp_fn(EntId id, CompSptr&& comp) {
		return insert_or_replace_comp_fn(id, std::move(comp),
			curr_file_num);
	}
	inline EngineInsertSearchMultiRet insert_or_replace_comp(
		EntId id, CompUmap&& some_comp_umap
	) {
		return insert_or_replace_comp_fn(id,
			std::move(some_comp_umap), curr_file_num);
	}
	//--------
	size_t erase_comp_fn(
		EntId id, const std::string& key, FileNum file_num
	);
	//template<EngineDerivedFromComp T>
	//inline size_t erase_comp_fn(EntId id, FileNum file_num) {
	//	return erase_comp_fn(id, T::KIND_STR, file_num);
	//}
	EngineEraseMultiRet erase_comp_fn(
		EntId id, const StrKeyUset& key_uset, FileNum file_num
	);

	//template<EngineDerivedFromComp... Ts>
	//inline EngineEraseMultiRet erase_comp_fn(EntId id, FileNum file_num) {
	//	StrKeyUset key_uset;
	//	(key_uset.insert(Ts::KIND_STR), ...);
	//	return erase_comp_fn(id, key_uset, file_num);
	//}
	//--------
	inline size_t erase_comp(EntId id, const std::string& key) {
		return erase_comp_fn(id, key, curr_file_num);
	}
	//template<EngineDerivedFromComp T>
	//inline size_t erase_comp(EntId id) {
	//	return erase_comp_fn<T>(id, curr_file_num);
	//}

	inline EngineEraseMultiRet erase_comp(
		EntId id, const StrKeyUset& key_uset
	) {
		return erase_comp_fn(id, key_uset, curr_file_num);
	}
	//template<EngineDerivedFromComp... Ts>
	//inline EngineEraseMultiRet erase_comp(EntId id) {
	//	return erase_comp_fn<Ts...>(id, curr_file_num);
	//}
	//--------
	bool insert_sys(const std::string& key, SysSptr&& sys);
	inline bool insert_sys(SysSptr&& sys) {
		const std::string& KIND_STR = sys->kind_str();
		return insert_sys(KIND_STR, std::move(sys));
	}
	EngineInsertSearchMultiRet insert_sys(SysUmap&& some_sys_umap);

	bool insert_or_replace_sys(const std::string& key, SysSptr&& sys);
	inline bool insert_or_replace_sys(SysSptr&& sys) {
		const std::string& KIND_STR = sys->kind_str();
		return insert_or_replace_sys(KIND_STR, std::move(sys));
	}
	EngineInsertSearchMultiRet insert_or_replace_sys(
		SysUmap&& some_sys_umap
	);

	size_t erase_sys(const std::string& key);
	//template<EngineDerivedFromSys T>
	//inline size_t erase_sys() {
	//	return erase_sys(T::KIND_STR);
	//}
	EngineEraseMultiRet erase_sys(const StrKeyUset& key_uset);

	//template<EngineDerivedFromSys... Ts>
	//inline EngineEraseMultiRet erase_sys() {
	//	StrKeyUset key_uset;
	//	(key_uset.insert(Ts::KIND_STR), ...);
	//	return erase_sys(key_uset);
	//}
	//--------
	inline bool has_ent_w_comp_fn(
		EntId id, const std::string& key, FileNum file_num
	) {
		return (engine_comp_umap_fn(file_num).contains(id)
			&& comp_umap_fn(id, file_num).contains(key));
	}
	//template<EngineDerivedFromComp T>
	//inline bool has_ent_w_comp_fn(EntId id, FileNum file_num) {
	//	return has_ent_w_comp_fn(id, T::KIND_STR, file_num);
	//}

	EngineInsertSearchMultiRet has_ent_w_comp_fn(
		EntId id, const StrKeyUset& key_uset, FileNum file_num
	);
	//template<EngineDerivedFromComp... Ts>
	//inline EngineInsertSearchMultiRet has_ent_w_comp_fn(
	//	EntId id, FileNum file_num
	//) {
	//	StrKeyUset key_uset;
	//	(key_uset.insert(Ts::KIND_STR), ...);
	//	return has_ent_w_comp_fn(id, key_uset, file_num);
	//}
	//--------
	inline bool has_ent_w_comp(EntId id, const std::string& key) {
		return has_ent_w_comp_fn(id, key, curr_file_num);
	}
	//template<EngineDerivedFromComp T>
	//inline bool has_ent_w_comp(EntId id) {
	//	return has_ent_w_comp_fn<T>(id, curr_file_num);
	//}

	inline EngineInsertSearchMultiRet has_ent_w_comp(
		EntId id, const StrKeyUset& key_uset
	) {
		return has_ent_w_comp_fn(id, key_uset, curr_file_num);
	}
	//template<EngineDerivedFromComp... Ts>
	//inline EngineInsertSearchMultiRet has_ent_w_comp(EntId id) {
	//	return has_ent_w_comp_fn<Ts...>(id, curr_file_num);
	//}
	//--------
	void tick();
	//--------
	inline EntId& next_ent_id_fn(FileNum file_num) {
		return _next_ent_id_darr.data.at(sel_file_num(file_num));
	}
	inline const EntId& next_ent_id_fn(FileNum file_num) const {
		return _next_ent_id_darr.data.at(sel_file_num(file_num));
	}

	inline EntId& next_ent_id() {
		return next_ent_id_fn(curr_file_num);
	}
	inline const EntId& next_ent_id() const {
		return next_ent_id_fn(curr_file_num);
	}
	//--------
	inline EntIdUset& to_destroy_uset_fn(FileNum file_num) {
		return _to_destroy_uset_darr.data.at(sel_file_num(file_num));
	}
	inline const EntIdUset& to_destroy_uset_fn(FileNum file_num) const {
		return _to_destroy_uset_darr.data.at(sel_file_num(file_num));
	}

	inline EntIdUset& to_destroy_uset() {
		return to_destroy_uset_fn(curr_file_num);
	}
	inline const EntIdUset& to_destroy_uset() const {
		return to_destroy_uset_fn(curr_file_num);
	}
	//--------
	inline EngineCompUmap& engine_comp_umap_fn(FileNum file_num) {
		return _engine_comp_umap_darr.data.at(sel_file_num(file_num));
	}
	inline const EngineCompUmap& engine_comp_umap_fn(
		FileNum file_num
	) const {
		return _engine_comp_umap_darr.data.at(sel_file_num(file_num));
	}

	inline EngineCompUmap& engine_comp_umap() {
		return engine_comp_umap_fn(curr_file_num);
	}
	inline const EngineCompUmap& engine_comp_umap() const {
		return engine_comp_umap_fn(curr_file_num);
	}
	//--------
	inline FileNum sel_file_num(FileNum some_file_num) const {
		//return (some_file_num == USE_CURR_FILE_NUM)
		//	? curr_file_num
		//	: some_file_num;
		switch (some_file_num) {
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
	GEN_GETTER_BY_VAL(next_ent_id_darr);
	GEN_GETTER_BY_CON_REF(to_destroy_uset_darr);
	GEN_GETTER_BY_VAL(num_files);
	GEN_GETTER_BY_CON_REF(engine_comp_umap_darr);
	GEN_GETTER_BY_CON_REF(sys_umap);
	//--------
//pubic:		// functions
//	inline FileNum sel_file_num(FileNum some_file_num) const {
//		//return (some_file_num == USE_CURR_FILE_NUM)
//		//	? curr_file_num
//		//	: some_file_num;
//	}
};
//--------
inline EntRef::EntRef(
	Engine* s_engine=nullptr, EntId s_id=ENT_NULL_ID,
	FileNum s_file_num=Engine::USE_CURR_FILE_NUM
)
	: _engine(s_engine), _id(s_id), _file_num(s_file_num) {
}
inline CompUmap& EntRef::comp_umap_fn() const {
	return _engine->comp_umap_fn(id(), file_num());
}
inline bool EntRef::insert_comp_fn(const std::string& key, CompSptr&& comp)
const {
	return _engine->insert_comp_fn(id(), key, std::move(comp), file_num());
}
inline bool EntRef::insert_or_replace_comp_fn(
	const std::string& key, CompSptr&& comp
) const {
	return _engine->insert_or_replace_comp_fn(id(), key, std::move(comp),
		file_num());
}
inline size_t EntRef::erase_comp_fn(const std::string& key) const {
	return _engine->erase_comp_fn(id(), key, file_num());
}
//--------
} // namespace ecs
} // namespace game
} // namespace liborangepower

#endif		// liborangepower_game_stuff_ecs_classes_hpp
