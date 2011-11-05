#pragma once

#include "Token.h"
#include <string>
using std::wstring;

class Identifier : public Token {
public:
    Identifier(const wstring& name, const int lineNum, const int charNum);

    wstring GetName() const;

    virtual bool operator== (const Token& right) const;
private:
    wstring name;
};