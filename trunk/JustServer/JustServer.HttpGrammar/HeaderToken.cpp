#include "HeaderToken.h"
#include "TokenTag.h"

using JustServer::HttpGrammar::TokenTag;

namespace JustServer {
namespace HttpGrammar {
namespace Tokens {

    HeaderToken::HeaderToken(const string& name, const string& value) 
        : Token(TokenTag::Header) {

        this->name = name;
        this->value = value;
    }

    string HeaderToken::GetName() const {
        return name;
    }

    string HeaderToken::GetValue() const {
        return value;
    }
}
}
}