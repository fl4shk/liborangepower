#ifndef src_test_class_hpp
#define src_test_class_hpp

// src/test_class.hpp

#include "misc_includes.hpp"
#include "hierarchy_classes.hpp"

class Test final
{
public:		// serialized variables
	#define MEMB_LIST_TEST(X) \
		X(data, _data_func_map)

	std::unordered_map<std::string, std::unique_ptr<Base>> data;
private:		// non-serialized variables
	FromJvFactoryFuncMap<Base> _data_func_map;
public:		// functions
	Test();
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Test);
	virtual ~Test() = default;

	void deserialize(const Json::Value& jv);
	virtual operator Json::Value () const;
};


#endif		// src_test_class_hpp
