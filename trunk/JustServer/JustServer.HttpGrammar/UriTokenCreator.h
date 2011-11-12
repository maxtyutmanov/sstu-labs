#ifndef URI_TOKEN_CREATOR
#define URI_TOKEN_CREATOR

#include <TokenCreator.h>
#include <NameValuePair.h>
#include <string>
#include <vector>
using std::string;
using std::vector;
using namespace JustServer::Utility;

namespace JustServer {
namespace HttpGrammar {

    class UriTokenCreator : public TokenCreator {
    public:
        virtual bool TryCreateToken(
            const string& lexeme, 
            int lineNum, 
            int charNum, 
            Token** token, 
            LexicalError** error);
    private: 
        bool TryParseHostAndPort(
            const string& hostAndPortStr,
            string& hostStr,
            bool& portIsSpecified,
            unsigned short& port);

        bool TryParseQueryString(
            const string& query,
            vector<NameValuePair>& params);
    };

}
}

#endif