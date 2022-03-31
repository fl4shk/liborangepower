#include "ecs_classes.hpp"
#include "../metaprog_defines.hpp"

namespace liborangepower
{
namespace game
{
namespace ecs
{
//--------
//EngineCompMapValue::EngineCompMapValue()
//{
//}
//EngineCompMapValue::EngineCompMapValue(int s_file_num,
//	CompMapSptr&& s_comp_map_uptr)
//	: file_num(s_file_num), comp_map_uptr(std::move(s_comp_map_uptr))
//{
//}
//EngineCompMapValue::~EngineCompMapValue()
//{
//}
//--------
std::string Comp::kind_str() const
{
	return "";
}
Comp::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_ECS_COMP(BINSER_MEMB_SERIALIZE);

	return ret;
}

const std::string NonSerializable::KIND_STR("NonSerializable");
std::string NonSerializable::kind_str() const
{
	return KIND_STR;
}
//--------
//Sys::Sys(const binser::Value& bv)
//{
//	MEMB_LIST_ECS_SYS(BINSER_MEMB_DESERIALIZE);
//}
std::string Sys::kind_str() const
{
	return "";
}
//Sys::operator binser::Value () const
//{
//	binser::Value ret;
//
//	MEMB_LIST_ECS_SYS(BINSER_MEMB_SERIALIZE);
//
//	return ret;
//}

void Sys::prep_init()
{
	_did_init = false;
	game_mode_active.back_up_and_update(false);
	game_mode_active.back_up_and_update(true);
}
void Sys::init(Engine* ecs_engine)
{
	// This should be implemented by derived classes

	// Example:
	//	_init_start(ecs_engine);
	//	// unique logic for the derived class goes here
}
void Sys::tick(Engine* ecs_engine)
{
	// This should be implemented by derived classes

	// Example:
	//	if (_tick_helper(ecs_engine, true))
	//	{
	//		// unique logic for the derived class goes here
	//	}
}

bool Sys::_tick_helper(Engine* ecs_engine, bool cond)
{
	if (cond)
	{
		if (game_mode_active() && game_mode_active.has_changed())
		{
			game_mode_active.back_up();

			return false;
		}
		else if (game_mode_active())
		{
			if (!_did_init)
			{
				init(ecs_engine);
			}

			return true;
		}
	}
	return false;
}
//--------
Engine::Engine(integer_types::u64 s_num_files)
	: _next_ent_id_vec(s_num_files, 0),
	_to_destroy_set_vec(s_num_files, EntIdSet()),
	_num_files(s_num_files)
	//_engine_comp_map_vec(s_num_files, EngineCompMap())
{
	for (integer_types::u64 i=0; i<_num_files; ++i)
	{
		_engine_comp_map_vec.push_back(EngineCompMap());
	}
}
Engine::~Engine()
{
}
//--------
Engine::operator binser::Value () const
{
	binser::Value ret;

	MEMB_AUTOSER_LIST_ECS_ENGINE(BINSER_MEMB_SERIALIZE);

	//for (Json::ArrayIndex i=0;
	//	i<static_cast<Json::ArrayIndex>(_num_files);
	//	++i)
	binser::ValueVec vec;
	for (decltype(_num_files) i=0; i<_num_files; ++i)
	{
		//Json::Value& jv_ecmap = ret["_engine_comp_map_vec"][i];

		//for (const auto& ent_pair: _engine_comp_map_vec.at(i))
		//{
		//	//Json::Value& ent_jv = ret["_engine_comp_map"]
		//	//	[sconcat(ent_pair.first)];

		//	//if (!ent_pair.second.contains(NonSerializable::KIND_STR))
		//	//{
		//	//	//Json::Value& ent_jv = inner_jv[sconcat(ent_pair.first)];

		//	//	//for (const auto& comp_pair: *ent_pair.second)
		//	//	//{
		//	//	//	set_jv_memb(ent_jv, comp_pair.first,
		//	//	//		*comp_pair.second);
		//	//	//}
		//	//}
		//}

		binser::Value bv_ecmap;

		binser::set_bv_map_like_std_container(bv_ecmap,
			_engine_comp_map_vec.at(i),
			[](const typename EngineCompMap::value_type& ent_pair) -> bool
			{
				return ent_pair.second.contains
					(NonSerializable::KIND_STR);
			});
		vec.push_back(binser::ValueSptr(new binser::Value
			(std::move(bv_ecmap))));
	}
	ret.insert("_engine_comp_map_vec", std::move(vec));
	//MEMB_SER_LIST_ECS_ENGINE(JSON_MEMB_SERIALIZE);

	return ret;
}
//--------
//void Engine::deserialize(const Json::Value& jv)
//{
//	MEMB_LIST_ECS_ENGINE(JSON_MEMB_DESERIALIZE);
//}
//void Engine::_autoser_deserialize(const Json::Value& jv)
//{
//}

//template<EngineDerivedFromComp FirstCompT,
//	EngineDerivedFromComp... RemCompTs>
//void Engine::_ent_deserialize(const Json::Value& jv)
void Engine::deserialize(const binser::Value& bv)
{
	MEMB_AUTOSER_LIST_ECS_ENGINE(BINSER_MEMB_DESERIALIZE);
	get_bv_memb(_engine_comp_map_vec, bv, "_engine_comp_map_vec",
		&_comp_deser_func_map);
	//MEMB_SER_LIST_ECS_ENGINE(JSON_MEMB_DESERIALIZE);

	//get_jv_memb(_next_ent_id_vec, jv, "_next_ent_id_vec", std::nullopt);
	//get_jv_memb(_to_destroy_set_vec, jv, "_to_destroy_set_vec",
	//	std::nullopt);
	//get_jv_memb(_num_files, jv, "_num_files", std::nullopt);
	////get_jv_memb<decltype(_engine_comp_map_vec), Comp>
	////	(_engine_comp_map_vec, jv, "_engine_comp_map_vec",
	////	&_comp_deser_func_map);
	//get_jv_memb(_engine_comp_map_vec, jv, "_engine_comp_map_vec",
	//	&_comp_deser_func_map);

}
////template<EngineDerivedFromSys FirstSysT,
////	EngineDerivedFromSys... RemSysTs>
//void Engine::_sys_deserialize(const Json::Value& jv)
//{
//	_sys_map.clear();
//
//	const auto& sys_name_vec = jv["_sys_map"].getMemberNames();
//	for (const auto& sys_name: sys_name_vec)
//	{
//		const Json::Value& sys_jv = jv["_sys_map"][sys_name];
//
//		//_inner_sys_deserialize<FirstSysT, RemSysTs...>
//		//	(sys_jv, sys_name);
//		//insert_sys(sys_name, SysSptr(new FirstSysT(sys_jv)));
//		insert_sys(sys_name,
//			_sys_deser_func_map.at(sys_name)(sys_jv));
//	}
//}
//--------
void Engine::_inner_create(EntId id, int file_num, bool mk_non_ser)
{
	//engine_comp_map(file_num)[id] = CompMapSptr(new CompMap());
	engine_comp_map(file_num)[id] = CompMap();

	if (mk_non_ser)
	{
		insert_comp(id, CompSptr(new NonSerializable()), file_num);
	}
}
EntId Engine::create(int file_num, bool mk_non_ser)
{
	_inner_create(next_ent_id(file_num), file_num, mk_non_ser);

	////_ent_id_to_comp_key_map[next_ent_id(file_num)]
	////	= std::set<std::string>();


	//const EntId& id = next_ent_id(file_num);

	////engine_comp_map(file_num)[id] = CompMapSptr(new CompMap());
	//engine_comp_map(file_num)[id] = CompMap();

	//if (mk_non_ser)
	//{
	//	insert_comp(id, CompSptr(new NonSerializable()), file_num);
	//}

	return (next_ent_id(file_num)++);
}
void Engine::destroy(EntId id, int file_num)
{
	comp_map(id, file_num).clear();
	if (to_destroy_set(file_num).contains(id))
	{
		to_destroy_set(file_num).erase(id);
	}
}
void Engine::destroy(int file_num)
{
	for (auto id: to_destroy_set(file_num))
	{
		comp_map(id, file_num).clear();
	}
	to_destroy_set(file_num).clear();
}

void Engine::destroy_all(int file_num)
{
	next_ent_id(file_num) = EntId();
	engine_comp_map(file_num).clear();
}

void Engine::destroy_all()
{
	for (decltype(_num_files) i=0; i<num_files(); ++i)
	{
		destroy_all(i);
	}
}

//--------
EntIdVec Engine::ent_id_vec_from_keys_any(const StrKeySet& key_set,
	int file_num)
{
	EntIdVec ret;

	for (auto&& pair: engine_comp_map(file_num))
	{
		auto& the_comp_map = comp_map(pair.first, file_num);

		for (const auto& key: key_set)
		{
			if (the_comp_map.contains(key))
			{
				ret.push_back(pair.first);

				break;
			}
		}
	}

	return ret;
}
EntIdSet Engine::ent_id_set_from_keys_any(const StrKeySet& key_set,
	int file_num)
{
	const EntIdVec vec(ent_id_vec_from_keys_any(key_set, file_num));

	EntIdSet ret;

	for (const auto& ent_id: vec)
	{
		ret.insert(ent_id);
	}

	return ret;
}

EntIdVec Engine::ent_id_vec_from_keys_all(const StrKeySet& key_set,
	int file_num)
{
	EntIdVec ret;

	for (auto&& pair: engine_comp_map(file_num))
	{
		auto& the_comp_map = comp_map(pair.first, file_num);

		bool all = true;

		for (const auto& key: key_set)
		{
			if (!the_comp_map.contains(key))
			{
				all = false;
				break;
			}
		}
		if (all)
		{
			ret.push_back(pair.first);
		}
	}

	return ret;
}
EntIdSet Engine::ent_id_set_from_keys_all(const StrKeySet& key_set,
	int file_num)
{
	const EntIdVec vec(ent_id_vec_from_keys_all(key_set, file_num));

	EntIdSet ret;

	for (const auto& ent_id: vec)
	{
		ret.insert(ent_id);
	}

	return ret;
}
//--------
bool Engine::insert_comp(EntId id, const std::string& key, CompSptr&& comp,
	int file_num)
{
	auto& the_comp_map = comp_map(id, file_num);

	if (!the_comp_map.contains(key))
	{
		the_comp_map[key] = std::move(comp);
		//_ent_id_to_comp_key_map.at(id).insert(key);
		return false;
	}
	return true;
}
bool Engine::insert_or_replace_comp(EntId id, const std::string& key,
	CompSptr&& comp, int file_num)
{
	auto& the_comp_map = comp_map(id, file_num);
	//_ent_id_to_comp_key_map.at(id).insert(key);

	const bool ret = the_comp_map.contains(key);
	the_comp_map[key] = std::move(comp);
	return ret;
}
size_t Engine::erase_comp(EntId id, const std::string& key, int file_num)
{
	auto& the_comp_map = comp_map(id, file_num);
	// A bad key will be handled by the `erase()` call itself.
	const auto ret = the_comp_map.erase(key);
	//_ent_id_to_comp_key_map.at(id).erase(key);
	return ret;
}
//--------
bool Engine::insert_sys(const std::string& key, SysSptr&& sys)
{
	if (!_sys_map.contains(key))
	{
		_sys_map[key] = std::move(sys);
		return false;
	}
	return true;
}
bool Engine::insert_or_replace_sys(const std::string& key, SysSptr&& sys)
{
	const bool ret = _sys_map.contains(key);
	_sys_map[key] = std::move(sys);
	return ret;
}
size_t Engine::erase_sys(const std::string& key)
{
	return _sys_map.erase(key);
}

void Engine::tick()
{
	for (auto&& pair: _sys_map)
	{
		pair.second->tick(this);
	}
}
//--------
} // namespace ecs
} // namespace game
} // namespace liborangepower
