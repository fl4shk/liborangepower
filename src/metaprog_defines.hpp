#ifndef liborangepower_metaprog_defines_h
#define liborangepower_metaprog_defines_h

#define PASS(...) __VA_ARGS__
#define EMPTY()
#define COMMA() ,
#define SEMICOLON() ;
#define PERIOD() .
#define PTR_ACCESS() ->
#define COLON() :
#define ELSE() else

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

#define DEFER1(m) m EMPTY()

#define MAP(m, sep, first, ...) \
	m(first) \
	\
	__VA_OPT__ \
	( \
		DEFER1(sep)() \
		DEFER1(_MAP)()(m, sep, __VA_ARGS__) \
	)
#define _MAP() MAP

#define MAP_PAIRS(m, sep, first, second, ...) \
	m(first, second) \
	\
	__VA_OPT__ \
	( \
		DEFER1(sep)() \
		DEFER1(_MAP_PAIRS)()(m, sep, __VA_ARGS__) \
	)
#define _MAP_PAIRS() MAP_PAIRS

#define MAP_TRIPLES(m, sep, first, second, third, ...) \
	m(first, second, third) \
	\
	__VA_OPT__ \
	( \
		DEFER1(sep)() \
		DEFER1(_MAP_TRIPLES)()(m, sep, __VA_ARGS__) \
	)
#define _MAP_TRIPLES() MAP_TRIPLES

#define MAP_QUADS(m, sep, first, second, third, fourth, ...) \
	m(first, second, third, fourth) \
	\
	__VA_OPT__ \
	( \
		DEFER1(sep)() \
		DEFER1(_MAP_QUADS)()(m, sep, __VA_ARGS__) \
	)
#define _MAP_QUADS() MAP_QUADS


#endif		// liborangepower_metaprog_defines_h
