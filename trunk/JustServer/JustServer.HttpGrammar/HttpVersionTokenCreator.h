#ifndef HTTP_VERSION_TOKEN_CREATOR
#define HTTP_VERSION_TOKEN_CREATOR

#include <TokenCreator.h>
#include <vector>
#include <string>
using std::vector;
using std::string;

namespace JustServer {
namespace HttpGrammar {

    class HttpVersionTokenCreator : public TokenCreator {
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