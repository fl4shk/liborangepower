#ifndef src_float32_class_hpp
#define src_float32_class_hpp

// src/math/float32_class.hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../misc/misc_bitwise_funcs.hpp"
namespace liborangepower {
namespace math {
//--------
using namespace integer_types;
using namespace bitwise;
//--------
class Float32 {
public:		// constants
	static constexpr size_t NUM_FLOAT32S = 1ull << 32ull;
	static constexpr i32
		BIAS = 127,
		AMOUNT_TO_ADD_FOR_MODDED_BIAS = 7,
		MODDED_BIAS = BIAS + AMOUNT_TO_ADD_FOR_MODDED_BIAS;
	static constexpr size_t
		MAX_ENC_EXP = 0xff,
		MAX_SATURATED_ENC_EXP = MAX_ENC_EXP - 1,
		SIGN_BITSIZE = 1ull,
		EXP_BITSIZE = 8ull,
		FRAC_BITSIZE = 24ull;

public:		// types
	class Data final {
	public:		// variables
		bool sign: SIGN_BITSIZE;
		i32 exp: EXP_BITSIZE;
		i32 frac: FRAC_BITSIZE;
	};
public:		// variables
	Data data;
public:		// functions
	void set_data(Data n_data) {
		data = n_data;
	}
	void set_data_raw(u32 n_data_raw) {
		memcpy(&data, &n_data_raw, sizeof(Data));
	}
};
//--------
} // namespace math
} // namespace liborangepower


#endif		// src_float32_class_hpp
