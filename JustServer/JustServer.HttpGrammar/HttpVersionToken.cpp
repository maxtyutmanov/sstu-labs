#include "HttpVersionToken.h"
#include "TokenTag.h"

using JustServer::HttpGrammar::TokenTag;

namespace JustServer {
namespace HttpGrammar {
namespace Tokens {
    HttpVersionToken::HttpVersionToken(unsigned int major, unsigned int minor) 
        : Token(TokenTag::HttpVersion), major(major), minor(minor) {}

    unsigned int HttpVersionToken::GetMajor() const {
        return major;
    }

    unsigned int HttpVersionToken::GetMinor() const {
        return minor;
    }
}
}
}