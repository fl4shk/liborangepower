#ifndef liborangepower_containers_defer_stuff_hpp
#define liborangepower_containers_defer_stuff_hpp

#include "../misc/misc_includes.hpp"

namespace liborangepower {
namespace containers {
//--------
//template<typename T>
//class GenMvDstry final
//requires (std::copyable<T> && std::movable<T>) {
//private:		// variables
//	T _self;
//public:		// functions
//	inline GenMvDstry(const T& s_self) {
//	}
//};
class Defer final {
private:		// variables
	std::function<void()> _func;
public:		// functions
	inline Defer(const std::function<void()>& s_func)
		: _func(s_func) {
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Defer);
	inline ~Defer() {
		_func();
	}
};
//template<typename T>
//class DeferDtor final {
//prviate:		// variables
//	T* _obj = nullptr;
//	std::function<void(T*)> _func;
//public:		// functions
//	inline DeferDtor(T* s_obj, const std::function<void(T*)>& s_func)
//		: _obj(s_obj), _func(s_func) {
//	}
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DeferDtor);
//	inline ~DeferDtor() {
//	}
//};
//--------
} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_defer_stuff_hpp
