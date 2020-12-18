#ifndef liborangepower_sdl2_sdl_audio_hpp
#define liborangepower_sdl2_sdl_audio_hpp

#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"
#include "../misc/memwhatever_wrappers.hpp"

#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

namespace liborangepower
{

namespace sdl
{

class Wav final
{
private:		// variables
	std::string _filename;
	SDL_AudioSpec _spec;
	Uint32 _length;
	Uint8* _buffer;

public:		// functions
	inline Wav(const std::string& s_filename, bool* err=nullptr)
		: _filename(s_filename)
	{
		if (_filename.size() > 0)
		{
			auto temp = SDL_LoadWAV(_filename.c_str(), &_spec, &_length,
				&_buffer);
			if (err != nullptr)
			{
				*err = (temp == NULL);
			}
		}
		else // if (_filename.size() == 0)
		{
			misc_util::arr_memset(&_spec, 0, 1);
			_length = 0;
			_buffer = nullptr;
		}
	}
	inline Wav(const Wav& to_copy) = delete;
	inline Wav(Wav&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~Wav()
	{
		if (is_open())
		{
			SDL_FreeWAV(_buffer);
		}
	}
	inline Wav& operator = (const Wav& to_copy)
		= delete;
	inline Wav& operator = (Wav&& to_move)
	{
		std::swap(_filename, to_move._filename);
		std::swap(_spec, to_move._spec);
		std::swap(_length, to_move._length);
		std::swap(_buffer, to_move._buffer);

		return *this;
	}

	inline bool is_open() const
	{
		return (_buffer != nullptr);
	}

	GEN_GETTER_BY_CON_REF(filename);
	GEN_GETTER_BY_CON_REF(spec);
	GEN_GETTER_BY_VAL(length);
	GEN_GETTER_BY_VAL(buffer);
};

class AudioDevice final
{
private:		// variables
	bool _valid = false;
	SDL_AudioDeviceID _dev;

public:		// functions
	inline AudioDevice()
		: _valid(false), _dev(0)
	{
	}
	inline AudioDevice(SDL_AudioDeviceID s_dev)
		: _valid(true), _dev(s_dev)
	{
	}
	inline AudioDevice(const AudioDevice& to_copy) = delete;
	inline AudioDevice(AudioDevice&& to_move)
	{
		*this = std::move(to_move);
	}
	inline ~AudioDevice()
	{
		if (_valid)
		{
			SDL_CloseAudioDevice(_dev);
		}
	}

	inline AudioDevice& operator = (const AudioDevice& to_copy) = delete;
	inline AudioDevice& operator = (AudioDevice&& to_move)
	{
		std::swap(_valid, to_move._valid);
		std::swap(_dev, to_move._dev);

		return *this;
	}

	GEN_GETTER_BY_REF(valid);
	GEN_GETTER_BY_REF(dev);
};

} // namespace sdl

} // namespace liborangepower


#endif		// liborangepower_sdl2_sdl_audio_hpp
