#pragma once

#include "Global.h"
#include <map>
#include <set>
using std::map;
using std::set;

typedef map<string_type, TokenTag::Enum> LexemesDictionary;
typedef map<char_type, TokenTag::Enum> OneCharLexemesDictionary;

const int DEFAULT_MAX_IDENTIFIER_LENGTH = 14;

class LexerSettings {
public:
    LexerSettings();

    LexerSettings(
        const LexemesDictionary& keyWords, 
        const LexemesDictionary& standardFunctions,
        const OneCharLexemesDictionary& singleCharLexemes);

    bool GetKeyword(const string_type& lexeme, TokenTag::Enum* keywordTag) const;
    bool GetStandardFunction(const string_type& lexeme, TokenTag::Enum* standardFunctionTag) const;
    bool GetSingleCharLexeme(const char_type ch, TokenTag::Enum* tokenTag) const;

    bool GetKeyword(const TokenTag::Enum keywordTag, string_type* lexeme) const;
    bool GetStandardFunction(const TokenTag::Enum standardFunctionTag, string_type* lexeme) const;
    bool GetSingleCharLexeme(const TokenTag::Enum ch, char_type* lexeme) const;

    int GetMaxIdentifierLength() const;
    void SetMaxIdentifierLength(int value);
private:
    LexemesDictionary keyWords;
    LexemesDictionary standardFunctions;
    OneCharLexemesDictionary oneCharLexemes;

    int maxIdentifierLength;
};