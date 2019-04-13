#ifndef liborangepower_with_defines_hpp
#define liborangepower_with_defines_hpp

#define with(obj, val) if (auto obj = val; true)
#define zwith(obj) if (obj; true)
#define awith(obj) if (auto obj; true)

#endif		// liborangepower_with_defines_hpp
