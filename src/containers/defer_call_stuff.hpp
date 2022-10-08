#ifndef liborangepower_containers_defer_call_stuff_hpp
#define liborangepower_containers_defer_call_stuff_hpp

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
#define mk_defer_func(...) \
	std::bind([&]() -> void { \
		__VA_ARGS__ \
	})
class DeferCall final {
public:		// types
	using Func = std::function<void()>;
private:		// variables
	Func _func;
public:		// functions
	inline DeferCall() {
	}
	inline DeferCall(const Func& s_func)
		: _func(s_func) {
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DeferCall);
	inline ~DeferCall() {
		//printout("DeferCall::~DeferCall(): ", bool(_func), "\n");
		if (_func) {
			_func();
		}
	}
};
//template<typename T>
//class DeferDtorCall final {
//public:		// types
//	using DtorFunc = std::function<void(T*)>;
//private:		// variables
//	T* _obj = nullptr;
//	DeferCall _dc;
//public:		// functions
//	inline DeferDtorCall(T* s_obj, const DtorFunc& s_func)
//		: _obj(s_obj) {
//		_dc = DeferCall([this, &s_func]() -> void { s_func(_obj); });
//	}
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DeferDtorCall);
//	inline ~DeferDtorCall() {
//	}
//};
//--------
} // namespace containers
} // namespace liborangepower

#endif		// liborangepower_containers_defer_call_stuff_hpp
