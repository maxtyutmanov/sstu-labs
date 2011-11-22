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
            const std::string& absolutePath,
            unsigned short port,
            const std::vector<JustServer::Utility::NameValuePair>& query);

        Uri(const std::string& scheme, 
            const std::string& host,
            const std::string& absolutePath,
            const std::vector<JustServer::Utility::NameValuePair>& query);

        std::string GetScheme() const;
        std::string GetHost() const;
        std::string GetAbsolutePath() const;
        unsigned short GetPort() const;
        const std::vector<JustServer::Utility::NameValuePair>& Query() const;
    private:
        std::string scheme;
        std::string host;
        std::string absolutePath;
        unsigned short port;
        std::vector<JustServer::Utility::NameValuePair> query;
    };
}
}

#endif