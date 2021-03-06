#pragma once

#include "Global.h"
#include "TokenCreator.h"

class StringLiteralTokenCreator : public TokenCreator {
public:
    virtual bool TryCreateToken(
        const string_type& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error);
};