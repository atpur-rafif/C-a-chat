#define APPEND_MACRO_1(a, b) a ## b
#define APPEND_MACRO(a, b) APPEND_MACRO_1(a, b)
#define FUN(name) APPEND_MACRO(name ## _, TYPE)