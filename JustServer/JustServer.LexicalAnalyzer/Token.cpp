#include "Token.h"

Token::~Token() {
    //do nothing
}

Token::Token(const int tag, const int lineNum, const int charNum) {
    this->tag = tag;
    this->lineNum = lineNum;
    this->charNum = charNum;
}

Token::Token(const int tag) {
    this->tag = tag;
    this->lineNum = -1;
    this->charNum = -1;
}

int Token::GetTag() const {
    return tag;
}

int Token::GetLineNum() const {
    return lineNum;
}

void Token::SetLineNum(const int lineNum) {
    this->lineNum = lineNum;
}

int Token::GetCharNum() const {
    return charNum;
}

void Token::SetCharNum(const int charNum) {
    this->charNum = charNum;
}

bool Token::operator== (const Token& right) const {
    return this->GetTag() == right.GetTag();
}