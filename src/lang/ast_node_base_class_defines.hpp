#ifndef liborangepower_lang_ast_node_base_class_defines_hpp
#define liborangepower_lang_ast_node_base_class_defines_hpp

// lang/ast_node_base_class_defines.hpp

#define MEMB_VAR(type, name) \
	type, name

#define _DECL_MEMB_VAR(type, name) \
	type name
#define _COPY_MEMB_VAR(type, name) \
	casted_dst->name = name
#define _INNER_WRAP_DATA(type, name) \
	ret += sconcat(#name, ":  ", name) 

#define _PLUS_RAW_NEWLINE() + "\\n";

#define DATA(...) \
	IF (HAS_ARGS(__VA_ARGS__)) \
	( \
		EVAL(MAP_PAIRS(_DECL_MEMB_VAR, SEMICOLON, __VA_ARGS__)); \
		\
		virtual inline void dup_data(AstNodeBase* dst) const \
		{ \
			auto casted_dst = static_cast<Self*>(dst); \
			EVAL(MAP_PAIRS(_COPY_MEMB_VAR, SEMICOLON, __VA_ARGS__)); \
		} \
		virtual inline std::string wrap_data() const \
		{ \
			std::string ret; \
			EVAL(MAP_PAIRS(_INNER_WRAP_DATA, _PLUS_RAW_NEWLINE, \
				__VA_ARGS__)); \
			return ret; \
		} \
	)

#define _INNER_ACCEPT_CHILDREN(type, name) \
	_inner_accept_children(visitor, #name, name)
#define _INNER_DUP(type, name) \
	_inner_dup(ret_ptr, ret_ptr->name, name)

#define CHILDREN(...) \
	IF (HAS_ARGS(__VA_ARGS__)) \
	( \
		EVAL(MAP_PAIRS(_DECL_MEMB_VAR, SEMICOLON, __VA_ARGS__)); \
		\
		virtual inline void accept_children(AstVisitorBase* visitor) \
		{ \
			EVAL(MAP_PAIRS(_INNER_ACCEPT_CHILDREN, SEMICOLON, \
				__VA_ARGS__)); \
		} \
		\
		virtual inline AstNodeBaseUptr dup(AstNodeBase* s_parent) const \
		{ \
			AstNodeBaseUptr ret(new Self(s_parent, fp())); \
			auto ret_ptr = static_cast<Self*>(ret.get()); \
			\
			this->dup_data(ret_ptr); \
			EVAL(MAP_PAIRS(_INNER_DUP, SEMICOLON, __VA_ARGS__)); \
			\
			return ret; \
		} \
	)


#define SHARED_FUNC_CONTENTS_2(name, base_name) \
	inline name() = default; \
	inline name(AstNodeBase* s_parent, const FilePos& s_fp) \
		: base_name(s_parent, s_fp) \
	{ \
		if (_parent != nullptr) \
		{ \
			_level = _parent->level() + static_cast<size_t>(1); \
		} \
		else \
		{ \
			_level = 0; \
		} \
	} \
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(name); \
	virtual inline ~name() = default; \
	virtual inline std::string id() const \
	{ \
		return std::string(#name); \
	} \
	using Self = name;
#define SHARED_CONTENTS(name, base_name) \
	SHARED_FUNC_CONTENTS_2(name, base_name) \
	virtual void accept(AstVisitorBase* visitor) \
	{ \
		auto casted_visitor = static_cast<AST_VISITOR*>(visitor); \
		casted_visitor->visit##name(this); \
	}

#define CONV_ENUM_CASE(type, which) \
	case type::which: \
		return #which;
#define CONV_KIND_CASE(which) \
	CONV_ENUM_CASE(Kind, which)
#define CONV_ENUM_SWITCH(CONV_CASE, ...) \
	switch (to_conv) \
	{ \
	/* -------- */ \
	EVAL(MAP(CONV_CASE, EMPTY, __VA_ARGS__)) \
	default: \
		return "Eek!"; \
	/* -------- */ \
	}

#define BUILD_KIND_OPERATOR_LSHIFT(type) \
	inline std::ostream& operator << (std::ostream& os, \
		type::Kind to_conv) \
	{ \
		os << type::conv_kind(to_conv); \
		return os; \
	}


#endif		// liborangepower_lang_ast_node_base_class_defines_hpp
