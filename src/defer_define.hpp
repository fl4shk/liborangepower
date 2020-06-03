#ifndef liborangepower_defer_define_hpp
#define liborangepower_defer_define_hpp

#include <memory>
#include <functional>

#include "cpp_magic.hpp"


#define _INNER_DEFER(item) \
	item

#define defer(name, ...) \
	std::shared_ptr<void> defer_ ## name (nullptr, \
		std::bind([&]() -> void \
		{ \
			EVAL(MAP(_INNER_DEFER, SEMICOLON, __VA_ARGS__)) \
		}))


#endif		// liborangepower_defer_define_hpp
