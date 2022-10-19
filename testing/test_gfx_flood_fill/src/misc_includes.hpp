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
#include "liborangepower_src/strings/sconcat_etc.hpp"
#include "liborangepower_src/containers/defer_call_stuff.hpp"
#include "liborangepower_src/concepts/misc_concepts.hpp"
#include "liborangepower_src/concepts/math_concepts.hpp"
#include "liborangepower_src/concepts/std_container_concepts.hpp"
#include "liborangepower_src/concepts/std_stream_concepts.hpp"
#include "liborangepower_src/concepts/is_specialization_concepts.hpp"
#include "liborangepower_src/time/time_stuff.hpp"
#include "liborangepower_src/gfx/plot_stuff.hpp"
#include "liborangepower_src/math/shape_2d_classes.hpp"

using namespace liborangepower::misc_output;
using namespace liborangepower::integer_types;
using namespace liborangepower::misc_util;
using namespace liborangepower::bitwise;
using namespace liborangepower::strings;
using namespace liborangepower::containers;
namespace concepts = liborangepower::concepts;
using namespace liborangepower::time;
using namespace liborangepower::gfx;
namespace math = liborangepower::math;

#include <pcg_random.hpp>

#endif		// src_misc_includes_hpp
