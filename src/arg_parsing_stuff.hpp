#ifndef liborangepower_arg_parsing_stuff_hpp
#define liborangepower_arg_parsing_stuff_hpp

#include "misc/misc_types.hpp"
#include "misc/misc_includes.hpp"
#include "misc/misc_output_classes.hpp"
#include "gen_class_innards_defines.hpp"
#include <ctype.h>

namespace liborangepower
{

namespace arg_parse
{

class OptArg final
{
private:		// variables
	std::string _opt, _val;
	bool _valid = true;
public:		// functions
	inline OptArg()
	{
	}
	inline OptArg(const std::string& to_parse, size_t num_prefixes=2,
		char prefix='-')
	{
		bool left = true;

		for (const auto& c: to_parse)
		{
			if (left)
			{
				if (_opt.size() < num_prefixes)
				{
					if (c == prefix)
					{
						_opt += c;
					}
					else // if (c != prefix)
					{
						_valid = false;
						break;
					}
				}
				else // if (_opt.size() >= num_prefixes)
				{
					if (isalnum(c) || (c == '_'))
					{
						_opt += c;
					}
					else
					{
						if ((_opt.size() < (num_prefixes + 1))
							|| (c != '='))
						{
							_valid = false;
							break;
						}
						else
						{
							left = false;
						}
					}
				}
			}
			else // if (!left)
			{
				_val += c;
			}
		}

		if (_opt.size() < (num_prefixes + 1))
		{
			_valid = false;
		}
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(OptArg);
	inline ~OptArg() = default;

	inline std::string errwarn_msg_dup() const
	{
		return misc_output::sconcat("Duplicate \"", opt(), "\" option.");
	}
	inline std::string errwarn_msg_has_val() const
	{
		return misc_output::sconcat("Option \"", opt(),
			"\" takes no value.");
	}
	inline std::string errwarn_msg_no_val() const
	{
		return misc_output::sconcat("Option \"", opt(),
			"\" requires a value.");
	}

	GEN_GETTER_BY_CON_REF(opt);
	GEN_GETTER_BY_CON_REF(val);
	GEN_GETTER_BY_VAL(valid);
};

} // namespace arg_parse

} // namespace liborangepower

#endif		// liborangepower_arg_parsing_stuff_hpp
