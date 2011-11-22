#include "Uri.h"

using std::string;
using std::vector;
using JustServer::Utility::NameValuePair;

namespace JustServer {
namespace Http {

    Uri::Uri(const string& scheme, 
        const string& host,
        const string& absolutePath,
        unsigned short port,
        const vector<NameValuePair>& query) 
        : scheme(scheme), host(host), absolutePath(absolutePath), port(port), query(query) {
    }

    Uri::Uri(const string& scheme, 
        const string& host,
        const string& absolutePath,
        const vector<NameValuePair>& query) 
        : scheme(scheme), host(host), absolutePath(absolutePath), port(80), query(query) {
    }

    string Uri::GetScheme() const {
        return scheme;
    }

    string Uri::GetHost() const {
        return host;
    }

    string Uri::GetAbsolutePath() const {
        return absolutePath;
    }

    unsigned short Uri::GetPort() const {
        return port;
    }

    const vector<NameValuePair>& Uri::Query() const {
        return query;
    }
}
}