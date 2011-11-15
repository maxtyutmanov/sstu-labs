#include "RequestBodyTokenCreator.h"
#include "RequestBody.h"

using JustServer::HttpGrammar::Tokens::RequestBody;

namespace JustServer {
namespace HttpGrammar {

    bool RequestBodyTokenCreator::TryCreateToken(
        const string_type& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error) {

        *token = new RequestBody(lexeme);
        return true;
    }

}
}