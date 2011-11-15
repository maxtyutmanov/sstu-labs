#ifndef HTTP_TEXT_TOKEN_H
#define HTTP_TEXT_TOKEN_H

#include <Token.h>
#include "TokenTag.h"
#include <string>
using std::string;

namespace JustServer {
namespace HttpGrammar {
namespace Tokens {

    class HttpTextToken : public Token {
    public:
        HttpTextToken(TokenTag::Enum tag, const string& text);

        string GetText() const;
    private:
        string text;
    };

}
}
}

#endif