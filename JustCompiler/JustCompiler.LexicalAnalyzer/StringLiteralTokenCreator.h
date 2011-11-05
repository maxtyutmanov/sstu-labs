#pragma once

#include "TokenCreator.h"

class StringLiteralTokenCreator : public TokenCreator {
public:
    virtual bool TryCreateToken(
        const wstring& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error);
};