#ifndef liborangepower_misc_defines_hpp
#define liborangepower_misc_defines_hpp


#define width_to_msb_pos(some_width) (some_width - 1)
#define bprange_to_mask(bit_pos_hi, bit_pos_lo) \
	(((size_t)1 << ((size_t)bit_pos_hi - (size_t)bit_pos_lo + (size_t)1)) \
	- (size_t)1)
#define bprange_to_shifted_mask(bit_pos_hi, bit_pos_lo) \
	((((size_t)1 << ((size_t)bit_pos_hi - (size_t)bit_pos_lo \
	+ (size_t)1)) - (size_t)1) << (size_t)bit_pos_lo)

#define _align4 aligned(4)
#define _align2 aligned(2)

#define alignas_regular alignas(4)

#define asm_comment(stuff) \
	asm volatile("//@ ---" stuff " ---")


#endif		// liborangepower_misc_defines_hpp
