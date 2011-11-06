#pragma once

#include <string>
#include <memory>
#include "Token.h"
#include "LexicalError.h"
using std::wstring;
using std::auto_ptr;

class TokenCreator {
public:
    virtual bool TryCreateToken(
        const wstring& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error) = 0;
};