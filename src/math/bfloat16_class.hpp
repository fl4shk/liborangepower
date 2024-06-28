#ifndef src_bfloat16_class_hpp
#define src_bfloat16_class_hpp

// src/bfloat16_class.hpp

//#include "misc_includes.hpp"
#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../misc/misc_bitwise_funcs.hpp"


namespace liborangepower {
namespace math {
using namespace integer_types;
using namespace bitwise;
//--------
template<size_t high_size, size_t low_size>
class HighAndLow {
public:		// variables
	size_t high: high_size;
	size_t low: low_size;
};

class BFloat16 {
public:		// constants
	static constexpr size_t num_bfloat16s = static_cast<size_t>(1)
		<< static_cast<size_t>(16);

	static constexpr i32 bias = 127;
	static constexpr i32 amount_to_add_for_modded_bias = 7;
	static constexpr i32 modded_bias = bias
		+ amount_to_add_for_modded_bias;
	static constexpr size_t max_enc_exp = 0xff;
	static constexpr size_t max_saturated_enc_exp = max_enc_exp - 1;

	static constexpr size_t max_saturated_data_abs = 0x7f7f;

	static constexpr size_t bit_pos_sign_h = 15, bit_pos_sign_l = 15;
	static constexpr size_t bit_pos_enc_exp_h = 14, bit_pos_enc_exp_l = 7;
	static constexpr size_t bit_pos_enc_mantissa_h = 6,
		bit_pos_enc_mantissa_l = 0;

	static constexpr size_t mul_significand_num_buffer_bits = 7;

	static constexpr size_t num_starting_recips = 256;
	//static const u8 starting_recips_table[num_starting_recips];

	static constexpr size_t width_enc_mantissa = 7;
public:		// classes
private:		// variables
	u16 _data = 0;
public:		// functions
	inline BFloat16() {
	}

	inline BFloat16(u32 s_sign, u32 s_enc_exp, u32 s_enc_mantissa) {
		set_sign(s_sign);
		set_enc_exp(s_enc_exp);
		set_enc_mantissa(s_enc_mantissa);
		convert_to_normal_if_needed();
	}

	inline BFloat16(float to_copy) {
		*this = to_copy;
	}

	inline BFloat16(i16 to_copy) {
		*this = to_copy;
	}

	inline BFloat16(u16 s_data) {
		set_data(s_data);
		convert_to_normal_if_needed();
	}
	inline BFloat16(u32 s_data) {
		set_data(s_data);
		convert_to_normal_if_needed();
	}
	inline BFloat16(size_t s_data) {
		set_data(s_data);
		convert_to_normal_if_needed();
	}

	inline BFloat16(const BFloat16& to_copy) = default;

	inline BFloat16& operator = (const BFloat16& to_copy) = default;

	BFloat16& operator = (float to_copy);

	BFloat16& operator = (i16 to_copy);

	inline BFloat16& operator += (const BFloat16& other) {
		*this = (*this) + other;
		return *this;
	}
	inline BFloat16& operator -= (const BFloat16& other) {
		*this = (*this) - other;
		return *this;
	}
	inline BFloat16& operator *= (const BFloat16& other) {
		*this = (*this) * other;
		return *this;
	}
	inline BFloat16& operator /= (const BFloat16& other) {
		*this = *this / other;
		return *this;
	}

	BFloat16 operator + (const BFloat16& other) const;
	inline BFloat16 operator - (const BFloat16& other) const {
		BFloat16 temp(other);
		temp.set_sign(!other.sign());
		return ((*this) + temp);
	}
	BFloat16 operator * (const BFloat16& other) const;
	BFloat16 operator / (const BFloat16& other) const;

	static BFloat16 fma(
		const BFloat16& left, const BFloat16& mul_a, const BFloat16& mul_b
	);
	inline bool operator == (const BFloat16& other) const {
		return ((data() == other.data()) 
			|| (is_either_zero() && other.is_either_zero()));
	}
	inline bool operator != (const BFloat16& other) const {
		//return (data() != other.data());
		return (!((*this) == other));
	}
	bool operator < (const BFloat16& other) const;
	inline bool operator > (const BFloat16& other) const {
		return (((*this) != other) && (other < (*this)));
	}
	inline bool operator <= (const BFloat16& other) const {
		return (((*this) < other) || ((*this) == other));
	}
	inline bool operator >= (const BFloat16& other) const {
		return (((*this) > other) || ((*this) == other));
	}

	template<typename CreateFromType>
	static inline BFloat16 create_from_int(CreateFromType to_cast) {
		static_assert(std::is_integral<CreateFromType>::value,
			"BFloat16::create_from_int() requires an integral type as the "
			"template parameter.");

		//// For some reason, this just doesn't work.  Don't use it!
		//static constexpr bool create_from_type_is_signed
		//	= ((static_cast<CreateFromType>(0)
		//	- static_cast<CreateFromType>(1))
		//	< static_cast<CreateFromType>(0));

		// This, on the other hand, appears to work flawlessly.
		static constexpr bool create_from_type_is_signed
			= ((static_cast<CreateFromType>(-1))
			< (static_cast<CreateFromType>(0)));


		static constexpr size_t width = sizeof(CreateFromType) * 8;

		BFloat16 ret;

		CreateFromType absolute_data;
		if (!create_from_type_is_signed) {
			absolute_data = to_cast;
			ret.set_sign(false);
		} else { // if (create_from_type_is_signed)
			//absolute_data = abs(static_cast<i64>(to_cast));
			absolute_data = llabs(to_cast);
			ret.set_sign(
				get_bits_r(static_cast<i64>(to_cast),
				(width - 1), (width - 1))
			);
		}


		const size_t absolute_num_leading_zeros
			= count_leading_zeros(absolute_data);

		const size_t n_enc_exp = static_cast<size_t>(bias)
			+ (width - static_cast<size_t>(1))
			- absolute_num_leading_zeros;

		//if (n_enc_exp < max_enc_exp)
		{
			ret.set_enc_exp(n_enc_exp);
			absolute_data <<= absolute_num_leading_zeros;
			absolute_data = get_bits_with_range(absolute_data, width - 1, 
				width - 8);

			if (absolute_data == 0) {
				ret.set_enc_exp(0);
			}

			ret.set_enc_mantissa(absolute_data);
		}
		//else {
		//	ret.saturate();
		//}

		return ret;
	}

	template<typename CastToType>
	inline CastToType cast_to_int() const {
	//inline CastToType cast_to_int(std::ostream& os) const
		static_assert(std::is_integral<CastToType>::value,
			"BFloat16::cast_to_int() requires an integral type as the "
			"template parameter.");
		//static constexpr bool cast_to_type_is_signed
		//	= ((static_cast<CastToType>(-1))
		//	< (static_cast<CastToType>(0)));
		static constexpr bool cast_to_type_is_signed
			= std::is_signed<CastToType>::value;


		//u64 ret = 0;
		typedef typename std::make_unsigned<CastToType>::type RetType;

		RetType ret = 0;

		ret = frac();


		const i32 curr_exp = exponent();
		//const s8 curr_exp = static_cast<s8>(enc_exp())
		//	- static_cast<s8>(modded_bias);
		const i32 abs_curr_exp = abs(curr_exp);


		static constexpr i32 max_shift_amount 
			= width_of_type<CastToType>() - 1;

		//const auto oracle = static_cast<RetType>(static_cast<float>
		//	(*this));

		if (curr_exp < 0) {
			//osprintout(os, "outer if:  curr_exp, ",
			//	"width_of_type(ret), enc_exp():  ",
			//	curr_exp, ", ", 
			//	static_cast<i32>(width_of_type(ret)), ", ",
			//	enc_exp(), "\n");

			if (abs_curr_exp <= max_shift_amount) {
				ret >>= abs_curr_exp;

				//osprintout(os, "before:  ", std::hex, ret, std::dec, "\n");

				if (!cast_to_type_is_signed && sign()) {
					ret = -ret;
				}
				//osprintout(os, "after:  ", std::hex, ret, std::dec, "\n");
			} else {
				ret = 0;
			}
			//ret = oracle;
		} else { // if (curr_exp >= 0)
			//ret = static_cast<CastToType>(static_cast<float>(*this));
			auto set_to_max_signed = [&]() -> void {
				ret = 0;
				set_bits_with_range(ret, 1,
					WIDTH2MP(width_of_type(ret)),
					WIDTH2MP(width_of_type(ret)));
			};

			//osprintout(os, "outer else:  curr_exp, ",
			//	"width_of_type(ret), enc_exp():  ",
			//	curr_exp, ", ", 
			//	static_cast<i32>(width_of_type(ret)), ", ",
			//	enc_exp(), "\n");
			if (abs_curr_exp <= max_shift_amount) {
				//osprintout(os, "outer else:  outer if:  ",
				//	std::hex, ret, std::dec, ", ", abs_curr_exp,
				//	"\n");

				//const bool sticky = get_bits_with_range(ret,
				//	WIDTH2MP(width_of_type(ret)),
				//	(WIDTH2MP(width_of_type(ret)) 
				//	- abs_curr_exp))
				//	|| ((abs_curr_exp 
				//	== WIDTH2MP(width_of_type(ret)))
				//	&& ret);
				const bool sticky = get_bits_with_range(ret,
					WIDTH2MP(width_of_type(ret)),
					(WIDTH2MP(width_of_type(ret))
					- abs_curr_exp));


				//if constexpr (sizeof(ret) <= sizeof(data()))
				{
					ret <<= abs_curr_exp;
				}

				//if (sticky && (!cast_to_type_is_signed)) {
				//	ret = 0;
				//}

				if (!cast_to_type_is_signed && sign()) {
					ret = -ret;
				}


				//if constexpr (sizeof(ret) > sizeof(data()))
				if (sizeof(ret) > sizeof(data())) {
					if (sticky) {
						if (!cast_to_type_is_signed) {
							//ret = -1;
							//ret = 0;

							if (
								std::is_same<u64, decltype(ret)>::value
							) {
								if (sign())
								{
									ret = 0;
									if (curr_exp >= 56)
									{
										set_to_max_signed();
									}
								}

								else if (curr_exp >= 57)
								{
									ret = 0;
								}
							}

						} else { // if (cast_to_type_is_signed)
							set_to_max_signed();
						}
					}

				}
				//ret = oracle;
				//ret = oracle;
			} else { // if (abs_curr_exp > max_shift_amount)
				//osprintout(os, "outer else:  outer else:  ",
				//	std::hex, ret, std::dec, ", ", abs_curr_exp,
				//	"\n");
				ret = 0;

				if constexpr (sizeof(ret) > sizeof(data())) {
					//osprintout(os, "outer else:  outer else:  if\n");
					if (
						(curr_exp >= static_cast<i32>(width_of_type(ret)))
						&& (enc_exp() != max_enc_exp)
					) {
						if (!cast_to_type_is_signed) {
							//ret = -1;
							//ret = 0;

							// For some reason, u64 needs special behavior
							// here.
							if (
								sign() 
								&& std::is_same<u64, decltype(ret)>::value
							) {
								set_to_max_signed();
							}
						} else { // if (cast_to_type_is_signed)
							set_to_max_signed();
						}
					}
				}
				//osprintout(os, "other case:  ",
				//	std::hex, ret, std::dec,
				//	"\n");

			}
		}


		//osprintout(os, "ret:  ", std::hex, ret, std::dec, "\n");
		if (cast_to_type_is_signed && sign()) {
		//if (sign())
			//printout("eek!\n");
			//osprintout(os, "eek!\n");
			ret = -ret;
		}
		//osprintout(os, "final ret:  ", std::hex, ret, std::dec, "\n");

		return ret;
	}
	

	//inline operator float() const
	//{
	//	union
	//	{
	//		u32 as_u32;
	//		float as_float;
	//	} ret_union;
	//	ret_union.as_u32 = static_cast<u32>(data())
	//		<< static_cast<u32>(16);

	//	return ret_union.as_float;
	//}
	operator float() const;
	operator i16() const;

	inline i16 oracle_to_i16() const {
		const float ret_float = static_cast<float>(*this);

		return static_cast<i16>(ret_float);
	}


	inline bool sign() const {
		return get_bits_r(_data, bit_pos_sign_h, bit_pos_sign_l);
	}
	inline bool set_sign(bool n_sign) {
		clear_and_set_bits_r(_data, n_sign, bit_pos_sign_h, bit_pos_sign_l);
		return sign();
	}
	inline u32 enc_exp() const {
		u16 ret = data();
		//ret >>= 7;
		ret >>= bit_pos_enc_exp_l;
		ret &= 0xff;

		return static_cast<u32>(ret);
	}
	inline u32 set_enc_exp(u32 n_enc_exp) {
		clear_and_set_bits(_data, n_enc_exp,
			bit_pos_enc_exp_h, bit_pos_enc_exp_l);
		return enc_exp();
	}
	inline i32 exponent() const {
		i32 ret = static_cast<i32>(enc_exp());
		ret -= modded_bias;
		//ret = static_cast<s8>(ret);

		return ret;
	}
	//inline i32 set_exponent(i32 n_exponent) {
	//	set_enc_exp(n_exponent + modded_bias);
	//	return exponent();
	//}
	inline u32 enc_mantissa() const {
		return get_bits_r(
			_data, bit_pos_enc_mantissa_h, bit_pos_enc_mantissa_l
		);
	}
	inline u32 set_enc_mantissa(u32 n_enc_mantissa) {
		clear_and_set_bits_r(
			_data, n_enc_mantissa, bit_pos_enc_mantissa_h,
			bit_pos_enc_mantissa_l
		);
		return enc_mantissa();
	}

	//inline BFloat16 get_as_normal() const {
	//	if (is_normal())
	//	{
	//		return *this;
	//	}

	//	return BFloat16(static_cast<u16>(0));
	//}

	inline bool is_either_zero() const {
		return ((data() & 0x7fff) == 0);
	}

	inline bool is_normal() const {
		//return (!((enc_exp() == 0) || ((enc_exp() == 255)
		//	&& (enc_mantissa() != 0))));
		return ((enc_exp() != 0) && (enc_exp() != 255));
	}



	inline u32 frac() const {
		// The only subnormal is zero.
		if (!is_normal()) {
			return 0;
		} else {// if (is_normal())
			return static_cast<u32>
				(static_cast<u8>((data() & 0x7f) | (data() ? 0x80 : 0)));
		}
	}


	//gen_getter_by_val(data)
	inline decltype(_data) data() const {
		return _data;
	}

protected:		// functions
	inline void convert_to_normal_if_needed() {
		if (!is_normal()) {
			set_enc_exp(0);
			set_enc_mantissa(0);
		}
	}

	inline void saturate() {
		// Saturate if needed since we don't have infinity or negative
		// infinity
		const bool n_sign = sign();

		set_data(max_saturated_data_abs);
		set_sign(n_sign);
	}
	//GEN_SETTER_BY_VAL(data)
	inline void set_data(decltype(_data) n_data) {
		_data = n_data;
	}
};
} // namespace math
} // namespace liborangepower


std::ostream& operator << (
	std::ostream& os, const liborangepower::math::BFloat16& to_print
);

#endif		// src_bfloat16_class_hpp
