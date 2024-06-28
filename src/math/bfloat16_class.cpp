#include "bfloat16_class.hpp"
#include "../misc/misc_output_funcs.hpp"
#include <string.h>
#include <math.h>
#include <fenv.h>

namespace liborangepower {
namespace math {

BFloat16& BFloat16::operator = (float to_copy) {
	u32 temp;

	// This assumes that floats and u32's have the same endianness...
	memcpy(&temp, &to_copy, sizeof(to_copy));

	set_data(temp >> 16);

	//if (enc_exp() == 0)
	//{
	//	set_enc_mantissa(0);
	//}

	convert_to_normal_if_needed();


	//union
	//{
	//	u32 as_u32;
	//	float as_float;
	//} temp;

	//temp.as_float = to_copy;

	//set_data(temp.as_u32 >> 16);

	return *this;
}

BFloat16& BFloat16::operator = (i16 to_copy) {
	set_data(to_copy);

	//normalize();

	const size_t width = sizeof(data()) * 8;
	set_sign(get_bits_r(data(), (width - 1), (width - 1)));

	u16 absolute_data = abs(static_cast<i16>(data()));
	//i16 absolute_data = abs(data());
	u32 absolute_num_leading_zeros = count_leading_zeros(absolute_data);

	const u32 n_enc_exp = static_cast<u32>(bias)
		+ static_cast<u32>(width - 1) - absolute_num_leading_zeros;

	if (n_enc_exp < max_enc_exp) {
		set_enc_exp(n_enc_exp);
		absolute_data <<= absolute_num_leading_zeros;

		if ((absolute_data >> 8) == 0) {
			set_enc_exp(0);
		}

		set_enc_mantissa(absolute_data >> 8);
		convert_to_normal_if_needed();
	} else {
		//printout("saturating\n");
		saturate();
	}



	return *this;
}

BFloat16 BFloat16::operator + (const BFloat16& other) const {
	//fesetround(FE_TOWARDZERO);
	BFloat16 ret;

	BFloat16 a(*this), b(other);

	//a.convert_to_normal_if_needed();
	//b.convert_to_normal_if_needed();

	//printout("BFloat16::operator +:  ", strappcom2(static_cast<float>(a),
	//	static_cast<float>(b)), "\n");


	//fesetround(FE_TOWARDZERO);
	//const BFloat16 oracle(static_cast<float>(a) + static_cast<float>(b));

	const bool effective_add = (a.sign() == b.sign());


	const size_t d = abs(static_cast<i32>(a.enc_exp()
		- b.enc_exp()));

	u32 a_significand, b_significand, ret_significand;

	static constexpr size_t num_buffer_bits = 3;

	a_significand = a.frac() << num_buffer_bits;
	b_significand = b.frac() << num_buffer_bits;


	auto shift_significand = [&](
		decltype(a_significand)& some_significand
	) -> void {
		if (d >= (sizeof(some_significand) * 8)) {
			// Set the sticky bit
			some_significand = static_cast<bool>(some_significand);
		} else if (d > 0) {
			const bool sticky = get_bits_r(some_significand,
				d - 1 + (num_buffer_bits - 1), (num_buffer_bits - 1));
			some_significand >>= d;
			clear_and_set_bits(some_significand,
				static_cast<size_t>(sticky), 0, 0);
		}
	};


	if (a.enc_exp() < b.enc_exp()) {
		shift_significand(a_significand);
		ret.set_enc_exp(b.enc_exp());
	} else { // if (a.enc_exp() >= b.enc_exp())
		shift_significand(b_significand);
		ret.set_enc_exp(a.enc_exp());
	}

	if (effective_add) {
		ret_significand = a_significand + b_significand;

		if (
			get_bits_r(ret_significand, 8 + num_buffer_bits,
			8 + num_buffer_bits))
		{
			ret_significand >>= 1;
			ret.set_enc_exp(ret.enc_exp() + 1);
		}

		// If necessary, saturate to highest valid enc_mantissa and exponent
		if (ret.enc_exp() == max_enc_exp)
		{
			ret_significand = -1;
			ret.set_enc_exp(max_saturated_enc_exp);
		}

		ret_significand >>= num_buffer_bits;

		ret.set_sign(a.sign());

	}
	else // if (!effective_add)
	{
		if (a.sign())
		{
			ret_significand = b_significand - a_significand;
		}
		else // if (b.sign())
		{
			ret_significand = a_significand - b_significand;
		}

		// Convert to sign and magnitude
		if (get_bits_r(ret_significand, 15, 15))
		{
			ret_significand = -ret_significand;
			ret.set_sign(true);
		}




		// If the result is not zero.
		if (ret_significand)
		{
			//while (!get_bits_r(ret_significand,
			//	7 + num_buffer_bits, 7 + num_buffer_bits))
			//{
			//	if (ret.enc_exp() == 0)
			//	{
			//		break;
			//	}

			//	ret_significand <<= 1;
			//	//ret_significand &= 0x3ffff;

			//	ret.set_enc_exp(ret.enc_exp() - 1);
			//}

			//const size_t num_leading_zeros
			//	= count_leading_zeros(static_cast<u16>(ret_significand));
			const size_t num_leading_zeros
				= count_leading_zeros(ret_significand);

			const size_t real_num_leading_zeros 
				= num_leading_zeros
				- ((sizeof(ret_significand) * 8)
				- ((sizeof(i8) * 8) + num_buffer_bits));

			if ((static_cast<i32>(ret.enc_exp())
				- static_cast<i32>(real_num_leading_zeros)) <= 0)
			{
				ret.set_enc_exp(0);
			}
			else
			{
				ret.set_enc_exp(ret.enc_exp()
					- real_num_leading_zeros);
				ret_significand <<= real_num_leading_zeros;
			}

		}
		else
		{
			ret.set_enc_exp(0);
		}

		if (ret.enc_exp() == 0)
		{
			ret_significand = 0;
		}

		ret_significand >>= num_buffer_bits;
	}

	ret.set_enc_mantissa(ret_significand);

	return ret;
}

BFloat16 BFloat16::operator * (const BFloat16& other) const
{
	//fesetround(FE_TOWARDZERO);

	BFloat16 ret;

	const BFloat16 a(*this), b(other);

	//const float oracle_float = static_cast<float>(a)
	//	* static_cast<float>(b);

	//const BFloat16 oracle(oracle_float);

	ret.set_sign(a.sign() ^ b.sign());


	const u32 a_significand = a.frac(), b_significand = b.frac();

	//printout("Start:  ", std::hex, a_significand, " * ", b_significand,
	//	std::dec, "\n");

	u32 ret_significand = a_significand * b_significand;


	i32 ret_enc_exp = a.enc_exp() + b.enc_exp() - bias;

	// Special case result of 0:  we need to set the encoded exponent to
	// zero in that case
	if (ret_significand == 0)
	{
		ret_enc_exp = 0;
	}

	// Normalize if needed
	//printout("Okay!  ", std::hex, ret_enc_exp, " ",
	//	oracle.enc_exp(), " ", ret_significand, std::dec, "\n");

	if (get_bits_r(ret_significand, 15, 15))
	{
		ret_significand >>= 1;
		++ret_enc_exp;
	}

	//printout("Okay!  ", std::hex, ret_enc_exp, " ",
	//	oracle.enc_exp(), " ", ret_significand, std::dec, "\n");
	ret_significand >>= mul_significand_num_buffer_bits;
	//printout("Okay!  ", std::hex, ret_enc_exp, " ",
	//	oracle.enc_exp(), " ", ret_significand, std::dec, "\n");



	// If necessary, saturate to highest valid enc_mantissa and exponent
	if (ret_enc_exp >= static_cast<i32>(max_enc_exp))
	{
		//ret_significand = 0xffff;
		ret_significand = max_saturated_data_abs;
		ret.set_enc_exp(max_saturated_enc_exp);
	}
	// If necessary, set everything to zero.
	else if (ret_enc_exp <= 0)
	{
		ret_significand = 0;
		ret.set_enc_exp(0);
	}
	else
	{
		ret.set_enc_exp(ret_enc_exp);
	}
	//printout("Okay!  ", std::hex, ret_enc_exp, " ",
	//	oracle.enc_exp(), " ", ret_significand, std::dec, "\n");

	ret.set_enc_mantissa(ret_significand);

	return ret;
}




// Accurate, but slow (or, well, only kind of slow since the enc_mantissa
// is so small)
BFloat16 BFloat16::operator / (const BFloat16& other) const {

	BFloat16 ret;

	const BFloat16 a(*this), b(other);

	//fesetround(FE_TOWARDZERO);
	//const BFloat16 oracle(static_cast<float>(a) / static_cast<float>(b));


	ret.set_sign(a.sign() ^ b.sign());

	static constexpr size_t num_buffer_bits = sizeof(u8) * 8;
	//static constexpr size_t modded_num_buffer_bits = num_buffer_bits + 1;

	const u32 a_significand = a.frac() << num_buffer_bits,
		b_significand = b.frac();
	//const u32 a_significand = a.frac(), b_significand = b.frac();

	// Divide 16-bit unsigned integer by 8-bit unsigned integer

	u32 ret_significand;
	
	// Special case of division by zero:  just set the whole thing to zero.
	if (b_significand == 0) {
		ret_significand = 0;
	} else {
		ret_significand = a_significand / b_significand;
		//ret_significand = div_u16_by_u8_low_10_bits(a_significand,
		//	b_significand);
		//ret_significand = div_u16_by_u8(a_significand, b_significand);
		//ret_significand = div_for_bfloat16(a_significand, b_significand);
	}

	i32 ret_enc_exp = a.enc_exp() - b.enc_exp()
		+ bias;

	// Special case 0 / whatever:  we need to set the encoded exponent to
	// zero in that case
	if (ret_significand == 0) {
		ret_enc_exp = 0;
	} else { // if (ret_significand)
		// Normalization here is really simple.
		// I don't fully understand how it works.  I just know that it
		// does.
		if (get_bits_r(ret_significand, 8, 8)) {
			ret_significand >>= 1;
		} else {
			--ret_enc_exp;
		}
	}

	if (ret_enc_exp >= static_cast<i32>(max_enc_exp)) {
		ret_significand = max_saturated_data_abs;
		ret.set_enc_exp(max_saturated_enc_exp);
	} else if (ret_enc_exp <= 0) {
	// If necessary, set everything to zero
		ret_significand = 0;
		ret.set_enc_exp(0);
	} else {
		ret.set_enc_exp(ret_enc_exp);
	}

	ret.set_enc_mantissa(ret_significand);

	return ret;
}


bool BFloat16::operator < (const BFloat16& other) const {
	const size_t the_signs = (static_cast<size_t>(sign()) << 1)
		| (static_cast<size_t>(other.sign()));

	switch (the_signs) {
		case 0b00:
			return ((data() & 0x7fff) < (other.data() & 0x7fff));
			break;

		case 0b01:
			// (((*this) >= 0) && (other <= 0))
			return false;
			break;

		case 0b10:
			// The only time opposite signs allows "<" to return false
			// is when (((*this) == 0.0f) && (other == -0.0f))

			//if (((data() & 0x7f8f) == 0)
			//	&& ((other.data() & 0x7fff) == 0))
			return (!((frac() == 0) && (other.frac() == 0)));
			break;

		case 0b11:
			return ((other.data() & 0x7fff) < (data() & 0x7fff));
			break;

		default:
			// Eek!
			return false;
			break;
	}
}

BFloat16::operator float() const {
	//union
	//{
	//	u32 as_u32;
	//	float as_float;
	//} ret_union;
	//ret_union.as_u32 = static_cast<u32>(data())
	//	<< static_cast<u32>(16);

	//return ret_union.as_float;

	u32 temp = 0;
	float ret;

	static constexpr size_t add_amount_for_bit_pos = 16;

	set_bits_r(temp, static_cast<u32>(sign()), 
		(bit_pos_sign_h + add_amount_for_bit_pos), 
		(bit_pos_sign_l + add_amount_for_bit_pos));

	// The only subnormal is zero, which affects how we convert to a 32-bit
	// float.
	//if (frac() != 0)
	//if (is_normal())

	//if (enc_exp() != 0)
	if (is_normal()) {
		set_bits_r(temp, enc_exp(), 
			(bit_pos_enc_exp_h + add_amount_for_bit_pos),
			(bit_pos_enc_exp_l + add_amount_for_bit_pos));
		set_bits_r(temp, enc_mantissa(), 
			(bit_pos_enc_mantissa_h + add_amount_for_bit_pos),
			(bit_pos_enc_mantissa_l + add_amount_for_bit_pos));
	}

	memcpy(&ret, &temp, sizeof(temp));

	//printout("operator float():  ", ret, "\n");

	return ret;
}

BFloat16::operator i16() const {
	u32 ret = 0;
	
	ret = frac();

	const i32 curr_exp = exponent();
	const i32 abs_curr_exp = abs(curr_exp);

	static constexpr i32 max_shift_amount = (sizeof(i16) * 8) - 1;

	if (curr_exp < 0) {
		if (abs_curr_exp <= max_shift_amount) {
			ret >>= abs_curr_exp;
		} else {
			ret = 0;
		}
	} else {
		if (abs_curr_exp <= max_shift_amount) {
			ret <<= abs_curr_exp;
		} else {
			ret = 0;
		}
	}

	if (sign()) {
		ret = -ret;
	}

	return ret;
}


} // namespace math
} // namespace liborangepower

std::ostream& operator << (
	std::ostream& os, const liborangepower::math::BFloat16& to_print
) {
	return liborangepower::misc_output::osprintout(os, to_print.sign(), ", ",
		//std::hex,
		(int16_t)(uint8_t)to_print.exponent(), ", ",
		(int16_t)(uint8_t)to_print.enc_exp(), ", ",
		//std::hex,
		"\t\t", to_print.frac(), ", ",
		//"\t\t", to_print.frac()
		to_print.enc_mantissa()
		//std::dec,
		//"\n"
		);
}
