#include "ecs_classes.hpp"

namespace liborangepower
{

namespace game
{

namespace ecs
{
//--------
CompMap& Ent::comp_map() const
{
	return _engine->comp_map(id());
}
//--------
std::string Comp::kind_str() const
{
	return "";
}
//--------
std::string Sys::kind_str() const
{
	return "";
}
void Sys::tick(Engine* engine)
{
	// This should be implemented by derived classes
}
//--------
Engine::Engine()
{
}
Engine::~Engine()
{
}

EntId Engine::create()
{
	_engine_comp_map[_next_ent_id] = CompMapUptr(new CompMap());
	//_ent_id_to_comp_key_map[_next_ent_id] = std::set<std::string>();
	return (_next_ent_id++);
}
void Engine::destroy(EntId id)
{
	comp_map(id).clear();
	if (_to_destroy_set.contains(id))
	{
		_to_destroy_set.erase(id);
	}
}
void Engine::destroy()
{
	for (auto id: _to_destroy_set)
	{
		comp_map(id).clear();

		//for (const auto& key: _ent_id_to_comp_key_map.at(id))
		//{
		//	_comp_key_to_ent_id_map.at(key).erase(id);
		//}
		//_ent_id_to_comp_key_map.erase(id);
	}
	_to_destroy_set.clear();
}

EntIdVec Engine::ent_id_vec_from_keys_any(const StrKeySet& key_set) const
{
	EntIdVec ret;

	for (auto&& pair: _engine_comp_map)
	{
		auto& the_comp_map = comp_map(pair.first);

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
EntIdSet Engine::ent_id_set_from_keys_any(const StrKeySet& key_set) const
{
	const EntIdVec vec(ent_id_vec_from_keys_any(key_set));

	EntIdSet ret;

	for (const auto& ent_id: vec)
	{
		ret.insert(ent_id);
	}

	return ret;
}

EntIdVec Engine::ent_id_vec_from_keys_all(const StrKeySet& key_set) const
{
	EntIdVec ret;

	for (auto&& pair: _engine_comp_map)
	{
		auto& the_comp_map = comp_map(pair.first);

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
EntIdSet Engine::ent_id_set_from_keys_all(const StrKeySet& key_set) const
{
	const EntIdVec vec(ent_id_vec_from_keys_all(key_set));

	EntIdSet ret;

	for (const auto& ent_id: vec)
	{
		ret.insert(ent_id);
	}

	return ret;
}

bool Engine::insert_comp(EntId id, const std::string& key, CompUptr&& comp)
{
	auto& the_comp_map = comp_map(id);
	if (!the_comp_map.contains(key))
	{
		the_comp_map[key] = std::move(comp);
		//_ent_id_to_comp_key_map.at(id).insert(key);
		return false;
	}
	return true;
}
bool Engine::insert_or_replace_comp(EntId id, const std::string& key,
	CompUptr&& comp)
{
	auto& the_comp_map = comp_map(id);
	//_ent_id_to_comp_key_map.at(id).insert(key);

	const bool ret = the_comp_map.contains(key);
	the_comp_map[key] = std::move(comp);
	return ret;
}
size_t Engine::erase_comp(EntId id, const std::string& key)
{
	auto& the_comp_map = comp_map(id);
	// A bad key will be handled by the `erase()` call itself.
	const auto ret = the_comp_map.erase(key);
	//_ent_id_to_comp_key_map.at(id).erase(key);
	return ret;
}

bool Engine::insert_sys(const std::string& key, SysUptr&& sys)
{
	if (!_sys_map.contains(key))
	{
		_sys_map[key] = std::move(sys);
		return false;
	}
	return true;
}
bool Engine::insert_or_replace_sys(const std::string& key, SysUptr&& sys)
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
