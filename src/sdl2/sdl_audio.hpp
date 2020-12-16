#ifndef liborangepower_sdl2_sdl_audio_hpp
#define liborangepower_sdl2_sdl_audio_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

namespace liborangepower
{

namespace sdl
{

class AudioDevice final
{
private:		// variables
	SDL_AudioDeviceID _dev;

public:		// functions
	inline AudioDevice(SDL_AudioDeviceID s_dev)
		: _dev(s_dev)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AudioDevice);
	inline ~AudioDevice()
	{
		SDL_CloseAudioDevice(_dev);
	}

	GEN_GETTER_BY_REF(dev);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_audio_hpp
