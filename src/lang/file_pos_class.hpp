#ifndef liborangepower_lang_file_pos_class_hpp
#define liborangepower_lang_file_pos_class_hpp

// src/file_pos_class.hpp

#include "../misc/misc_includes.hpp"
#include "../misc/misc_output_classes.hpp"

namespace liborangepower
{

namespace lang
{

class FilePos final
{
protected:		// variables
	string _filename;
	size_t _line = 0, _pos_in_line = 0;
public:		// functions
	inline FilePos() = default;
	inline FilePos(const string& s_filename, size_t s_line,
		size_t s_pos_in_line)
		: _filename(s_filename), _line(s_line), _pos_in_line(s_pos_in_line)
	{
	}
	inline FilePos(string&& s_filename, size_t s_line,
		size_t s_pos_in_line)
		: _filename(move(s_filename)), _line(s_line),
		_pos_in_line(s_pos_in_line)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(FilePos);
	virtual inline ~FilePos() = default;

	virtual void warn(const string& msg) const
	{
		misc_output::printerr("Warning in file \"", filename(),
			"\" on line ", line(), ", position ", pos_in_line(), ":  ",
			msg, "\n");
	}
	virtual void err(const string& msg) const
	{
		misc_output::printerr("Error in file \"", filename(),
			"\" on line ", line(), ", position ", pos_in_line(), ":  ",
			msg, "\n");
		exit(1);
	}
	//inline size_t line() const
	//{
	//	return ctx()->getStart()->getLine();
	//}
	//inline size_t pos_in_line() const
	//{
	//	return ctx()->getStart()->getCharPositionInLine();
	//}

	GEN_GETTER_AND_SETTER_BY_CON_REF(filename);
	GEN_SETTER_BY_RVAL_REF(filename);
	GEN_GETTER_AND_SETTER_BY_VAL(line);
	GEN_GETTER_AND_SETTER_BY_VAL(pos_in_line);
};

} // namespace lang

} // namespace liborangepower

inline std::ostream& operator << (std::ostream& os,
	const liborangepower::lang::FilePos& fp)
{
	return liborangepower::misc_output::osprintout(os, fp.filename(), ":",
		fp.line(), ":", fp.pos_in_line());
}

#endif		// liborangepower_lang_file_pos_class_hpp
