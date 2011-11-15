#ifndef HEADER_TOKEN_CREATOR_H
#define HEADER_TOKEN_CREATOR_H

#include <TokenCreator.h>
#include <string>
using std::string;

namespace JustServer {
namespace HttpGrammar {

    class HeaderTokenCreator : public TokenCreator {
    public:
        virtual bool TryCreateToken(
            const string& lexeme, 
            int lineNum, 
            int charNum, 
            Token** token, 
            LexicalError** error);
    };

}
}

#endif