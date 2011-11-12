#include "HttpVerbTokenCreator.h"
#include "HttpVerb.h"

using JustServer::HttpGrammar::Tokens::HttpVerb;

namespace JustServer {
namespace HttpGrammar {

    HttpVerbTokenCreator::HttpVerbTokenCreator(const vector<string>& allowedVerbs) 
        : allowedVerbs(allowedVerbs) {
    }

    bool HttpVerbTokenCreator::TryCreateToken(
        const string& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error) {

        for (size_t i = 0; i < allowedVerbs.size(); ++i) {
            if (lexeme == allowedVerbs[i]) {
                *token = new HttpVerb(lexeme);
                return true;
            }
        }

        *error = new LexicalError(lineNum, charNum, -1);
        return false;
    }

}
}