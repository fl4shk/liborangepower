#ifndef liborangepower_arg_parsing_stuff_hpp
#define liborangepower_arg_parsing_stuff_hpp

#include "misc_types.hpp"
#include "misc_includes.hpp"
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
	inline OptArg(const string& to_parse)
	{
		bool old_left, left = true;

		for (const auto& c: to_parse)
		{
			if (left)
			{
				if (isalnum(c) || (c == '_'))
				{
					_opt += c;
				}
				else
				{
					old_left = left;
					left = false;
				}
			}
			else // if (!left)
			{
				if (old_left)
				{
					if (c != '=')
					{
						_valid = false;
						break;
					}
				}
				else // if (!old_left)
				{
					_val += c;
				}
				old_left = left;
			}
		}

		if (_opt.size() == 0)
		{
			_valid = false;
		}
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(OptArg);
	inline ~OptArg() = default;

	GEN_GETTER_BY_CON_REF(opt);
	GEN_GETTER_BY_CON_REF(val);
	GEN_GETTER_BY_VAL(val);
};

} // namespace arg_parse

} // namespace liborangepower

#endif		// liborangepower_arg_parsing_stuff_hpp
