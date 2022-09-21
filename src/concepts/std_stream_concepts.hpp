#ifndef liborangepower_concepts_std_stream_concepts_hpp
#define liborangepower_concepts_std_stream_concepts_hpp

#include "../misc/misc_includes.hpp"

namespace liborangepower
{
namespace concepts
{
//--------
template<typename T>
concept HasStdOstmOpLshift = requires(T c, std::ostream& os)
{
	{ os << c };
};
template<typename T>
concept HasStdIstmOpRshift = requires(T c, std::istream& is)
{
	{ is >> c };
};
//--------
} // namespace concepts
} // namespace liborangepower

#endif		// liborangepower_concepts_std_stream_concepts_hpp
