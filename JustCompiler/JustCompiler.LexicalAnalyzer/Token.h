#pragma once

#include "TokenTag.h"

class Token {
public:
    Token();
    virtual ~Token();
    Token(const TokenTag::Enum tag);

    TokenTag::Enum GetTag() const;

    virtual bool operator== (const Token& right) const;
protected:
    TokenTag::Enum tag;
};