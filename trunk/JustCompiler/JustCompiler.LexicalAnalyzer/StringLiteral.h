#pragma once

#include "Token.h"
#include <string>
using std::wstring;

class StringLiteral : public Token {
public:
    StringLiteral(const wstring& text);

    wstring GetText() const;

    virtual bool operator== (const Token& right) const;
private:
    wstring text;
};