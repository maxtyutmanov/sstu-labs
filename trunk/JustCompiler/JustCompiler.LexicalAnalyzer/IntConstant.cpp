#include "IntConstant.h"

IntConstant::IntConstant(const int value, const int lineNum, const int charNum) 
    :Token(TokenTag::IntConstant, lineNum, charNum) {

    this->value = value;
}

int IntConstant::GetValue() const {
    return value;
}

bool IntConstant::operator== (const Token& right) const {
    if (right.GetTag() != TokenTag::IntConstant) {
        return false;
    }

    const IntConstant* rightIntConstant = dynamic_cast<const IntConstant*>(&right);

    return this->value == rightIntConstant->value;
}