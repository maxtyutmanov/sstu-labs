#include "HttpTextTokenCreator.h"
#include "HttpTextToken.h"

using namespace JustServer::HttpGrammar::Tokens;

namespace JustServer {
namespace HttpGrammar {

    HttpTextTokenCreator::HttpTextTokenCreator(TokenTag::Enum tag)
        : tag(tag) { }

    bool HttpTextTokenCreator::TryCreateToken(
        const string& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error) {

        *token = new HttpTextToken(tag, lexeme);
        return true;
    }
}
}