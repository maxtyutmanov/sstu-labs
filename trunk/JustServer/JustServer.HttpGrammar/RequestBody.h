#ifndef REQUEST_BODY_H
#define REQUEST_BODY_H

#include <Token.h>
#include <string>
using std::string;

namespace JustServer {
namespace HttpGrammar {
namespace Tokens {

    class RequestBody : public Token {
    public:
        RequestBody(const string& contents);

        string GetContents() const;
    private:
        string contents;
    };

}
}
}

#endif