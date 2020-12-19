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
	static constexpr size_t HEADER_SIZE = 44;
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
		return (HEADER_SIZE + _sample_vec.size());
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
		ret.push_back('R');
		ret.push_back('I');
		ret.push_back('F');
		ret.push_back('F');

		ret.push_back((file_length_minus_8() >> 0) & 0xff);
		ret.push_back((file_length_minus_8() >> 8) & 0xff);
		ret.push_back((file_length_minus_8() >> 16) & 0xff);
		ret.push_back((file_length_minus_8() >> 24) & 0xff);

		ret.push_back('W');
		ret.push_back('A');
		ret.push_back('V');
		ret.push_back('E');
		//--------


		//--------
		// The `fmt` chunk
		ret.push_back('f');
		ret.push_back('m');
		ret.push_back('t');
		ret.push_back(' ');

		// Length of the `fmt` data (16 bytes)
		ret.push_back(0x10);
		ret.push_back(0x00);
		ret.push_back(0x00);
		ret.push_back(0x00);

		// Format tag:  1 = PCM
		ret.push_back(0x01);
		ret.push_back(0x00);

		// Channels:  1 = mono, 2 = stereo
		ret.push_back((channels() >> 0) & 0xff);
		ret.push_back((channels() >> 8) & 0xff);

		// Samples per second
		ret.push_back((sample_rate() >> 0) & 0xff);
		ret.push_back((sample_rate() >> 8) & 0xff);
		ret.push_back((sample_rate() >> 16) & 0xff);
		ret.push_back((sample_rate() >> 24) & 0xff);

		// bytes/second
		ret.push_back((bytes_per_second() >> 0) & 0xff);
		ret.push_back((bytes_per_second() >> 8) & 0xff);
		ret.push_back((bytes_per_second() >> 16) & 0xff);
		ret.push_back((bytes_per_second() >> 24) & 0xff);

		// block align
		ret.push_back((block_align() >> 0) & 0xff);
		ret.push_back((block_align() >> 8) & 0xff);

		// bits/sample
		ret.push_back((bits_per_sample() >> 0) & 0xff);
		ret.push_back((bits_per_sample() >> 8) & 0xff);
		//--------


		//--------
		// The `data` chunk
		ret.push_back('d');
		ret.push_back('a');
		ret.push_back('t');
		ret.push_back('a');

		const auto DATA_BLOCK_LENGTH = (sample_vec().size() * sizeof(u8);
		ret.push_back((DATA_BLOCK_LENGTH >> 0) & 0xff);
		ret.push_back((DATA_BLOCK_LENGTH >> 8) & 0xff);
		ret.push_back((DATA_BLOCK_LENGTH >> 16) & 0xff);
		ret.push_back((DATA_BLOCK_LENGTH >> 24) & 0xff);

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
