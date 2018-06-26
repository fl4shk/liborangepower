#ifndef liborangepower_count_leading_zeros_hpp
#define liborangepower_count_leading_zeros_hpp

// src/count_leading_zeros.hpp

//#include "misc_includes.hpp"
#include "misc_bitwise_funcs.hpp"

namespace liborangepower
{

namespace bitwise
{

using liborangepower::integer_types::u8;
using liborangepower::integer_types::s8;

using liborangepower::integer_types::u16;
using liborangepower::integer_types::s16;

using liborangepower::integer_types::u32;
using liborangepower::integer_types::s32;

using liborangepower::integer_types::u64;
using liborangepower::integer_types::s64;


template<typename Type>
size_t count_leading_zeros(Type x)
{
	size_t ret = 0;

	//u64 temp32 = 0, temp16 = 0, temp8 = 0, temp4 = 0, temp2 = 0;
	u64 s = x;

	if (s == 0)
	{
		ret = sizeof(Type) * 8;
	}

	else
	{
		switch (sizeof(Type))
		{
			case 8:
				s = get_bits_with_range(s, 63, 32)
					? get_bits_with_range(s, 63, 32)
					: ((static_cast<u64>(1) << static_cast<u64>(32)) 
					| get_bits_with_range(s, 31, 0));
				set_bits_with_range(ret, get_bits_with_range(s, 32, 32), 5,
					5);

			case 4:
				s = get_bits_with_range(s, 31, 16)
					? get_bits_with_range(s, 31, 16)
					: ((1 << 16) | get_bits_with_range(s, 15, 0));
				set_bits_with_range(ret, get_bits_with_range(s, 16, 16), 4, 
					4);

			case 2:
				s = get_bits_with_range(s, 15, 8)
					? get_bits_with_range(s, 15, 8)
					: ((1 << 8) | get_bits_with_range(s, 7, 0));
				set_bits_with_range(ret, get_bits_with_range(s, 8, 8), 3,
					3);

			case 1:
				s = get_bits_with_range(s, 7, 4)
					? get_bits_with_range(s, 7, 4)
					: ((1 << 4) | get_bits_with_range(s, 3, 0));
				set_bits_with_range(ret, get_bits_with_range(s, 4, 4), 2,
					2);

				s = get_bits_with_range(s, 3, 2)
					? get_bits_with_range(s, 3, 2)
					: ((1 << 2) | get_bits_with_range(s, 1, 0));
				set_bits_with_range(ret, get_bits_with_range(s, 2, 2), 1,
					1);

				set_bits_with_range(ret, !get_bits_with_range(s, 1, 1), 0,
					0);
				break;

			//default:
			//	for (s64 i=((1 << sizeof(Type)) - 1); i>=0; --i)
			//	{
			//		if (!get_bits_with_range(s, i, i))
			//		{
			//			++ret;
			//		}
			//		else
			//		{
			//			break;
			//		}
			//	}
			//	break;
		}
	}

	return ret;
}

} // namespace bitwise

} // namespace liborangepower


#endif		// liborangepower_count_leading_zeros_hpp
