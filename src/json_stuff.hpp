#ifndef liborangepower_json_stuff_hpp
#define liborangepower_json_stuff_hpp

#include "misc_includes.hpp"
#include "misc_output_classes.hpp"

// jsoncpp headers
#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>


namespace liborangepower
{

namespace json
{

template<typename... arg_types>
void err(arg_types&&... args)
{
	printout_etc::printerr("Error:  ", args..., "\n");
	exit(1);
}

std::string get_json_value_type_as_str(const Json::Value& some_value);
inline std::string get_json_value_type_as_str(Json::Value* iter)
{
	return std::move(get_json_value_type_as_str(*iter));
}

inline void print_json_value_type(const Json::Value& some_value,
	std::ostream& os=std::cout)
{
	osprintout(os, std::move(get_json_value_type_as_str(some_value)));
}
inline void print_json_value_type(Json::Value* iter, 
	std::ostream& os=std::cout)
{
	osprintout(os, std::move(get_json_value_type_as_str(iter)));
}

bool parse_json(Json::CharReaderBuilder* rbuilder, std::istream& is,
	Json::Value* root, std::string* errs);
bool parse_json(Json::CharReaderBuilder* rbuilder, 
	const std::string& input_file_name, Json::Value* root, 
	std::string* errs);

inline bool parse_json(std::istream& is, Json::Value* root, 
	std::string* errs)
{
	return parse_json(nullptr, is, root, errs);
}
inline bool parse_json(const std::string& input_file_name, 
	Json::Value* root, std::string* errs)
{
	return parse_json(nullptr, input_file_name, root, errs);
}


void write_json(Json::StreamWriterBuilder* wbuilder,
	std::ostream& os, Json::Value* root);
void write_json(Json::StreamWriterBuilder* wbuilder,
	const std::string& output_file_name, Json::Value* root);

inline void write_json(std::ostream& os, Json::Value* root)
{
	write_json(nullptr, os, root);
}
inline void write_json(const std::string& output_file_name, 
	Json::Value* root)
{
	write_json(nullptr, output_file_name, root);
}



// A recursive function for printing out the contents of a JSON file.
// Note that it does NOT print out valid JSON, just something similar.
// The main difference from real JSON is that every value ends with a
// comma, even when at the end of an objectValue or arrayValue.
void debug_print_json(const Json::Value& some_value, 
	std::ostream& os=std::cout, size_t tabs_level=0);
inline void debug_print_json(Json::Value* iter, std::ostream& os=std::cout,
	size_t tabs_level=0)
{
	debug_print_json(*iter, os, tabs_level);
}

}

}

#endif		// liborangepower_json_stuff_hpp
