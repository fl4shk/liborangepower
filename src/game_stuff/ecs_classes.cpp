#include "ecs_classes.hpp"
#include "../misc/misc_output_funcs.hpp"
#include "../binser/serialize_defines.hpp"
#include "../metaprog_defines.hpp"

namespace liborangepower {
namespace game {
namespace ecs {
//--------
//EngineCompUmapValue::EngineCompUmapValue() {
//}
//EngineCompUmapValue::EngineCompUmapValue(
//	FileNum s_file_num, CompMapSptr&& s_comp_umap_uptr
//)
//	: file_num(s_file_num), comp_umap_uptr(std::move(s_comp_umap_uptr)) {
//}
//EngineCompUmapValue::~EngineCompUmapValue() {
//}
//--------
//--------
std::string Comp::kind_str() const {
	throw std::runtime_error(sconcat
		("liborangepower::game::ecs::Comp::kind_str(): Error: ",
		"this function is not supposed to be called. Did a derived class ",
		"not implement this function?"));

	return "";
}
Comp::operator binser::Value () const {
	binser::Value ret;

	MEMB_LIST_ECS_COMP(BINSER_MEMB_SERIALIZE);

	return ret;
}

const std::string NonSerializable::KIND_STR("NonSerializable");
std::string NonSerializable::kind_str() const {
	return KIND_STR;
}
//--------
//Sys::Sys(const binser::Value& bv) {
//	MEMB_LIST_ECS_SYS(BINSER_MEMB_DESERIALIZE);
//}
std::string Sys::kind_str() const {
	throw std::runtime_error(sconcat
		("liborangepower::game::ecs::Sys::kind_str(): Error: ",
		"this function is not supposed to be called. Did a derived class ",
		"not implement this function?"));
	return "";
}
//Sys::operator binser::Value () const {
//	binser::Value ret;
//
//	MEMB_LIST_ECS_SYS(BINSER_MEMB_SERIALIZE);
//
//	return ret;
//}

void Sys::prep_init() {
	_did_init = false;
	active.back_up_and_update(false);
	active.back_up_and_update(true);
}

void Sys::_init(Engine* ecs_engine) {
	// This should be implemented by derived classes

	// Example:
	//	_init_start(ecs_engine);
	//	// unique logic for the derived class goes here
}

void Sys::tick(Engine* ecs_engine) {
	// This should be implemented by derived classes

	// Example:
	//	if (_tick_helper(ecs_engine, true)) {
	//		// unique logic for the derived class goes here
	//	}
}

bool Sys::_tick_helper(Engine* ecs_engine, bool cond) {
	if (cond) {
		if (active() && active.has_changed()) {
			active.back_up();

			return false;
		} else if (active()) {
			if (!_did_init) {
				_init(ecs_engine);
			}
			return true;
		}
	}
	return false;
}
//--------
Engine::Engine(u64 s_num_files)
	: _next_ent_id_darr
	({
		.data=std::vector<EntId>(s_num_files, 0),
		.checked_size=s_num_files
	}),
	_to_destroy_uset_darr
	({
		.data=std::vector<EntIdUset>(s_num_files, EntIdUset()),
		.checked_size=s_num_files
	}),
	_num_files(s_num_files)
	//_engine_comp_umap_darr(s_num_files, EngineCompUmap())
{
	_engine_comp_umap_darr.checked_size = s_num_files;
	for (FileNum i=0; i<_num_files; ++i) {
		_engine_comp_umap_darr.data.push_back(EngineCompUmap());
	}
}
Engine::~Engine() {}
//--------
Engine::operator binser::Value () const {
	binser::Value ret;

	MEMB_AUTOSER_LIST_ECS_ENGINE(BINSER_MEMB_SERIALIZE);

	//for (Json::ArrayIndex i=0;
	//	i<static_cast<Json::ArrayIndex>(_num_files);
	//	++i)
	binser::ValueDarr darr;
	for (FileNum i=0; i<_num_files; ++i) {
		//Json::Value& jv_ecmap = ret["_engine_comp_umap_darr"][i];

		//for (const auto& ent_pair: _engine_comp_umap_darr.at(i)) {
		//	//Json::Value& ent_jv = ret["_engine_comp_umap"]
		//	//	[sconcat(ent_pair.first)];

		//	//if (!ent_pair.second.contains(NonSerializable::KIND_STR)) {
		//	//	//Json::Value& ent_jv = inner_jv[sconcat(ent_pair.first)];

		//	//	//for (const auto& comp_pair: *ent_pair.second) {
		//	//	//	set_jv_memb(ent_jv, comp_pair.first,
		//	//	//		*comp_pair.second);
		//	//	//}
		//	//}
		//}

		binser::Value bv_ecmap;

		binser::set_bv_map_like_std_container(bv_ecmap,
			_engine_comp_umap_darr.data.at(i),
			[](
				const typename EngineCompUmap::value_type& ent_pair
			) -> bool {
				return ent_pair.second.contains(NonSerializable::KIND_STR);
			});
		darr.push_back(binser::ValueSptr(new binser::Value
			(std::move(bv_ecmap))));
	}
	ret.insert("_engine_comp_umap_darr", std::move(darr));
	//MEMB_SER_LIST_ECS_ENGINE(JSON_MEMB_SERIALIZE);

	return ret;
}
//--------
void Engine::copy_file() {
	if (src_file_num < 0 || src_file_num >= _num_files) {
		throw std::out_of_range(sconcat
			("liborangepower::game::ecs::Engine::copy_file(): Error: "
			"Invalid `src_file_num`: ",
			src_file_num, " ", _num_files));
	}
	if (copy_dst_file_num < 0 || copy_dst_file_num >= _num_files) {
		throw std::out_of_range(sconcat
			("liborangepower::game::ecs::Engine::copy_file(): Error: "
			"Invalid `copy_dst_file_num`: ",
			copy_dst_file_num, " ", _num_files));
	}
	_next_ent_id_darr.data.at(copy_dst_file_num)
		= _next_ent_id_darr.data.at(src_file_num);
	_to_destroy_uset_darr.data.at(copy_dst_file_num)
		= _to_destroy_uset_darr.data.at(src_file_num);
	_engine_comp_umap_darr.data.at(copy_dst_file_num)
		= _engine_comp_umap_darr.data.at(src_file_num);
}
void Engine::erase_file() {
	if (src_file_num < 0 || src_file_num >= _num_files) {
		throw std::out_of_range(sconcat
			("liborangepower::game::ecs::Engine::copy_file(): Error: "
			"Invalid `src_file_num`: ",
			src_file_num, " ", _num_files));
	}
	_next_ent_id_darr.data.at(src_file_num) = EntId();
	_to_destroy_uset_darr.data.at(src_file_num) = EntIdUset();
	_engine_comp_umap_darr.data.at(src_file_num) = EngineCompUmap();
}
//--------
//void Engine::deserialize(const Json::Value& jv) {
//	MEMB_LIST_ECS_ENGINE(JSON_MEMB_DESERIALIZE);
//}
//void Engine::_autoser_deserialize(const Json::Value& jv) {
//}

//template<EngineDerivedFromComp FirstCompT,
//	EngineDerivedFromComp... RemCompTs>
//void Engine::_ent_deserialize(const Json::Value& jv)
void Engine::deserialize(const binser::Value& bv) {
	MEMB_AUTOSER_LIST_ECS_ENGINE(BINSER_MEMB_DESERIALIZE);
	get_bv_memb(_engine_comp_umap_darr, bv, "_engine_comp_umap_darr",
		&_comp_deser_func_umap);

	//MEMB_SER_LIST_ECS_ENGINE(JSON_MEMB_DESERIALIZE);

	//get_jv_memb(_next_ent_id_darr, jv, "_next_ent_id_darr", std::nullopt);
	//get_jv_memb(_to_destroy_uset_darr, jv, "_to_destroy_uset_darr",
	//	std::nullopt);
	//get_jv_memb(_num_files, jv, "_num_files", std::nullopt);
	////get_jv_memb<decltype(_engine_comp_umap_darr), Comp>
	////	(_engine_comp_umap_darr, jv, "_engine_comp_umap_darr",
	////	&_comp_deser_func_umap);
	//get_jv_memb(_engine_comp_umap_darr, jv, "_engine_comp_umap_darr",
	//	&_comp_deser_func_umap);

}
////template<EngineDerivedFromSys FirstSysT,
////	EngineDerivedFromSys... RemSysTs>
//void Engine::_sys_deserialize(const Json::Value& jv) {
//	_sys_umap.clear();
//
//	const auto& sys_name_darr = jv["_sys_umap"].getMemberNames();
//	for (const auto& sys_name: sys_name_darr) {
//		const Json::Value& sys_jv = jv["_sys_umap"][sys_name];
//
//		//_inner_sys_deserialize<FirstSysT, RemSysTs...>
//		//	(sys_jv, sys_name);
//		//insert_sys(sys_name, SysSptr(new FirstSysT(sys_jv)));
//		insert_sys(sys_name,
//			_sys_deser_func_umap.at(sys_name)(sys_jv));
//	}
//}
//--------
//void Engine::_inner_create(EntId id, FileNum file_num, bool mk_non_ser)
void Engine::_inner_create_fn(
	EntId id, FileNum file_num, std::optional<CompUmap>&& s_comp_umap
) {
	//engine_comp_umap_fn(file_num)[id] = CompMapSptr(new CompUmap());
	//engine_comp_umap_fn(file_num)[id] = CompUmap();
	engine_comp_umap_fn(file_num)[id]
		= !s_comp_umap ? CompUmap() : std::move(*s_comp_umap);

	//if (mk_non_ser) {
	//	insert_comp_fn(id, CompSptr(new NonSerializable()), file_num);
	//}
}
//EntId Engine::create(FileNum file_num, bool mk_non_ser)
EntId Engine::create_fn(
	FileNum file_num, std::optional<CompUmap>&& s_comp_umap
) {
	//_inner_create(next_ent_id_fn(file_num), file_num, mk_non_ser);
	_inner_create_fn(next_ent_id_fn(file_num), file_num,
		std::move(s_comp_umap));

	////_ent_id_to_comp_key_umap[next_ent_id_fn(file_num)]
	////	= std::set<std::string>();


	//const EntId& id = next_ent_id_fn(file_num);

	////engine_comp_umap_fn(file_num)[id] = CompMapSptr(new CompUmap());
	//engine_comp_umap_fn(file_num)[id] = CompUmap();

	//if (mk_non_ser) {
	//	insert_comp_fn(id, CompSptr(new NonSerializable()), file_num);
	//}

	return (next_ent_id_fn(file_num)++);
}
EntId Engine::create_singleton_any_fn(
	FileNum file_num, CompUmap&& s_comp_umap, const std::string& func_name
) {
	StrKeyUset key_uset;

	for (const auto& pair: s_comp_umap) {
		key_uset.insert(pair.first);
	}

	force_singleton_any_fn(key_uset, func_name, file_num);

	return create_fn(file_num, std::move(s_comp_umap));
}
EntId Engine::create_singleton_all_fn(
	FileNum file_num, CompUmap&& s_comp_umap, const std::string& func_name
) {
	StrKeyUset key_uset;

	for (const auto& pair: s_comp_umap) {
		key_uset.insert(pair.first);
	}

	force_singleton_all_fn(key_uset, func_name, file_num);

	return create_fn(file_num, std::move(s_comp_umap));
}
void Engine::force_singleton_any_fn(
	const StrKeyUset& key_uset, const std::string& func_name,
	FileNum file_num
) {
	const auto& ent_id_darr = ent_id_darr_from_keys_any_fn(key_uset,
		file_num);

	if (ent_id_darr.size() > 0) {
		std::string err_msg(sconcat
			("liborangepower::game::ecs::Engine"
				"::force_singleton_any_fn(): ",
			func_name, "(): ",
			"Error: ",
			"Found existing entities: {"));

		if (std::stringstream sstm; true) {
			misc_output::osprint_arr(sstm, ent_id_darr.data(),
				ent_id_darr.size());
			err_msg += sstm.str();
		}
		err_msg += "}";

		throw std::runtime_error(err_msg);
	}
}

void Engine::force_singleton_all_fn(
	const StrKeyUset& key_uset, const std::string& func_name,
	FileNum file_num
) {
	const auto& ent_id_darr = ent_id_darr_from_keys_all_fn(key_uset,
		file_num);

	if (ent_id_darr.size() > 0) {
		std::string err_msg(sconcat
			("liborangepower::game::ecs::Engine"
				"::force_singleton_all_fn(): ",
			func_name, "(): ",
			"Error: ",
			"Found existing entities: {"));

		if (std::stringstream sstm; true) {
			misc_output::osprint_arr(sstm, ent_id_darr.data(),
				ent_id_darr.size());
			err_msg += sstm.str();
		}
		err_msg += "}";

		throw std::runtime_error(err_msg);
	}
}


void Engine::destroy_now_fn(EntId id, FileNum file_num) {
	comp_umap_fn(id, file_num).clear();
	if (to_destroy_uset_fn(file_num).contains(id)) {
		to_destroy_uset_fn(file_num).erase(id);
	}
}
//void Engine::destroy_now_fn(FileNum file_num) {
//	for (auto id: to_destroy_uset_fn(file_num)) {
//		to_destroy_uset_fn();
//	}
//}

//void Engine::destroy_scheduled_fn(EntId id, FileNum file_num) {
//	if (to_destroy_uset_fn(file_num).contains(id)) {
//		comp_umap_fn(id, file_num).clear();
//		to_destroy_uset_fn(file_num).erase(id);
//	}
//}
void Engine::destroy_scheduled_fn(FileNum file_num) {
	for (auto id: to_destroy_uset_fn(file_num)) {
		comp_umap_fn(id, file_num).clear();
	}
	to_destroy_uset_fn(file_num).clear();
}

void Engine::destroy_all_fn(FileNum file_num) {
	next_ent_id_fn(file_num) = EntId();
	engine_comp_umap_fn(file_num).clear();
}

void Engine::destroy_all_every_fn() {
	for (FileNum i=0; i<num_files(); ++i) {
		destroy_all_fn(i);
	}
}

//--------
EntIdDarr Engine::ent_id_darr_from_keys_any_fn(
	const StrKeyUset& key_uset, FileNum file_num
) {
	EntIdDarr ret;

	auto& ecm = engine_comp_umap_fn(file_num);
	for (auto&& pair: ecm) {
		auto& the_comp_umap = comp_umap_fn(pair.first, file_num);

		for (const auto& key: key_uset) {
			if (the_comp_umap.contains(key)) {
				ret.push_back(pair.first);

				break;
			}
		}
	}

	return ret;
}
EntIdUset Engine::ent_id_uset_from_keys_any_fn(
	const StrKeyUset& key_uset, FileNum file_num
) {
	//const EntIdDarr darr(ent_id_darr_from_keys_any_fn(key_uset, file_num));

	//EntIdUset ret;

	//for (const auto& ent_id: darr) {
	//	ret.insert(ent_id);
	//}

	//return ret;
	EntIdUset ret;

	auto& ecm = engine_comp_umap_fn(file_num);
	for (auto&& pair: ecm) {
		auto& the_comp_umap = comp_umap_fn(pair.first, file_num);

		for (const auto& key: key_uset) {
			if (the_comp_umap.contains(key)) {
				ret.insert(pair.first);

				break;
			}
		}
	}

	return ret;
}

EntIdDarr Engine::ent_id_darr_from_keys_all_fn(
	const StrKeyUset& key_uset, FileNum file_num
) {
	EntIdDarr ret;

	auto& ecm = engine_comp_umap_fn(file_num);
	for (auto&& pair: ecm) {
		auto& the_comp_umap = comp_umap_fn(pair.first, file_num);

		bool all = true;

		for (const auto& key: key_uset) {
			if (!the_comp_umap.contains(key)) {
				all = false;
				break;
			}
		}
		if (all) {
			ret.push_back(pair.first);
		}
	}

	return ret;
}
EntIdUset Engine::ent_id_uset_from_keys_all_fn(
	const StrKeyUset& key_uset, FileNum file_num
) {
	//const EntIdDarr darr(ent_id_darr_from_keys_all_fn(key_uset, file_num));

	//EntIdUset ret;

	//for (const auto& ent_id: darr) {
	//	ret.insert(ent_id);
	//}

	//return ret;
	EntIdUset ret;

	auto& ecm = engine_comp_umap_fn(file_num);
	for (auto&& pair: ecm) {
		auto& the_comp_umap = comp_umap_fn(pair.first, file_num);

		bool all = true;

		for (const auto& key: key_uset) {
			if (!the_comp_umap.contains(key)) {
				all = false;
				break;
			}
		}
		if (all) {
			ret.insert(pair.first);
		}
	}

	return ret;
}
//--------
bool Engine::insert_comp_fn(
	EntId id, const std::string& key, CompSptr&& comp, FileNum file_num
) {
	auto& the_comp_umap = comp_umap_fn(id, file_num);

	if (!the_comp_umap.contains(key)) {
		the_comp_umap[key] = std::move(comp);
		//_ent_id_to_comp_key_umap.at(id).insert(key);
		return false;
	}
	return true;
}
EngineInsertSearchMultiRet Engine::insert_comp_fn(
	EntId id, CompUmap&& some_comp_umap, FileNum file_num
) {
	EngineInsertSearchMultiRet ret;

	ret.first = false;

	for (auto& pair: some_comp_umap) {
		const bool temp = insert_comp_fn(id, pair.first,
			std::move(pair.second), file_num);

		ret.second[pair.first] = temp;

		if (temp) {
			ret.first = true;
		}
	}

	return ret;
}
bool Engine::insert_or_replace_comp_fn(
	EntId id, const std::string& key, CompSptr&& comp, FileNum file_num
) {
	auto& the_comp_umap = comp_umap_fn(id, file_num);
	//_ent_id_to_comp_key_umap.at(id).insert(key);

	const bool ret = the_comp_umap.contains(key);
	the_comp_umap[key] = std::move(comp);
	return ret;
}
EngineInsertSearchMultiRet Engine::insert_or_replace_comp_fn(
	EntId id, CompUmap&& some_comp_umap, FileNum file_num
) {
	EngineInsertSearchMultiRet ret;

	ret.first = false;

	for (auto& pair: some_comp_umap) {
		const bool temp = insert_or_replace_comp_fn(id, pair.first,
			std::move(pair.second), file_num);

		ret.second[pair.first] = temp;

		if (temp) {
			ret.first = true;
		}
	}

	return ret;
}
size_t Engine::erase_comp_fn(
	EntId id, const std::string& key, FileNum file_num
) {
	auto& the_comp_umap = comp_umap_fn(id, file_num);
	// A bad key will be handled by the `erase()` call itself.
	const auto ret = the_comp_umap.erase(key);
	//_ent_id_to_comp_key_umap.at(id).erase(key);
	return ret;
}
EngineEraseMultiRet Engine::erase_comp_fn(
	EntId id, const StrKeyUset& key_uset, FileNum file_num
) {
	EngineEraseMultiRet ret;

	for (const auto& key: key_uset) {
		ret[key] = erase_comp_fn(id, key, file_num);
	}

	return ret;
}
//--------
bool Engine::insert_sys(const std::string& key, SysSptr&& sys) {
	if (!_sys_umap.contains(key)) {
		_sys_umap[key] = std::move(sys);
		return false;
	}
	return true;
}
EngineInsertSearchMultiRet Engine::insert_sys(SysUmap&& some_sys_umap) {
	EngineInsertSearchMultiRet ret;

	ret.first = false;

	for (auto& pair: some_sys_umap) {
		const bool temp = insert_sys(pair.first, std::move(pair.second));

		ret.second[pair.first] = temp;

		if (temp) {
			ret.first = true;
		}
	}

	return ret;
}
bool Engine::insert_or_replace_sys(const std::string& key, SysSptr&& sys) {
	const bool ret = _sys_umap.contains(key);
	_sys_umap[key] = std::move(sys);
	return ret;
}
EngineInsertSearchMultiRet Engine::insert_or_replace_sys(
	SysUmap&& some_sys_umap
) {
	EngineInsertSearchMultiRet ret;

	ret.first = false;

	for (auto& pair: some_sys_umap) {
		const bool temp = insert_or_replace_sys(pair.first,
			std::move(pair.second));

		ret.second[pair.first] = temp;

		if (temp) {
			ret.first = true;
		}
	}

	return ret;
}
size_t Engine::erase_sys(const std::string& key) {
	return _sys_umap.erase(key);
}
EngineEraseMultiRet Engine::erase_sys(const StrKeyUset& key_uset) {
	EngineEraseMultiRet ret;

	for (const auto& key: key_uset) {
		ret[key] = erase_sys(key);
	}

	return ret;
}

EngineInsertSearchMultiRet Engine::has_ent_w_comp_fn(
	EntId id, const StrKeyUset& key_uset, FileNum file_num
) {
	EngineInsertSearchMultiRet ret;

	ret.first = false;

	for (auto& key: key_uset) {
		const bool temp = has_ent_w_comp_fn(id, key, file_num);

		ret.second[key] = temp;

		if (temp) {
			ret.first = true;
		}
	}

	return ret;
}
void Engine::tick(
	const std::optional<std::string>& start_sys_key,
	const std::optional<std::string>& end_sys_key
) {
	if (start_sys_key) {
		_sys_umap.at(*start_sys_key)->tick(this);
	}
	for (auto&& pair: _sys_umap) {
		if (
			(
				!start_sys_key
				|| pair.first != *start_sys_key
			) && (
				!end_sys_key
				|| pair.first != *end_sys_key
			)
		) {
			pair.second->tick(this);
		}
	}
	if (end_sys_key) {
		_sys_umap.at(*end_sys_key)->tick(this);
	}
}
//--------
} // namespace ecs
} // namespace game
} // namespace liborangepower
