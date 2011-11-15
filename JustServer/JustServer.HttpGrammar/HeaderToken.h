#ifndef HEADER_TOKEN_H
#define HEADER_TOKEN_H

#include <Token.h>
#include <string>
using std::string;

namespace JustServer {
namespace HttpGrammar {
namespace Tokens {

    class HeaderToken : public Token {
    public:
        HeaderToken(const string& name, const string& value);

        string GetName() const;
        string GetValue() const;
    private:
        string name;
        string value;
    };

}
}
}

#endif