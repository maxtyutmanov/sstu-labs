#pragma once

#include "Token.h"
#include <string>
using std::wstring;

class Identifier : public Token {
public:
    explicit Identifier(const wstring& name);

    wstring GetName() const;

    virtual bool operator== (const Token& right) const;
private:
    wstring name;
};