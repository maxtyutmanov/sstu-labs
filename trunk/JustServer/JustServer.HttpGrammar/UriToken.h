#ifndef URL_TOKEN_H
#define URL_TOKEN_H

#include <Token.h>
#include <NameValuePair.h>
#include <string>
#include <vector>
using std::string;
using std::vector;
using namespace JustServer::Utility;

namespace JustServer {
namespace HttpGrammar {
namespace Tokens {

    class UriToken : public Token {
    public:
        static const unsigned short UnspecifiedPort = 0;

        UriToken(
            const string& scheme, 
            const string& host, 
            const unsigned short port, 
            const string& absolutePath, 
            const vector<NameValuePair>& query);

        UriToken(
            const string& scheme,
            const string& host,
            const string& absolutePath,
            const vector<NameValuePair>& query);

        string GetScheme() const;
        string GetHost() const;
        unsigned short GetPort() const;
        string GetAbsolutePath() const;
        vector<NameValuePair> GetQuery() const;
    private:
        string scheme;
        string host;
        unsigned short port;
        string absolutePath;
        vector<NameValuePair> query;
    };

}
}
}

#endif