#pragma once

#include "Token.h"

class IntConstant : public Token {
public:
    IntConstant(const int value, const int lineNum, const int charNum);

    int GetValue() const;

    virtual bool operator== (const Token& right) const;
private:
    int value;
};