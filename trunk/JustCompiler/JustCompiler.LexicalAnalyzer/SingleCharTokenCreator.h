#pragma once

#include "Global.h"
#include "TokenCreator.h"
#include "LexerSettings.h"

class SingleCharTokenCreator : public TokenCreator {
public:
    SingleCharTokenCreator(const LexerSettings& lexerSettings);

    virtual bool TryCreateToken(
        const string_type& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error);

private:
    LexerSettings settings;
};