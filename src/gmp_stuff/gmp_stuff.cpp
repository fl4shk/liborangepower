#include "gmp_stuff.hpp"

namespace liborangepower
{

namespace bignum
{

bool str_is_base_10_sint_bignum(const std::string& str, BigNum& ret)
{
	size_t i = 0;

	bool negative = false;

	if (str.front() == '-')
	{
		negative = true;
		++i;
	}

	if (isdigit(str.at(i)))
	{
		ret = str.at(i) - '0';
		++i;

		for (; i<str.size(); ++i)
		{
			if (isdigit(str.at(i)))
			{
				ret = (ret * 10) + (str.at(i) - '0');
			}
			else // if (!isdigit(str.at(i)))
			{
				return false;
			}
			
		}

		if (negative)
		{
			ret *= -1;
		}

		return true;
	}

	return false;
}

} // namespace bignum

} // namespace liborangepower
