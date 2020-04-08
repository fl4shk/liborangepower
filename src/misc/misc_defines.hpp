#ifndef liborangepower_misc_defines_hpp
#define liborangepower_misc_defines_hpp


#define WIDTH2MP(some_width) ((some_width) - 1)
#define BPRANGE2MASK(bit_pos_hi, bit_pos_lo) \
	(((size_t)1 << (((size_t)bit_pos_hi) - (size_t)(bit_pos_lo) \
	+ (size_t)1)) - (size_t)1)
#define BPRANGE2SHIFTED_MASK(bit_pos_hi, bit_pos_lo) \
	((((size_t)1 << ((size_t)(bit_pos_hi) - (size_t)(bit_pos_lo) \
	+ (size_t)1)) - (size_t)1) << (size_t)(bit_pos_lo))


#define _ALIGN4 aligned(4)
#define _ALIGN2 aligned(2)

#define ALIGNAS_REGULAR alignas(4)

#define ASM_COMMENT(stuff) \
	asm volatile("//@ --- " stuff " ---")


#define INNER_TOKENPASTE1(x) x
#define TOKENPASTE1(x) INNER_TOKENPASTE1(x)

#define INNER_TOKENPASTE2(x, y) x ## y
#define TOKENPASTE2(x, y) INNER_TOKENPASTE2(x, y)

#define TOKENPASTE3(x, y, z) TOKENPASTE2(x, TOKENPASTE2(y, z))
#define TOKENPASTE4(x, y, z, w) TOKENPASTE3(x, y, TOKENPASTE2(z, w))


#endif		// liborangepower_misc_defines_hpp
