#ifndef liborangepower_metaprog_defines_h
#define liborangepower_metaprog_defines_h
//--------
#define PARENS() () // Note space before (), so object-like macro
#define EMPTY()
#define COMMA() ,
#define SEMICOLON() ;
#define PERIOD() .
#define PTR_ACCESS() ->
#define COLON() :
#define ELSE() else

#define ID(arg) arg
#define EAT(...)
#define EXPAND(...) __VA_ARGS__
#define STRINGIFY(x) #x

#define DEFER(m) m EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()

// The `##` operator inhibits macro expansion, so use `CAT()` for this
#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define CHECK_N(x, n, ...) n
#define CHECK(...) CHECK_N(__VA_ARGS__, 0,)
#define PROBE(x) x, 1,

//// Expands to `0`
//CHECK(~)
//// Expands to `1`
//CHECK(PROBE(~))

// `PROBE(~)` expands to `~1`, or `0`

// Note: `CHECK(IS_PAREN_PROBE ())`
#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE(~)
//// Expands to `1`
//IS_PAREN(())
//// Expands to '0'
//IS_PAREN(xxx)


#define IIF(cond) PRIMITIVE_CAT(IIF_, cond)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t

#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define BITAND(x) PRIMITIVE_CAT(BITAND_, x)
#define BITAND_0(y) 0
#define BITAND_1(y) y

#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
#define NOT_0 PROBE(~)

#define BOOL(x) COMPL(NOT(x))
#define IF(c) IIF(BOOL(c))
// Replace `DEFER` with `OBSTRUCT` when inside of `WHEN`'s second set of
// parentheses
#define WHEN(c) IF(c)(EXPAND, EAT)

//#define A_COMMA() a,
// Expands to `a,`
//IF(2)(DEFER(A_COMMA)(), b)

//WHEN(0)(STRINGIFY(when 0))
//IF(0)(STRINGIFY(if 0), EMPTY())
//WHEN(1)(STRINGIFY(when 1))
//IF(1)(STRINGIFY(if 1), EMPTY())
//WHEN(2)(STRINGIFY(when 2))
//IF(2)(STRINGIFY(if 2), EMPTY())

#define FIRST(a, ...) a

#define HAS_ARGS(...) BOOL(FIRST(_END_OF_ARGUMENTS_ __VA_ARGS__)())
#define _END_OF_ARGUMENTS_() 0


// `EVAL` causes `DEFER`red or `OBSTRUCT`ed macro calls with `__VA_ARGS__`
// as an argument to be recurse into the next expansion of the containing
// macro.
#define EVAL(...) EVAL1024(__VA_ARGS__)
#define EVAL1024(...) EVAL512(EVAL512(__VA_ARGS__))
#define EVAL512(...) EVAL256(EVAL256(__VA_ARGS__))
#define EVAL256(...) EVAL128(EVAL128(__VA_ARGS__))
#define EVAL128(...) EVAL64(EVAL64(__VA_ARGS__))
#define EVAL64(...) EVAL32(EVAL32(__VA_ARGS__))
#define EVAL32(...) EVAL16(EVAL16(__VA_ARGS__))
#define EVAL16(...) EVAL8(EVAL8(__VA_ARGS__))
#define EVAL8(...) EVAL4(EVAL4(__VA_ARGS__))
#define EVAL4(...) EVAL2(EVAL2(__VA_ARGS__))
#define EVAL2(...) EVAL1(EVAL1(__VA_ARGS__))
#define EVAL1(...) __VA_ARGS__

// `MAP` is one of the main components of this metaprogramming library.
// This macro is mainly intended to be used as, when called, the argument
// to `EVAL`.

// `__VA_OPT__` makes it so that its arguments expand only when there's at
// least one argument to `__VA_ARGS__`. It is almost the same as
// `WHEN(HAS_ARGS(__VA_ARGS__))`, but uses of `DEFER` are replaced with
// uses of `OBSTRUCT`
#define MAP(m, sep, first, ...) \
	m(first) \
	\
	__VA_OPT__ \
	( \
		DEFER(sep)() \
		DEFER(MAP_INDIRECT)()(m, sep, __VA_ARGS__) \
	)
#define MAP_INDIRECT() MAP
// Here is an alternative version of `MAP` that could have been adapted to
// use with the following macros that are called `MAP_\d` were it being
// used.
//#define MAP(m, sep, first, ...)
//	m(first)
//
//	WHEN(HAS_ARGS(__VA_ARGS__))
//	(
//		OBSTRUCT(sep)()
//		OBSTRUCT(MAP_INDIRECT)()(m, sep, __VA_ARGS__)
//	)

#define MAP_2(m, sep, first, second, ...) \
	m(first, second) \
	\
	__VA_OPT__ \
	( \
		DEFER(sep)() \
		DEFER(MAP_2_INDIRECT)()(m, sep, __VA_ARGS__) \
	)
#define MAP_2_INDIRECT() MAP_2

#define MAP_3(m, sep, first, second, third, ...) \
	m(first, second, third) \
	\
	__VA_OPT__ \
	( \
		DEFER(sep)() \
		DEFER(MAP_3_INDIRECT)()(m, sep, __VA_ARGS__) \
	)
#define MAP_3_INDIRECT() MAP_3

#define MAP_4(m, sep, first, second, third, fourth, ...) \
	m(first, second, third, fourth) \
	\
	__VA_OPT__ \
	( \
		DEFER(sep)() \
		DEFER(MAP_4_INDIRECT)()(m, sep, __VA_ARGS__) \
	)
#define MAP_4_INDIRECT() MAP_4

//#define DEF_VAR(type, name) type name
//EVAL(MAP_2(DEF_VAR, SEMICOLON,
//	int, x,
//	Vec2<int>, y,
//	std::string, z)
//)

// There are two ways to define `LIST` for use with `MAP` or
// `MAP_INDIRECT`.
//#define LIST(X, sep) EVAL(MAP(X, sep, a, b, c, d))
//
// The workaround is to use `DEFER(MAP_INDIRECT)()` instead of `MAP`
//#define LIST a, b, c, d
//EVAL(DEFER(MAP_INDIRECT)()(STRINGIFY, SEMICOLON, LIST))

//#define PLUS_3(x) ((x) + 3)

//EVAL(MAP(STRINGIFY, SEMICOLON, a, b, c, d))

//LIST(STRINGIFY, ELSE)

//#define A() 123
//A()
//// Expands to `A ()` because it requires one more scan to fully expand
//DEFER(A)()
//// Expands to `123`, because the `EVAL` macro forces another scan
//EVAL(DEFER(A)())
//--------
#define CX_WHEN(cx_cond) WHEN(cx_cond)(constexpr)
//--------
#endif		// liborangepower_metaprog_defines_h
