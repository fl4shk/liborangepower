#ifndef liborangepower_mp11_defines_hpp
#define liborangepower_mp11_defines_hpp


// These are things intended for use with Boost's MP11 library.
// See `testing/mp11_tests/...` for some examples on how to use these
// macros.

//--------
// All classes of the hierarchy_list use these
#define MP11_DECLARE_IDENT_STATIC_VARS \
	static const size_t ident_num; \
	static const char* ident_name;

#define MP11_DEFINE_IDENT_STATIC_VARS(some_class, hierarchy_list) \
	static_assert(mp_find<hierarchy_list, some_class>::value \
		!= mp_size<hierarchy_list>::value, "Missing type from list!"); \
	const size_t some_class::ident_num \
		= mp_find<hierarchy_list, some_class>::value; \
	const char* some_class::ident_name = #some_class;
//--------


//--------
// Base class stuff
#define MP11_MAKE_BASE_CLASS_ESSENTIAL_INSIDES \
public:		/* static variables */ \
	MP11_DECLARE_IDENT_STATIC_VARS \
	\
	static const size_t hierarchy_size; \


#define MP11_MAKE_BASE_CLASS_ARR_GETTER_INSIDES \
private:		/* static variables */ \
	static size_t _ret_for_all_ident_num_arr[]; \
	static const char* _ret_for_all_ident_name_arr[]; \
	\
public:		/* static functions */ \
	static constexpr size_t* all_ident_num_arr(); \
	static constexpr const char** all_ident_name_arr(); \


#define MP11_MAKE_BASE_CLASS_INSIDES \
	MP11_MAKE_BASE_CLASS_ESSENTIAL_INSIDES \
	MP11_MAKE_BASE_CLASS_ARR_GETTER_INSIDES


#define MP11_MAKE_BASE_CLASS_ESSENTIAL_OUTSIDES(base_class, \
	hierarchy_list) \
static_assert(mp_is_set<hierarchy_list>::value == true, \
	"Hierarchy list must NOT contain duplicate types!"); \
\
MP11_DEFINE_IDENT_STATIC_VARS(base_class, hierarchy_list) \
\
size_t base_class::_ret_for_all_ident_num_arr \
	[mp_size<hierarchy_list>::value]; \
const char* base_class::_ret_for_all_ident_name_arr \
	[mp_size<hierarchy_list>::value]; \
\
const size_t base_class::hierarchy_size = mp_size<hierarchy_list>::value; \


#define MP11_MAKE_BASE_CLASS_ARR_GETTER_OUTSIDES(some_class, \
	hierarchy_list) \
constexpr size_t* some_class::all_ident_num_arr() \
{ \
	mp_for_each<hierarchy_list>([](auto iter) -> void \
		{ \
			_ret_for_all_ident_num_arr[decltype(iter)::ident_num] \
				= decltype(iter)::ident_num; \
		}); \
	\
	return _ret_for_all_ident_num_arr; \
} \
\
constexpr const char** some_class::all_ident_name_arr() \
{ \
	mp_for_each<hierarchy_list>([](auto iter) -> void \
		{ \
			_ret_for_all_ident_name_arr[decltype(iter)::ident_num] \
				= decltype(iter)::ident_name; \
		}); \
	\
	return _ret_for_all_ident_name_arr; \
}
//--------

#endif		// liborangepower_mp11_defines_hpp
