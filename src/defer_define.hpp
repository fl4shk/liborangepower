#ifndef liborangepower_defer_define_hpp
#define liborangepower_defer_define_hpp

#include <memory>
#include <functional>


#define defer(name, ...) \
	std::shared_ptr<void> defer_ ## name (nullptr, \
		std::bind([&]() -> void \
		{ \
			__VA_ARGS__ \
		}))


#endif		// liborangepower_defer_define_hpp
