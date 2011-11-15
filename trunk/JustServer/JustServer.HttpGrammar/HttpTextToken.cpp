#include "HttpTextToken.h"

namespace JustServer {
namespace HttpGrammar {
namespace Tokens {

    HttpTextToken::HttpTextToken(TokenTag::Enum tag, const string& text)
        : Token(tag), text(text) {}

    string HttpTextToken::GetText() const {
        return text;
    }
}
}
}