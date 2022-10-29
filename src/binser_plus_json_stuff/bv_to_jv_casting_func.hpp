#ifndef liborangepower_binser_plus_json_stuff_bv_to_jv_casting_func_hpp
#define liborangepower_binser_plus_json_stuff_bv_to_jv_casting_func_hpp

#include "../binser/value_class.hpp"

// jsoncpp headers
#include <json/value.h>

namespace liborangepower {
namespace binser {
//--------
Json::Value bv_to_jv(const binser::Value& bv);
//Value jv_to_bv(const Json::Value& jv);
//--------
} // namespace binser
} // namespace liborangepower

#endif
	// liborangepower_binser_plus_json_stuff_bv_to_jv_casting_func_hpp
