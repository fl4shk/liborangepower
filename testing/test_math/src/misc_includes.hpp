#ifndef src_misc_includes_hpp
#define src_misc_includes_hpp

// src/misc_includes.hpp

#include "liborangepower_src/misc/misc_includes.hpp"
#include "liborangepower_src/misc/misc_output_funcs.hpp"
#include "liborangepower_src/misc/misc_types.hpp"
#include "liborangepower_src/misc/misc_utility_funcs.hpp"
#include "liborangepower_src/misc/misc_bitwise_funcs.hpp"
#include "liborangepower_src/misc/misc_defines.hpp"
#include "liborangepower_src/gen_class_innards_defines.hpp"
#include "liborangepower_src/strings/string_conversion_stuff.hpp"
#include "liborangepower_src/math/vec2_classes.hpp"
#include "liborangepower_src/math/vec3_classes.hpp"
#include "liborangepower_src/math/cx_fixed_pt_class.hpp"
#include "liborangepower_src/math/shape_2d_classes.hpp"
#include "liborangepower_src/containers/prev_curr_pair_classes.hpp"
#include "liborangepower_src/containers/misc_templates.hpp"
#include "liborangepower_src/json_stuff/json_stuff.hpp"
#include "liborangepower_src/binser/serialize_funcs.hpp"
#include "liborangepower_src/binser_plus_json_stuff/bv_to_jv_casting_func.hpp"
#include "liborangepower_src/metaprog_defines.hpp"
#include "liborangepower_src/concepts/math_concepts.hpp"

using namespace liborangepower::misc_output;
using namespace liborangepower::integer_types;
using namespace liborangepower::misc_util;
using namespace liborangepower::bitwise;
using namespace liborangepower::strings;
namespace json = liborangepower::json;
namespace binser = liborangepower::binser;
using namespace liborangepower::containers;
using namespace liborangepower::math;
namespace concepts = liborangepower::concepts; 

#endif		// src_misc_includes_hpp
