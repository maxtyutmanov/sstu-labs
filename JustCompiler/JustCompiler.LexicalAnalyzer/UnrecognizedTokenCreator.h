#pragma once

#include "TokenCreator.h"

//TODO: consider deleting of this class

class UnrecognizedTokenCreator : public TokenCreator {
public:
    virtual bool TryCreateToken(
        const wstring& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error);
};