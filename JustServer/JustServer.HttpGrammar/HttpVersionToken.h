#ifndef HTTP_VERSION_TOKEN_H
#define HTTP_VERSION_TOKEN_H

#include <Token.h>
#include <string>
using std::string;

namespace JustServer {
namespace HttpGrammar {
namespace Tokens {

    class HttpVersionToken : public Token {
    public:
        HttpVersionToken(unsigned int major, unsigned int minor);

        unsigned int GetMajor() const;
        unsigned int GetMinor() const;
    private:
        unsigned int major;
        unsigned int minor;
    };

}
}
}

#endif