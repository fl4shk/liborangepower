#ifndef liborangepower_time_stuff_hpp
#define liborangepower_time_stuff_hpp

#include "misc_defines.hpp"
#include "misc_types.hpp"
#include "misc_includes.hpp"
#include "gen_getter_setter_defines.hpp"

#include <iomanip>


namespace liborangepower
{

namespace time
{

class Prng
{
public:		// typedefs
	typedef decltype(std::chrono::high_resolution_clock::now()
		.time_since_epoch().count()) SeedType;

	//typedef std::minstd_rand InstanceType;
	//typedef std::mt19937 InstanceType;
	typedef std::mt19937_64 InstanceType;

protected:		// variables
	int ___param_0, ___param_1;

	InstanceType ___instance;


protected:		// functions
	inline SeedType initial_seed()
	{
		// I have no idea how good this is, but it seems to work?
		return (std::chrono::high_resolution_clock::now()
			.time_since_epoch().count() * (param_0() + 1)) + param_1();
	}

public:		// functions
	inline Prng(int s_param_0=0, int s_param_1=0) 
		: ___param_0(s_param_0), ___param_1(s_param_1),
		___instance(initial_seed())
	{
	}

	gen_getter_by_val(param_0);
	gen_getter_by_val(param_1);
	gen_getter_by_con_ref(instance);


	inline auto operator () ()
	{
		return ___instance();
	}

	template<typename Type>
	inline auto run()
	{
		return static_cast<Type>(___instance());
	}

	inline auto operator () (integer_types::u64 max_val, 
		const bool saturate=false)
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

};


class Profiler
{
protected:		// variables
	std::chrono::high_resolution_clock::time_point start_tp, end_tp;

public:		// functions
	static inline auto get_hrc_now()
	{
		return std::chrono::high_resolution_clock::now();
	}
	static inline auto get_hrc_now_time_t()
	{
		return std::chrono::high_resolution_clock::to_time_t
			(get_hrc_now());
	}

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
	return Profiler::get_hrc_now_time_t();
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



#endif		// liborangepower_time_stuff_hpp
