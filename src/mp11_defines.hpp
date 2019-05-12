#ifndef liborangepower_mp11_defines_hpp
#define liborangepower_mp11_defines_hpp


#define MP11_DECLARE_IDENT_GETTERS \
	static const size_t ident_num; \
	static const char* ident_name;

#define MP11_MAKE_IDENT_GETTERS(hierarchy, some_class) \
	static_assert(mp_find<hierarchy, some_class>::value \
		!= mp_size<hierarchy>::value, \
		"missing type from list!"); \
	const size_t some_class::ident_num \
		= mp_find<hierarchy, some_class>::value; \
	const char* some_class::ident_name = #some_class;


#define MP11_MAKE_BASE_CLASS_INSIDES(base_class, some_num) \
private:		/* static variables */ \
	static const size_t _ret_for_all_ident_nums_arr[]; \
	static const char* _ret_for_all_ident_names_arr[]; \
	\
public:		/* static variables */ \
	MP11_DECLARE_IDENT_GETTERS \
	\
	static const size_t some_num; \
	\
public:		/* static functions */ \
	static constexpr size_t* all_ident_nums_arr(); \
	static constexpr const char** all_ident_names_arr(); \


#define MP11_MAKE_BASE_CLASS_OUTSIDES(base_class, some_num, hierarchy) \
static_assert(mp_is_set<hierarchy>::value == true, \
	#hierarchy " must NOT contain duplicate types!"); \
\
MP11_MAKE_IDENT_GETTERS(base_class, hierarchy) \
\
const size_t base_class::_ret_for_all_ident_nums_arr \
	[mp_size<hierarchy>::value]; \
const char* base_class::_ret_for_all_ident_names_arr \
	[mp_size<hierarchy>::value]; \
\
const size_t base_class::some_num = mp_size<hierarchy>::value; \


#define MP11_MAKE_ARR_GETTERS(some_class, hierarchy) \
constexpr size_t* some_class::all_ident_nums_arr() \
{ \
	mp_for_each<hierarchy>([](auto iter) -> void \
		{ \
			_ret_for_all_ident_nums_arr[decltype(iter)::ident_num] \
				= decltype(iter)::ident_num; \
		}); \
	\
	return _ret_for_all_ident_nums_arr; \
} \
\
constexpr const char** some_class::all_ident_names_arr() \
{ \
	mp_for_each<hierarchy>([](auto iter) -> void \
		{ \
			_ret_for_all_ident_names_arr[decltype(iter)::ident_num] \
				= decltype(iter)::ident_name; \
		}); \
	\
	return _ret_for_all_ident_names_arr; \
}

#endif		// liborangepower_mp11_defines_hpp
