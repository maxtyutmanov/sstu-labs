#pragma once

#include "TokenCreator.h"
#include "LexerSettings.h"

class SingleCharTokenCreator : public TokenCreator {
public:
    SingleCharTokenCreator(const LexerSettings& lexerSettings);

    virtual bool TryCreateToken(
        const wstring& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error);

private:
    LexerSettings settings;
};