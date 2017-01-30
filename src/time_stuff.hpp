// This file is part of Lib Orange Power.
// 
// Copyright (C) 2017 Andrew Clark (FL4SHK)
// 
// Lib Orange Power is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Lib Orange Power is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
// General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with Lib Orange Power.  If not, see
// <http://www.gnu.org/licenses/>.


#ifndef time_stuff_hpp
#define time_stuff_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"

class prng
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
		return ( std::chrono::high_resolution_clock::now()
			.time_since_epoch().count() * ( get_param_0() + 1 ) )
			+ get_param_1();
	}
	
public:		// functions
	inline prng( int s_param_0, int s_param_1 ) 
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
	
	inline auto operator () ( u64 max_val, const bool use_cap=false )
	{
		auto ret = (*this)();
		
		if (!use_cap)
		{
			ret %= max_val;
		}
		else // if (use_cap)
		{
			if ( ret > max_val )
			{
				ret = max_val;
			}
		}
		
		return ret;
	}
	
} __attribute__((_align4));


class profiler
{
protected:		// variables
	std::chrono::high_resolution_clock::time_point start_tp, end_tp;
	
protected:		// functions
	static inline auto get_hrc_now()
	{
		return std::chrono::high_resolution_clock::now();
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



#endif		// time_stuff_hpp
