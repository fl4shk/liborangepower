#ifndef liborangepower_with_defines_hpp
#define liborangepower_with_defines_hpp

#define with(obj) if (auto obj; true)
#define zwith(obj) if (obj; true)
#define vwith(obj, val) with(obj = val)

#endif		// liborangepower_with_defines_hpp
