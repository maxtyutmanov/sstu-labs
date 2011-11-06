#include <boost/test/auto_unit_test.hpp>

#include "LexerInputBuffer.h"
#include <sstream>
#include <string>
using std::wistringstream;
using std::wstring;

BOOST_AUTO_TEST_CASE( LexerInputBuffer_GetLineNumber ) {
    wstring source = L"abc\ndef\nabc";
    wistringstream sourceStream(source);

    LexerInputBuffer buffer(sourceStream);

    wstring str1;

    for (int i = 0; i < 3; ++i) {
        str1.push_back(buffer.Get());
    }

    BOOST_CHECK(str1 == L"abc");
    BOOST_CHECK(buffer.GetLineNumber() == 1);
    BOOST_CHECK(buffer.GetCharacterNumber() == 4);

    BOOST_CHECK(buffer.Get() == L'\n');
    BOOST_CHECK(buffer.GetLineNumber() == 2);
    BOOST_CHECK(buffer.GetCharacterNumber() == 1);

    buffer.Unget();

    BOOST_CHECK(buffer.GetLineNumber() == 1);
    BOOST_CHECK(buffer.GetCharacterNumber() == 4);

    BOOST_CHECK(buffer.Get() == L'\n');
    BOOST_CHECK(buffer.GetLineNumber() == 2);
    BOOST_CHECK(buffer.GetCharacterNumber() == 1);

    wstring str2;

    for (int i = 0; i < 3; ++i) {
        str2.push_back(buffer.Get());
    }

    BOOST_CHECK(str2 == L"def");
}