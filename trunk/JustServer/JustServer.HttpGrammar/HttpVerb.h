#ifndef HTTP_VERB_H
#define HTTP_VERB_H

#include <Token.h>
#include <string>
using std::string;

namespace JustServer {
namespace HttpGrammar {
namespace Tokens {

    class HttpVerb : public Token {
    public:
        HttpVerb(const string& verb);

        string VerbName() const;
    private:
        string verb;
    };

}
}
}

#endif