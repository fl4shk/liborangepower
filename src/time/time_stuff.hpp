#ifndef liborangepower_time_stuff_time_stuff_hpp
#define liborangepower_time_stuff_time_stuff_hpp

#include "../misc/misc_defines.hpp"
#include "../misc/misc_types.hpp"
#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <iomanip>

#include <pcg_random.hpp>

namespace liborangepower
{

using integer_types::u64;
using integer_types::i64;

namespace time
{
//--------
inline auto get_hrc_now()
{
	return std::chrono::high_resolution_clock::now();
}
inline auto get_hrc_now_time_t()
{
	return std::chrono::high_resolution_clock::to_time_t(get_hrc_now());
}
inline auto get_hrc_now_rng_seed()
{
	return get_hrc_now().time_since_epoch().count();
}
//--------
inline std::time_t now_as_time_t()
{
	return get_hrc_now_time_t();
}
inline std::tm* now_as_localtime()
{
	auto now = now_as_time_t();
	auto ret = std::localtime(&now);

	return ret;
}
inline std::tm* now_as_gmtime()
{
	auto now = now_as_time_t();
	auto ret = std::gmtime(&now);

	return ret;
}
//--------
inline auto put_now_as_localtime()
{
	//return std::put_time(now_as_localtime(), "%c");
	return std::put_time(now_as_localtime(), "%Y-%m-%d %H:%M:%S %Z");
}
inline auto put_now_as_gmtime()
{
	//return std::put_time(now_as_gmtime(), "%c");
	return std::put_time(now_as_gmtime(), "%Y-%m-%d %H:%M:%S %Z");
}
//--------
template<typename _InstanceT=pcg64>
class Prng final
{
public:		// types
	using SeedT = decltype(get_hrc_now_rng_seed());

	//using InstanceT = std::minstd_rand;
	//using InstanceT = std::mt19937;
	//using InstanceT = std::mt19937_64;
	using InstanceT = _InstanceT;

protected:		// variables
	i64 _param_0, _param_1;

	InstanceT _instance;

protected:		// functions
	inline SeedT _default_initial_seed()
	{
		// I have no idea how good this is, but it seems to work?
		return (get_hrc_now_rng_seed() * (param_0() + 1))
			+ param_1();
	}

public:		// functions
	inline Prng(i64 s_param_0=0, i64 s_param_1=0) 
		: _param_0(s_param_0), _param_1(s_param_1),
		_instance(_default_initial_seed())
	{
	}
	inline Prng(SeedT s_seed)
		: _instance(s_seed)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Prng);
	inline ~Prng() = default;

	inline auto operator () ()
	{
		return _instance();
	}
	inline auto operator () (u64 max_val, bool saturate=false)
	{
		auto ret = (*this)();

		if (!saturate)
		{
			ret %= max_val;
		}
		else // if (saturate)
		{
			if (ret > max_val)
			{
				ret = max_val;
			}
		}

		return ret;
	}
	template<typename T>
	inline auto run()
	{
		return T((*this)());
	}
	template<typename T>
	inline auto run(const T& max_val, bool saturate=false)
	{
		//return T(_instance());
		return T((*this)(u64(max_val), saturate));
	}
	template<std::floating_point FloatT=float>
	inline auto run(FloatT scale)
	{
		return run<Float>() * scale;
	}
	template<std::floating_point FloatT=float>
	inline auto run(FloatT scale, FloatT max_val,
		bool saturate=false)
	{
		return run<FloatT>(max_val, saturate) * scale;
	}

	// For serialization
	template<typename CharT, typename Traits=std::char_traits<CharT>>
	inline std::basic_ostream<CharT, Traits>& operator <<
		(std::basic_ostream<CharT, Traits>& os) const
	{
		os << _instance;
		return os;
	}
	template<typename CharT, typename Traits=std::char_traits<CharT>>
	inline std::basic_istream<CharT, Traits>& operator >>
		(std::basic_istream<CharT, Traits>& is)
	{
		is >> _instance;
		return is;
	}

	GEN_GETTER_BY_VAL(param_0)
	GEN_GETTER_BY_VAL(param_1)
	GEN_GETTER_BY_CON_REF(instance)
};
//--------
class Profiler
{
protected:		// variables
	std::chrono::high_resolution_clock::time_point start_tp, end_tp;

public:		// functions

public:		// functions
	inline void start()
	{
		start_tp = get_hrc_now();
	}

	inline auto stop()
	{
		end_tp = get_hrc_now();

		std::chrono::duration<double> diff_dtn = end_tp - start_tp;

		return diff_dtn.count();
	}
};
//--------
} // namespace time
} // namespace liborangepower



#endif		// liborangepower_time_stuff_time_stuff_hpp
