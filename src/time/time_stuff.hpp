#ifndef liborangepower_time_stuff_time_stuff_hpp
#define liborangepower_time_stuff_time_stuff_hpp

#include "../misc/misc_defines.hpp"
#include "../misc/misc_types.hpp"
#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include "../math/misc_funcs.hpp"

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
template<typename RngT>
concept CallableLikeRng = requires(RngT rng)
{
	{ rng() };
};

template<typename T, CallableLikeRng RngT>
inline auto rng_run(RngT& rng)
{
	return T(rng());
}
template<typename T, CallableLikeRng RngT>
inline auto rng_run(RngT& rng, const T& max, bool saturate=false)
{
	T ret = rng_run<T>(rng);

	if (!saturate)
	{
		ret %= max;
	}
	else // if (saturate)
	{
		if (ret > max)
		{
			ret = max;
		}
	}

	return ret;
}
template<typename T, CallableLikeRng RngT>
inline auto rng_run_mm(RngT& rng, const T& max, const T& min,
	bool saturate=false)
{
	return rng_run<T>(rng, math::cstm_abs(max - min), saturate) + min;
}

template<typename T, CallableLikeRng RngT>
inline auto rng_run_scaled(RngT& rng, const T& scale)
{
	return rng_run<T>(rng) * scale;
}
template<typename T, CallableLikeRng RngT>
inline auto rng_run_scaled(RngT& rng, const T& scale, const T& max,
	bool saturate=false)
{
	return rng_run<T>(rng, max, saturate) * scale;
}
template<typename T, CallableLikeRng RngT>
inline auto rng_run_scaled_mm(RngT& rng, const T& scale, const T& max,
	const T& min, bool saturate=false)
{
	return rng_run_mm<T>(rng, max, min, saturate) * scale;
}

template<typename _InstanceT=std::mt19937_64>
class Prng final
{
public:		// types
	using SeedT = decltype(get_hrc_now_rng_seed());

	//using InstanceT = std::minstd_rand;
	//using InstanceT = std::mt19937;
	//using InstanceT = std::mt19937_64;
	using InstanceT = _InstanceT;
private:		// variables
	//i64 _param_0, _param_1;

	InstanceT _instance;
private:		// functions
	inline SeedT _default_initial_seed(i64 param_0, i64 param_1)
	{
		// I have no idea how good this is, but it seems to work?
		return (get_hrc_now_rng_seed() * (param_0 + i64(1))) + param_1;
	}
public:		// functions
	inline Prng(i64 param_0=0, i64 param_1=0)
		: _instance(_default_initial_seed(param_0, param_1))
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
		return rng_run<decltype(_instance())>(_instance);
	}
	template<typename T>
	inline auto operator () (const T& max, bool saturate=false)
	{
		return rng_run<T>(_instance, max, saturate);
	}
	template<typename T>
	inline auto run()
	{
		return rng_run<T>(_instance);
	}
	template<typename T>
	inline auto run_scale(const T& scale)
	{
		return rng_run_scaled<T>(_instance, scale);
	}
	template<typename T>
	inline auto run_scaled(const T& scale, const T& max,
		bool saturate=false)
	{
		return rng_run_scaled<T>(_instance, scale, max, saturate);
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

	//GEN_GETTER_BY_VAL(param_0)
	//GEN_GETTER_BY_VAL(param_1)
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
