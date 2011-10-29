#pragma once

#include "TokenTag.h"
#include <string>
#include <map>
#include <set>
using std::map;
using std::wstring;
using std::set;

typedef map<wstring, TokenTag::Enum> LexemesDictionary;
typedef map<wchar_t, TokenTag::Enum> OneCharLexemesDictionary;

class LexerSettings {
public:
    LexerSettings();

    LexerSettings(
        const LexemesDictionary& keyWords, 
        const LexemesDictionary& standardFunctions,
        const OneCharLexemesDictionary& singleCharLexemes);

    bool GetKeyword(const wstring& lexeme, TokenTag::Enum* keywordTag) const;
    bool GetStandardFunction(const wstring& lexeme, TokenTag::Enum* standardFunctionTag) const;
    bool GetSingleCharLexeme(const wchar_t ch, TokenTag::Enum* tokenTag) const;

    bool GetKeyword(const TokenTag::Enum keywordTag, wstring* lexeme) const;
    bool GetStandardFunction(const TokenTag::Enum standardFunctionTag, wstring* lexeme) const;
    bool GetSingleCharLexeme(const TokenTag::Enum ch, wchar_t* lexeme) const;

    int GetMaxIdentifierLength() const;
private:
    LexemesDictionary keyWords;
    LexemesDictionary standardFunctions;
    OneCharLexemesDictionary oneCharLexemes;
};