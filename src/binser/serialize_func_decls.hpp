#ifndef liborangepower_binser_serialize_func_decls_hpp
#define liborangepower_binser_serialize_func_decls_hpp

#include "../misc/misc_includes.hpp"
#include "value_class.hpp"

namespace liborangepower {
namespace binser {
//--------
template<typename T>
inline void val_from_bv(T& ret, const Value& bv,
	const std::nullopt_t& some_nullopt);

template<typename T, typename BaseT>
inline void get_bv_memb(T& ret, const Value& bv,
	const std::string& name, FromBvFactoryFuncMap<BaseT>* func_map);
template<typename T>
inline void get_bv_memb(T& ret, const Value& bv,
	const std::string& name, const std::nullopt_t& some_nullopt);

template<typename TempT, typename RetT, typename BaseT>
inline void get_bv_memb_w_stat_cast(RetT& ret, const Value& bv,
	const std::string& name, FromBvFactoryFuncMap<BaseT>* func_map);
template<typename TempT, typename RetT>
inline void get_bv_memb_w_stat_cast(RetT& ret, const Value& bv,
	const std::string& name, const std::nullopt_t& some_nullopt);

template<typename T>
inline void set_bv(Value& bv, const T& val);
template<typename T>
inline void set_bv_memb(Value& bv, const std::string& name, const T& val);
//--------
} // namespace binser
} // namespace liborangepower

#endif		// liborangepower_binser_serialize_func_decls_hpp
