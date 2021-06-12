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
const CompMap& comp_map() const
{
	return _engine->comp_map(id());
}
//--------
std::string Comp::base_kind_str() const
{
	return "";
}
//--------
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

EntIdVec Engine::ent_id_vec_from_keys
	(const std::vector<std::string>& key_vec) const
{
	EntIdVec ret;

	for (auto&& pair: _engine_comp_map)
	{
		auto& the_comp_map = comp_map(pair.first);

		for (const auto& key: key_vec)
		{
			if (the_comp_map.contains(key))
			{
				ret.push_back(pair.first);

				// The `break` is there to speed 
				break;
			}
		}
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
