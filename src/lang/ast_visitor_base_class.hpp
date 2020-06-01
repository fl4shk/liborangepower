#ifndef liborangepower_lang_ast_visitor_base_class_hpp
#define liborangepower_lang_ast_visitor_base_class_hpp

// lang/ast_visitor_base_class.hpp

#include "../misc/misc_includes.hpp"
#include "../containers/linked_list_classes.hpp"
#include "file_pos_class.hpp"

#include <variant>

namespace liborangepower
{
namespace lang
{

using containers::IndCircLinkList;

class AstNodeBase;
using AstNodeBaseUptr = unique_ptr<AstNodeBase>;
using AstNodeBaseUptrList = IndCircLinkList<AstNodeBaseUptr>;

class AstVisitorBase
{
	friend class AstNodeBase;

public:		// types
	using Child = std::variant<AstNodeBaseUptr, AstNodeBaseUptrList>;

protected:		// variables
	string _memb_name;
	Child _child;

public:		// functions
	inline AstVisitorBase() = default;
	virtual inline ~AstVisitorBase() = default;

	GEN_GETTER_AND_SETTER_BY_CON_REF(memb_name);
};

} // namespace lang
} // namespace liborangepower


#endif		// lang_ast_visitor_base_class_hpp
