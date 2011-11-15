#ifndef URI_H
#define URI_H

#include <string>
#include <vector>

#include <NameValuePair.h>

namespace JustServer {
namespace Http {

    class Uri {
    public:
        Uri(const std::string& scheme, 
            const std::string& host,
            unsigned short port,
            const std::vector<JustServer::Utility::NameValuePair>& query);

        Uri(const std::string& scheme, 
            const std::string& host,
            const std::vector<JustServer::Utility::NameValuePair>& query);

        string GetScheme() const;
        string GetHost() const;
        unsigned short GetPort() const;
        const std::vector<JustServer::Utility::NameValuePair>& Query() const;
    private:
        std::string scheme;
        std::string host;
        unsigned short port;
        std::vector<JustServer::Utility::NameValuePair> query;
    };
}
}

#endif