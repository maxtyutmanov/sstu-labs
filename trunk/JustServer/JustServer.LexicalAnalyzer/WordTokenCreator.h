#pragma once

#include "Global.h"
#include "TokenCreator.h"
#include "LexerSettings.h"
#include "CharValidationRule.h"

//Creates tokens for keywords, standard functions and identifiers
class WordTokenCreator : public TokenCreator {
public:
    WordTokenCreator(const LexerSettings& lexerSettings, CharValidationRule charValidationRule);

    virtual bool TryCreateToken(
        const string_type& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error);

private:
    LexerSettings settings;
    CharValidationRule charValidationRule;

    bool CheckCharset(const string_type& lexeme);
};