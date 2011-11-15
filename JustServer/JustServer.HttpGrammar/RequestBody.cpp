#include "RequestBody.h"
#include "TokenTag.h"

using JustServer::HttpGrammar::TokenTag;

namespace JustServer {
namespace HttpGrammar {
namespace Tokens {

    RequestBody::RequestBody(const string& contents)
        : Token(TokenTag::Body) {

        this->contents = contents;
    }

    string RequestBody::GetContents() const {
        return contents;
    }
}
}
}