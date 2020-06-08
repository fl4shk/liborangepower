#ifndef liborangepower_lang_ast_node_base_class_hpp
#define liborangepower_lang_ast_node_base_class_hpp

// lang/ast_node_base_class.hpp

#include "../misc/misc_includes.hpp"
#include "../metaprog_defines.hpp"
#include "../containers/linked_list_classes.hpp"
#include "../misc/misc_output_classes.hpp"

#include "ast_visitor_base_class.hpp"
#include "file_pos_class.hpp"

#include "ast_node_base_class_defines.hpp"

namespace liborangepower
{

//class Symbol;

namespace lang
{

using containers::IndCircLinkList;
using namespace misc_output;

//--------
class AstNodeBase;
using AstNodeBaseUptr = unique_ptr<AstNodeBase>;
using AstNodeBaseUptrList = containers::IndCircLinkList<AstNodeBaseUptr>;

class AstNodeBase
{
public:		// types
protected:		// variables
	AstNodeBase* _parent = nullptr;
	FilePos _fp;
	size_t _level = 0;

//public:		// variables
//	Symbol* sym = nullptr;

public:		// functions
	inline AstNodeBase() = default;
	inline AstNodeBase(AstNodeBase* s_parent, const FilePos& s_fp)
		: _parent(s_parent), _fp(s_fp)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(AstNodeBase);
	virtual inline ~AstNodeBase() = default;
	virtual inline std::string id() const
	{
		return std::string("AstNodeBase");
	}

	// Derived classes should fill these in
	virtual inline void accept(AstVisitorBase* visitor)
	{
	}
	virtual inline void dup_data(AstNodeBase* dst) const
	{
	}
	virtual inline std::string wrap_data() const
	{
		return "";
	}
	virtual inline AstNodeBaseUptr dup(AstNodeBase* s_parent) const
	{
		return AstNodeBaseUptr();
	}
	virtual inline void accept_children(AstVisitorBase* visitor)
	{
	}
	virtual inline void accept_children(AstVisitorBase* visitor,
		const AstNodeBaseUptr& other)
	{
	}

	GEN_GETTER_BY_VAL(parent);
	GEN_GETTER_BY_CON_REF(fp);
	GEN_GETTER_BY_VAL(level);

protected:		// functions
	static inline void _inner_accept_children
		(AstVisitorBase* visitor, const std::string& memb_name,
		AstNodeBaseUptr& child)
	{
		if (child)
		{
			visitor->set_memb_name(memb_name);
			child->accept(visitor);
		}
	}
	static inline void _inner_accept_children
		(AstVisitorBase* visitor, const std::string& memb_name,
		AstNodeBaseUptrList& child_list)
	{
		size_t i = 0;
		for (const auto& child: child_list)
		{
			visitor->set_memb_name(sconcat(memb_name, "[", i, "]"));
			child.data->accept(visitor);
			++i;
		}
	}

	static inline void _inner_dup(AstNodeBase* s_parent,
		AstNodeBaseUptr& item,
		const AstNodeBaseUptr& other_item)
	{
		if (other_item)
		{
			item = other_item->dup(s_parent);
		}
	}
	static inline void _inner_dup(AstNodeBase* s_parent,
		AstNodeBaseUptrList& item_list,
		const AstNodeBaseUptrList& other_item_list)
	{
		for (const auto& other_item: other_item_list)
		{
			item_list.push_back(other_item.data->dup(s_parent));
		}
	}
};
//--------

} // namespace lang
} // namespace liborangepower


#endif		// liborangepower_lang_ast_node_base_class_hpp
