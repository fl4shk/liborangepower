#ifndef liborangepower_media_audio_file_classes_hpp
#define liborangepower_media_audio_file_classes_hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_types.hpp"
#include "../misc/memwhatever_wrappers.hpp"
#include "../gen_class_innards_defines.hpp"

namespace liborangepower
{

namespace media
{

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
	SampleVec _sample_vec;

public:		// functions
	inline Wav(bool s_stereo, u32 s_sample_rate, 
		bool s_sixteen_bits_per_sample,
		const SampleVec& s_sample_vec)
		: _stereo(s_stereo), _sample_rate(s_sample_rate),
		_sixteen_bits_per_sample(s_sixteen_bits_per_sample),
		_sample_vec(s_sample_vec)
	{
	}
	inline Wav(bool s_stereo, u32 s_sample_rate,
		bool s_sixteen_bits_per_sample, SampleVec&& s_sample_vec)
		: _stereo(s_stereo), _sample_rate(s_sample_rate),
		_sixteen_bits_per_sample(s_sixteen_bits_per_sample),
		_sample_vec(std::move(s_sample_vec))
	{
	}

	inline u32 file_length_minus_8() const
	{
		return ((HEADER_LENGTH + _sample_vec.size()) - 8);
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
		return _sample_vec.at(index);
	}
	inline void set_mono_u8(size_t index, u8 n_sample)
	{
		_sample_vec.at(index) = n_sample;
	}

	inline i16 mono_i16_sample(size_t index) const
	{
		// WAV files encode data as little endian
		return byte_vec_get_i16_le(_sample_vec, index);
	}
	inline void set_mono_i16_sample(size_t index, i16 n_sample)
	{
		// Little endian
		byte_vec_set_i16_le(_sample_vec, index, n_sample);
	}

	inline u8 stereo_u8_sample(size_t index, bool channel) const
	{
		return _sample_vec.at((index * 2) + (channel ? 1 : 0));
	}
	inline void set_stereo_u8_sample(size_t index, bool channel,
		u8 n_sample)
	{
		_sample_vec.at((index * 2) + (channel ? 1 : 0)) = n_sample;
	}

	inline i16 stereo_i16_sample(size_t index, bool channel) const
	{
		//return _sample_vec.at((index * 2) + (channel ? 1 : 0));
		return mono_i16_sample
	}
	inline void set_stereo_i16_sampe(size_t index, bool channel,
		i16 n_sample)
	{
		set_mono_i16_sample(((index * 2) + (channel ? 1 : 0)), n_sample);
	}

	inline std::vector<u8> as_u8_vec() const
	{
		std::vector<u8> ret;

		//--------
		// RIFF header
		byte_vec_push_back_string(ret, "RIFF", false);

		byte_vec_push_back_u32_le(ret, file_length_minus_8());

		byte_vec_push_back_string(ret, "WAVE", false);
		//--------


		//--------
		// The `fmt` chunk
		byte_vec_push_back_string(ret, "fmt ", false);

		// Length of the `fmt` data (16 bytes)
		byte_vec_push_back_u32_le(ret, 0x00000010);

		// Format tag:  1 = PCM
		byte_vec_push_back_u16_le(ret, 0x0001);

		// Channels:  1 = mono, 2 = stereo
		byte_vec_push_back_u16_le(ret, channels());

		// Samples per second
		byte_vec_push_back_u32_le(ret, sample_rate());

		// bytes/second
		byte_vec_push_back_u32_le(ret, bytes_per_second());

		// block align
		byte_vec_push_back_u16_le(ret, block_align());

		// bits/sample
		byte_vec_push_back_u16_le(ret, bits_per_sample());
		//--------


		//--------
		// The `data` chunk
		ret.push_back('d');
		ret.push_back('a');
		ret.push_back('t');
		ret.push_back('a');

		byte_vec_push_back_u32_le(ret, (sample_vec.size() * sizeof(u8)));

		for (const auto& item: sample_vec())
		{
			ret.push_back(item);
		}
		//--------

		return ret;
	}

	GEN_GETTER_BY_VAL(sample_rate);
	GEN_GETTER_BY_CON_REF(sample_vec);
};

} // namespace media

} // namespace liborangepower

#endif		// liborangepower_media_audio_file_classes_hpp
