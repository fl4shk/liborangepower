#ifndef liborangepower_misc_defines_hpp
#define liborangepower_misc_defines_hpp


#define WIDTH2MP(some_width) (some_width - 1)
#define BPRANGE2MASK(bit_pos_hi, bit_pos_lo) \
	(((size_t)1 << ((size_t)bit_pos_hi - (size_t)bit_pos_lo + (size_t)1)) \
	- (size_t)1)
#define BPRANGE2SHIFTED_MASK(bit_pos_hi, bit_pos_lo) \
	((((size_t)1 << ((size_t)bit_pos_hi - (size_t)bit_pos_lo \
	+ (size_t)1)) - (size_t)1) << (size_t)bit_pos_lo)

#define _ALIGN4 aligned(4)
#define _ALIGN2 aligned(2)

#define ALIGNAS_REGULAR alignas(4)

#define ASM_COMMENT(stuff) \
	asm volatile("//@ ---" stuff " ---")


#endif		// liborangepower_misc_defines_hpp
