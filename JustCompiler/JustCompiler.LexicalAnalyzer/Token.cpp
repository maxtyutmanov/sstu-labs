#include "Token.h"

Token::Token() {
    //TODO: WTF?
    tag = TokenTag::Space;
}

Token::~Token() {
    //do nothing
}

Token::Token(const TokenTag::Enum tag) {
    this->tag = tag;
}

TokenTag::Enum Token::GetTag() const {
    return tag;
}

bool Token::operator== (const Token& right) const {
    return this->GetTag() == right.GetTag();
}