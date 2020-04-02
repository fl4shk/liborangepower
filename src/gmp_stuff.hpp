#ifndef liborangepower_gmp_stuff_hpp
#define liborangepower_gmp_stuff_hpp

#include "misc_includes.hpp"

// GMP headers
#include <gmpxx.h>

namespace liborangepower
{

namespace bignum
{

typedef mpz_class BigNum;

bool str_is_base_10_sint_bignum(const std::string& str, BigNum& ret);

template<typename Type>
inline Type convert_bignum_to(const BigNum& to_conv)
{
	Type ret;
	std::stringstream sstm;
	sstm << in_bignum;
	sstm >> ret;
	return ret;
}

inline std::string convert_bignum_to_str(const BigNum& to_conv)
{
	return convert_bignum_to<std::string>(to_conv);
}


} // namespace bignum

} // namespace liborangepower

#endif		// liborangepower_gmp_stuff_hpp
