#ifndef liborangepower_binser_serialize_defines_hpp
#define liborangepower_binser_serialize_defines_hpp

// These are for use with X macros that call a macro on at least some
// members of a class to serialize or deserialize
#define BINSER_MEMB_SERIALIZE(name, ...) \
	liborangepower::binser::set_bv_memb(ret, #name, name);
#define BINSER_MEMB_DESERIALIZE(name, func_map, ...) \
	liborangepower::binser::get_bv_memb(name, bv, #name, func_map);
#define BINSER_MEMB_FROM_BV_DESERIALIZE(name, func_map, ...) \
	liborangepower::binser::get_bv_memb(ret.name, bv, #name, func_map);

#define BINSER_MEMB_DESERIALIZE_EX_CS(name, func_map, temp_type, temp_name, cs_arg, cs_is_max_arg, min_size_arg) \
	do { \
		if (temp_type temp_name; true) { \
			temp_name.checked_size = cs_arg; \
			temp_name.cs_is_max = cs_is_max_arg; \
			temp_name.min_size = min_size_arg; \
			liborangepower::binser::get_bv_memb( \
				temp_name, bv, #name, std::nullopt \
			); \
			name = std::move(temp_name.data); \
		} \
	} while (0)

#define BINSER_MEMB_FROM_BV_DESERIALIZE_EX_CS(name, func_map, temp_type, temp_name, cs_arg, cs_is_max_arg, min_size_arg) \
	do { \
		if (temp_type temp_name; true) { \
			temp_name.checked_size = cs_arg; \
			temp_name.cs_is_max = cs_is_max_arg; \
			temp_name.min_size = min_size_arg; \
			liborangepower::binser::get_bv_memb( \
				temp_name, bv, #name, std::nullopt \
			); \
			ret.name = std::move(temp_name.data); \
		} \
	} while (0)

#define BINSER_MEMB_DESERIALIZE_EX_MM(name, func_map, temp_type, temp_name, max_arg, min_arg) \
	do { \
		if (temp_type temp_name; true) { \
			temp_name.max = max_arg; \
			temp_name.min = min_arg; \
			liborangepower::binser::get_bv_memb( \
				temp_name, bv, #name, func_map \
			); \
			name = std::move(temp_name.data); \
		} \
	} while (0)
#define BINSER_MEMB_FROM_BV_DESERIALIZE_EX_MM(name, func_map, temp_type, temp_name, max_arg, min_arg) \
	do { \
		if (temp_type temp_name; true) { \
			temp_name.max = max_arg; \
			temp_name.min = min_arg; \
			liborangepower::binser::get_bv_memb( \
				temp_name, bv, #name, func_map \
			); \
			ret.name = std::move(temp_name.data); \
		} \
	} while (0)

#endif		// liborangepower_binser_serialize_defines_hpp
