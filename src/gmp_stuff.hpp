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

bool str_is_integer_bignum(const std::string& str, BigNum& ret);

inline std::string convert_bignum_to_str(const BigNum& in_bignum)
{
	std::string ret;
	std::stringstream sstm;
	sstm << in_bignum;
	sstm >> ret;
	return ret;
}

} // namespace bignum

} // namespace liborangepower

#endif		// liborangepower_gmp_stuff_hpp
