#pragma once

#include <string>
#include <iostream>

#ifdef USE_WIDE_CHARS

typedef wchar_t char_type;

#define LITERAL(quote) L##quote

#else

typedef char char_type;

#define LITERAL(quote) quote

#endif

typedef std::basic_string<char_type> string_type;
typedef std::basic_istream<char_type> input_stream_type;
typedef std::basic_ostream<char_type> output_stream_type;