#pragma once

#include "TokenTag.h"

class Token {
public:
    Token(const TokenTag::Enum tag, const int lineNum, const int charNum);
    virtual ~Token();

    TokenTag::Enum GetTag() const;
    int GetLineNum() const;
    int GetCharNum() const;

    virtual bool operator== (const Token& right) const;
protected:
    TokenTag::Enum tag;
    int lineNum;
    int charNum;
};