#ifndef liborangepower_sdl2_sdl_thread_hpp
#define liborangepower_sdl2_sdl_thread_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <algorithm>
#include <SDL.h>
#include <SDL_thread.h>

namespace liborangepower {
namespace sdl {
//--------
class Thread final {
private:		// variables
	SDL_Thread* _self = nullptr;
public:		// functions
	inline Thread(SDL_Thread* s_self=nullptr)
		: _self(s_self) {
	}
	inline Thread(const Thread& to_copy) = delete;
	inline Thread(Thread&& to_move) {
		*this = std::move(to_move);
	}
	inline ~Thread() {
		if (_self != nullptr) {
			SDL_DetachThread(_self);
		}
	}
	inline Thread& operator = (const Thread& to_copy)
		= delete;
	inline Thread& operator = (Thread&& to_move) {
		std::swap(_self, to_move._self);

		return *this;
	}
	inline bool operator ! () const {
		return (!_self);
	}
	inline operator SDL_Thread* () {
		return _self;
	}
	inline auto* operator -> () {
		return _self;
	}
	inline const auto* operator -> () const {
		return _self;
	}

	GEN_GETTER_BY_REF(self);
};
//--------
} // namespace sdl
} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_thread_hpp
