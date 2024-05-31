#ifndef liborangepower_media_audio_file_classes_hpp
#define liborangepower_media_audio_file_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../misc/memwhatever_wrappers.hpp"
#include "../misc/byte_vec_accessors.hpp"
#include "../gen_class_innards_defines.hpp"

#include <fstream>

namespace liborangepower
{

namespace media
{
struct Testificate;

using namespace integer_types;
using namespace misc_util;

class Wav
{
public:		// constants
	static constexpr size_t HEADER_LENGTH = 44;
	static constexpr u32 DEFAULT_SAMPLE_RATE = 44100;

public:		// types
	using SampleVec = std::vector<u8>;

protected:		// variables
	// Channels:  1 = mono, 2 = stereo
	bool _stereo = false;

	// Samples per second, e.g., 44100
	u32 _sample_rate = DEFAULT_SAMPLE_RATE; 

	// 8 or 16
	bool _sixteen_bits_per_sample;
	SampleVec _sample_darr;

public:		// functions
	inline Wav(bool s_stereo, u32 s_sample_rate,
		bool s_sixteen_bits_per_sample)
		: _stereo(s_stereo), _sample_rate(s_sample_rate),
		_sixteen_bits_per_sample(s_sixteen_bits_per_sample)
	{
	}
	inline Wav(bool s_stereo, u32 s_sample_rate, 
		bool s_sixteen_bits_per_sample, const SampleVec& s_sample_darr)
		: _stereo(s_stereo), _sample_rate(s_sample_rate),
		_sixteen_bits_per_sample(s_sixteen_bits_per_sample),
		_sample_darr(s_sample_darr)
	{
	}
	inline Wav(bool s_stereo, u32 s_sample_rate, 
		bool s_sixteen_bits_per_sample, SampleVec&& s_sample_darr)
		: _stereo(s_stereo), _sample_rate(s_sample_rate),
		_sixteen_bits_per_sample(s_sixteen_bits_per_sample),
		_sample_darr(std::move(s_sample_darr))
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Wav);
	virtual inline ~Wav() = default;

	inline u32 file_length_minus_8() const
	{
		return ((HEADER_LENGTH + sample_darr().size()) - 8);
	}

	inline u16 channels() const
	{
		return (_stereo ? 2 : 1);
	}
	inline u32 bytes_per_second() const
	{
		return (sample_rate() * block_align());
	}
	inline u16 block_align() const
	{
		return (channels() * (bits_per_sample() / 8));
	}
	inline u16 bits_per_sample() const
	{
		return (_sixteen_bits_per_sample ? 16 : 8);
	}

	inline u8 mono_u8_sample(size_t index) const
	{
		return _sample_darr.at(index);
	}
	inline void set_mono_u8_sample(size_t index, u8 n_sample)
	{
		_sample_darr.at(index) = n_sample;
	}
	inline void push_back_mono_u8_sample(u8 n_sample)
	{
		_sample_darr.push_back(n_sample);
	}

	inline i16 mono_i16_sample(size_t index) const
	{
		// WAV files encode data as little endian
		return get_i16_le(_sample_darr, index);
	}
	inline void set_mono_i16_sample(size_t index, i16 n_sample)
	{
		// Little endian
		set_i16_le(_sample_darr, index, n_sample);
	}
	inline void push_back_mono_i16_sample(i16 n_sample)
	{
		push_back_i16_le(_sample_darr, n_sample);
	}

	inline u8 stereo_u8_sample(size_t index, bool channel) const
	{
		return _sample_darr.at((index * 2) + (channel ? 1 : 0));
	}
	inline void set_stereo_u8_sample(size_t index, bool channel,
		u8 n_sample)
	{
		_sample_darr.at((index * 2) + (channel ? 1 : 0)) = n_sample;
	}
	inline void push_back_stereo_u8_sample_pair(u8 n_sample_0,
		u8 n_sample_1)
	{
		_sample_darr.push_back(n_sample_0);
		_sample_darr.push_back(n_sample_1);
	}

	inline i16 stereo_i16_sample(size_t index, bool channel) const
	{
		//return _sample_darr.at((index * 2) + (channel ? 1 : 0));
		return mono_i16_sample((index * 2) + (channel ? 1 : 0));
	}
	inline void set_stereo_i16_sampe(size_t index, bool channel,
		i16 n_sample)
	{
		set_mono_i16_sample(((index * 2) + (channel ? 1 : 0)), n_sample);
	}
	inline void push_back_stereo_i16_sample_pair(i16 n_sample_0,
		i16 n_sample_1)
	{
		push_back_i16_le(_sample_darr, n_sample_0);
		push_back_i16_le(_sample_darr, n_sample_1);
	}

	inline std::vector<u8> as_u8_darr() const
	{
		std::vector<u8> ret;

		//--------
		// RIFF header
		push_back_string(ret, "RIFF", false);

		push_back_u32_le(ret, file_length_minus_8());

		push_back_string(ret, "WAVE", false);
		//--------


		//--------
		// The `fmt` chunk
		push_back_string(ret, "fmt ", false);

		// Length of the `fmt` data (16 bytes)
		push_back_u32_le(ret, 0x00000010);

		// Format tag:  1 = PCM
		push_back_u16_le(ret, 0x0001);

		// Channels:  1 = mono, 2 = stereo
		push_back_u16_le(ret, channels());

		// Samples per second
		push_back_u32_le(ret, sample_rate());

		// bytes/second
		push_back_u32_le(ret, bytes_per_second());

		// block align
		push_back_u16_le(ret, block_align());

		// bits/sample
		push_back_u16_le(ret, bits_per_sample());
		//--------


		//--------
		// The `data` chunk
		push_back_string(ret, "data", false);

		push_back_u32_le(ret, (sample_darr().size() * sizeof(u8)));

		for (const auto& item: sample_darr())
		{
			ret.push_back(item);
		}
		//--------

		return ret;
	}

	// Returns whether or not writing the file succeeded
	inline bool write_to_file(const std::string& filename) const
	{
		if (auto file = std::fstream(filename, 
			(std::ios_base::binary 
				| std::ios_base::out
				| std::ios_base::trunc));
			file.is_open())
		{
			auto vec = as_u8_darr();

			for (const auto& item: vec)
			{
				file.put(static_cast<char>(item));
			}

			return true;
		}
		else
		{
			//printerr("Error:  Couldn't open \"", filename,
			//	"\" for writing.\n");
			//exit(1);
			return false;
		}
	}

	GEN_GETTER_BY_VAL(sample_rate);
	GEN_GETTER_BY_CON_REF(sample_darr);
	//GEN_SETTER_BY_CON_REF(sample_darr);
	GEN_SETTER_BY_RVAL_REF(sample_darr);
};

} // namespace media

} // namespace liborangepower

#endif		// liborangepower_media_audio_file_classes_hpp
