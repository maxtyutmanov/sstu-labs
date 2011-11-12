#ifndef HTTP_VERB_TOKEN_CREATOR_H
#define HTTP_VERB_TOKEN_CREATOR_H

#include <TokenCreator.h>
#include <vector>
#include <string>
using std::vector;
using std::string;

namespace JustServer {
namespace HttpGrammar {

    class HttpVerbTokenCreator : public TokenCreator {
    public:
        HttpVerbTokenCreator(const vector<string>& allowedVerbs);

        virtual bool TryCreateToken(
            const string_type& lexeme, 
            int lineNum, 
            int charNum, 
            Token** token, 
            LexicalError** error);
    private:
        vector<string> allowedVerbs;
    };

}
}

#endif