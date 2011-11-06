#include "HttpVerb.h"
#include "TokenTag.h"

namespace JustServer {
namespace HttpGrammar {
namespace Tokens {

    HttpVerb::HttpVerb(const string& verb)
        : Token(TokenTag::HttpVerb), verb(verb) {}

    string HttpVerb::VerbName() const {
        return verb;
    }

}
}
}