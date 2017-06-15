#ifndef liborangepower_time_stuff_hpp
#define liborangepower_time_stuff_hpp

#include "misc_defines.hpp"
#include "misc_types.hpp"
#include "misc_includes.hpp"

#include <iomanip>


namespace liborangepower
{

namespace time
{

class Prng
{
public:		// typedefs
	typedef decltype(std::chrono::high_resolution_clock::now()
		.time_since_epoch().count()) seed_type;
	
	//typedef std::minstd_rand instance_type;
	//typedef std::mt19937 instance_type;
	typedef std::mt19937_64 instance_type;
	
protected:		// variables
	int param_0, param_1;
	
	instance_type instance;
	
	
protected:		// functions
	inline seed_type get_initial_seed()
	{
		// I have no idea how good this is, but it seems to work?
		return (std::chrono::high_resolution_clock::now()
			.time_since_epoch().count() * (get_param_0() + 1))
			+ get_param_1();
	}
	
public:		// functions
	inline Prng(int s_param_0=0, int s_param_1=0) 
		: param_0(s_param_0), param_1(s_param_1),
		instance(get_initial_seed())
	{
	}
	
	inline int get_param_0() const
	{
		return param_0;
	}
	inline int get_param_1() const
	{
		return param_1;
	}
	
	inline auto operator () ()
	{
		return instance();
	}
	
	inline auto operator () (integer_types::u64 max_val, 
		const bool use_cap=false)
	{
		auto ret = (*this)();
		
		if (!use_cap)
		{
			ret %= max_val;
		}
		else // if (use_cap)
		{
			if (ret > max_val)
			{
				ret = max_val;
			}
		}
		
		return ret;
	}
	
} __attribute__((_align4));


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
	
	
} __attribute__((_align4));

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


}

}



#endif		// liborangepower_time_stuff_hpp
