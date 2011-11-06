#pragma once

#include "TokenCreator.h"
#include "LexerSettings.h"

//Creates tokens for keywords, standard functions and identifiers
class WordTokenCreator : public TokenCreator {
public:
    WordTokenCreator(const LexerSettings& lexerSettings);

    virtual bool TryCreateToken(
        const wstring& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error);

private:
    LexerSettings settings;

    bool CheckCharset(const wstring& lexeme);
};