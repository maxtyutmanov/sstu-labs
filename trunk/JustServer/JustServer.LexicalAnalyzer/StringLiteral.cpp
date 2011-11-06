#include "StringLiteral.h"

StringLiteral::StringLiteral(const string_type& text, const int lineNum, const int charNum)
    :Token(TokenTag::StringLiteral, lineNum, charNum) {

    this->text = text;
}

string_type StringLiteral::GetText() const {
    return text;
}

bool StringLiteral::operator== (const Token& right) const {
    if (right.GetTag() != TokenTag::StringLiteral) {
        return false;
    }

    const StringLiteral* rightStringLiteral = dynamic_cast<const StringLiteral*>(&right);

    return this->text == rightStringLiteral->text;
}