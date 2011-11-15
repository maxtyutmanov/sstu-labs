#ifndef REQUEST_BODY_TOKEN_CREATOR_H
#define REQUEST_BODY_TOKEN_CREATOR_H

#include <TokenCreator.h>

namespace JustServer {
namespace HttpGrammar {

    class RequestBodyTokenCreator : public TokenCreator {
    public:
        virtual bool TryCreateToken(
            const string_type& lexeme, 
            int lineNum, 
            int charNum, 
            Token** token, 
            LexicalError** error);
    };

}
}

#endif