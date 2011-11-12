#include "UriToken.h"
#include "TokenTag.h"

namespace JustServer {
namespace HttpGrammar {
namespace Tokens {

    UriToken::UriToken(
        const string& scheme, 
        const string& host, 
        const unsigned short port, 
        const string& absolutePath, 
        const vector<NameValuePair>& query) 
        : Token(TokenTag::Uri) {

        this->scheme = scheme;
        this->host = host;
        this->port = port;
        this->absolutePath = absolutePath;
        this->query = query;
    }

    UriToken::UriToken(
        const string& scheme, 
        const string& host, 
        const string& absolutePath, 
        const vector<NameValuePair>& query) 
        : Token(TokenTag::Uri) {

        this->scheme = scheme;
        this->host = host;
        this->absolutePath = absolutePath;
        this->query = query;
        this->port = UriToken::UnspecifiedPort;
    }

    string UriToken::GetScheme() const {
        return scheme;
    }

    string UriToken::GetHost() const {
        return host;
    }

    unsigned short UriToken::GetPort() const {
        return port;
    }

    string UriToken::GetAbsolutePath() const {
        return absolutePath;
    }

    vector<NameValuePair> UriToken::GetQuery() const {
        return query;
    }

}
}
}