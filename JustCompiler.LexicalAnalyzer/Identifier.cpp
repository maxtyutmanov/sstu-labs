#include "Identifier.h"

Identifier::Identifier(const wstring& name)
    : Token(TokenTag::Identifier) {

    this->name = name;
}

wstring Identifier::GetName() const {
    return name;
}

bool Identifier::operator== (const Token& right) const {
    if (right.GetTag() != TokenTag::Identifier) {
        return false;
    }

    //TODO: can be optimized

    const Identifier *rightIdentifier = dynamic_cast<const Identifier *>(&right);

    //TODO: check is needed. Or not?

    return this->name == rightIdentifier->name;
}