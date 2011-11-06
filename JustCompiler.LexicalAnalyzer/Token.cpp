#include "Token.h"

Token::~Token() {
    //do nothing
}

Token::Token(const TokenTag::Enum tag, const int lineNum, const int charNum) {
    this->tag = tag;
    this->lineNum = lineNum;
    this->charNum = charNum;
}

TokenTag::Enum Token::GetTag() const {
    return tag;
}

int Token::GetLineNum() const {
    return lineNum;
}

int Token::GetCharNum() const {
    return charNum;
}

bool Token::operator== (const Token& right) const {
    return this->GetTag() == right.GetTag();
}