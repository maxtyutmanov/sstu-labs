#pragma once

#include "Global.h"
#include <memory>
#include "Token.h"
#include "LexicalError.h"
using std::auto_ptr;

class TokenCreator {
public:
    virtual bool TryCreateToken(
        const string_type& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error) = 0;
};