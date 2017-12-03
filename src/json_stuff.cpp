#include "json_stuff.hpp"

using namespace liborangepower::printout_etc;

namespace liborangepower
{

namespace json
{

std::string get_json_value_type_as_str(const Json::Value& some_value)
{
	switch (some_value.type())
	{
		case Json::nullValue:
			return std::string("nullValue");
		case Json::intValue:
			return std::string("intValue");
		case Json::uintValue:
			return std::string("uintValue");
		case Json::realValue:
			return std::string("realValue");
		case Json::stringValue:
			return std::string("stringValue");
		case Json::booleanValue:
			return std::string("booleanValue");
		case Json::arrayValue:
			return std::string("arrayValue");
		case Json::objectValue:
			return std::string("objectValue");
		default:
			return std::string();
	}
}

bool parse_json(Json::CharReaderBuilder* rbuilder, std::istream& is,
	Json::Value* root, std::string* errs)
{
	auto parse = [&is, &root, &errs]
		(Json::CharReaderBuilder& actual_rbuilder) -> bool
	{
		actual_rbuilder["collectComments"] = false;

		const bool ret = Json::parseFromStream(actual_rbuilder, is, root, 
			errs);

		return ret;
	};
	
	if (rbuilder != nullptr)
	{
		return parse(*rbuilder);
	}

	Json::CharReaderBuilder actual_rbuilder;
	return parse(actual_rbuilder);
}

bool parse_json(Json::CharReaderBuilder* rbuilder, 
	const std::string& input_file_name, Json::Value* root, 
	std::string* errs)
{
	std::fstream infile(input_file_name, std::ios_base::in);

	if (!infile.is_open())
	{
		err("parse_json():  Can't open file called \"", input_file_name, 
			"\"!");
	}

	return parse_json(rbuilder, infile, root, errs);
}


void write_json(Json::StreamWriterBuilder* wbuilder, std::ostream& os, 
	Json::Value* root)
{
	auto write = [&os, &root](Json::StreamWriterBuilder& some_wbuilder)
	{
		some_wbuilder["commentStyle"] = "None";
		some_wbuilder["indentation"] = "\t";
		std::unique_ptr<Json::StreamWriter> writer
			(some_wbuilder.newStreamWriter());
		writer->write(*root, &os);
		os << std::endl;  // add lf and flush
	};
	
	if (wbuilder != nullptr)
	{
		write(*wbuilder);
	}
	else // if (wbuilder == nullptr)
	{
		Json::StreamWriterBuilder actual_wbuilder;
		write(actual_wbuilder);
	}
}
void write_json(Json::StreamWriterBuilder* wbuilder,
	const std::string& output_file_name, Json::Value* root)
{
	std::fstream outfile(output_file_name, std::ios_base::out);

	if (!outfile.is_open())
	{
		err("write_json():  Can't open file called \"", output_file_name,
			"\"!");
	}

	write_json(wbuilder, outfile, root);
}



void debug_print_json(const Json::Value& some_value, std::ostream& os, 
	size_t tabs_level)
{
	auto print_leading_tabs = [&]() -> void
	{
		for (size_t i=0; i<tabs_level; ++i)
		{
			osprintout(os, "\t");
		}
	};

	auto print_leading_tabs_2 = [&]() -> void
	{
		print_leading_tabs();
		osprintout(os, "\t");
	};

	auto print_arrayValue = [&]() -> void
	{
		osprintout(os, "[\n");
		
		for (const auto& inner_iter : some_value)
		{
			print_leading_tabs_2();
			debug_print_json(inner_iter, os, tabs_level + 1);
		}

		print_leading_tabs();
		osprintout(os, "],\n");
	};
	
	auto print_objectValue = [&]() -> void
	{
		const auto& member_names = some_value.getMemberNames();

		osprintout(os, "{\n");

		for (const auto& name_iter : member_names)
		{
			print_leading_tabs_2();
			osprintout(os, "\"", name_iter, "\" : ");
			debug_print_json(some_value[name_iter], os, tabs_level + 1);
		}

		print_leading_tabs();
		osprintout(os, "},\n");
	};
	
	switch (some_value.type())
	{
		case Json::nullValue:
		case Json::intValue:
		case Json::uintValue:
		case Json::realValue:
		case Json::booleanValue:
			osprintout(os, some_value.asString(), ",\n");
			break;
		
		case Json::stringValue:
			osprintout(os, "\"", some_value.asString(), "\",\n");
			break;

		case Json::arrayValue:
			print_arrayValue();
			break;

		case Json::objectValue:
			print_objectValue();
			break;

		default:
			err("debug_print_json():  Unknown Json::Value type()!");
	}
}

}

}
