#ifndef DEFAULT_TOKEN_CREATOR_H
#define DEFAULT_TOKEN_CREATOR_H

#include <TokenCreator.h>
#include "TokenTag.h"
#include <string>
using std::string;

namespace JustServer {
namespace HttpGrammar {

    class HttpTextTokenCreator : public TokenCreator {
    public:
        HttpTextTokenCreator(TokenTag::Enum tag);

        virtual bool TryCreateToken(
            const string& lexeme, 
            int lineNum, 
            int charNum, 
            Token** token, 
            LexicalError** error);
    private:
        TokenTag::Enum tag;
    };

}
}

#endif