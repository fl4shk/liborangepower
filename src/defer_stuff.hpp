#ifndef liborangepower_defer_stuff_hpp
#define liborangepower_defer_stuff_hpp

#include <memory>
#include <functional>

#define defer(name, ...) \
	auto DEFER_ ## name = std::shared_ptr<void>(nullptr, \
		std::bind([&]() -> void \
		{ \
			__VA_ARGS__ \
		}))


#define with_defer(...) \
	if (defer(SUFFIX, __VA_ARGS__); true)


#endif		// liborangepower_defer_stuff_hpp
