#ifndef liborangepower_time_stuff_time_stuff_hpp
#define liborangepower_time_stuff_time_stuff_hpp

#include "../misc/misc_defines.hpp"
#include "../misc/misc_types.hpp"
#include "../misc/misc_includes.hpp"
#include "../gen_class_innards_defines.hpp"

#include <iomanip>

namespace liborangepower
{
namespace time
{

inline auto get_hrc_now()
{
	return std::chrono::high_resolution_clock::now();
}
inline auto get_hrc_now_time_t()
{
	return std::chrono::high_resolution_clock::to_time_t(get_hrc_now());
}

class Prng
{
public:		// types
	using integer_types::i64;
	using integer_types::u64;

	using SeedT = decltype(get_hrc_now().time_since_epoch().count());

	//using InstanceT = std::minstd_rand;
	//using InstanceT = std::mt19937;
	using InstanceT = std::mt19937_64;

protected:		// variables
	i64 _param_0, _param_1;

	InstanceT _instance;

protected:		// functions
	inline SeedT _default_initial_seed()
	{
		// I have no idea how good this is, but it seems to work?
		return (get_hrc_now().time_since_epoch().count() * (param_0() + 1))
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

	inline ~Prng() = default;

	inline auto operator () ()
	{
		return _instance();
	}

	inline auto operator () (u64 max_val, const bool saturate=false)
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
		return static_cast<T>(_instance());
	}

	GEN_GETTER_BY_VAL(param_0)
	GEN_GETTER_BY_VAL(param_1)
	GEN_GETTER_BY_CON_REF(instance)
};


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


} // namespace time
} // namespace liborangepower



#endif		// liborangepower_time_stuff_time_stuff_hpp
