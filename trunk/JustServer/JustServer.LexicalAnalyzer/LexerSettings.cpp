#include "LexerSettings.h"
#include <assert.h>

LexerSettings::LexerSettings() {
    maxIdentifierLength = -1;
}

LexerSettings::LexerSettings(
    const LexemesDictionary& keyWords, 
    const LexemesDictionary& standardFunctions,
    const OneCharLexemesDictionary& oneCharLexemes) {

    this->keyWords = keyWords;
    this->standardFunctions = standardFunctions;
    this->oneCharLexemes = oneCharLexemes;

    maxIdentifierLength = -1;
}

//TODO: DRY

bool LexerSettings::GetKeyword(const string_type& lexeme, TokenTag::Enum* keyWord) const {
    LexemesDictionary::const_iterator found = keyWords.find(lexeme);

    if (found != keyWords.end()) {
        *keyWord = found->second;
        return true;
    }
    else {
        return false;
    }
}

bool LexerSettings::GetStandardFunction(const string_type& lexeme, TokenTag::Enum* standardFunction) const {
    LexemesDictionary::const_iterator found = standardFunctions.find(lexeme);

    if (found != standardFunctions.end()) {
        *standardFunction = found->second;
        return true;
    }
    else {
        return false;
    }
}

bool LexerSettings::GetSingleCharLexeme(const char_type ch, TokenTag::Enum* tokenTag) const {
    OneCharLexemesDictionary::const_iterator found = oneCharLexemes.find(ch);

    if (found != oneCharLexemes.end()) {
        *tokenTag = found->second;
        return true;
    }
    else {
        return false;
    }
}

bool LexerSettings::GetKeyword(const TokenTag::Enum keywordTag, string_type* lexeme) const {
    LexemesDictionary::const_iterator kwIt;

    for (kwIt = keyWords.begin(); kwIt != keyWords.end(); ++kwIt) {
        if (kwIt->second == keywordTag) {
            *lexeme = kwIt->first;
            return true;
        }
    }

    return false;
}

bool LexerSettings::GetStandardFunction(const TokenTag::Enum standardFunctionTag, string_type* lexeme) const {
    LexemesDictionary::const_iterator sfIt;

    for (sfIt = standardFunctions.begin(); sfIt != standardFunctions.end(); ++sfIt) {
        if (sfIt->second == standardFunctionTag) {
            *lexeme = sfIt->first;
            return true;
        }
    }

    return false;
}

bool LexerSettings::GetSingleCharLexeme(const TokenTag::Enum singleCharTag, char_type* lexeme) const {
    OneCharLexemesDictionary::const_iterator scIt;

    for (scIt = oneCharLexemes.begin(); scIt != oneCharLexemes.end(); ++scIt) {
        if (scIt->second == singleCharTag) {
            *lexeme = scIt->first;
            return true;
        }
    }

    return false;
}

int LexerSettings::GetMaxIdentifierLength() const {
    if (maxIdentifierLength == -1) {
        return DEFAULT_MAX_IDENTIFIER_LENGTH;
    }
    else {
        return maxIdentifierLength;
    }
}

void LexerSettings::SetMaxIdentifierLength(int value) {
    assert(value > 0);

    maxIdentifierLength = value;
}