#include "Uri.h"
#include <boost/lexical_cast.hpp>

using namespace std;
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

    wstring Uri::ToWString() const {
        string str = GetScheme() + "://" + GetHost() + ":" + boost::lexical_cast<string, unsigned short>(GetPort()) + GetAbsolutePath();
        wstring result(str.begin(), str.end());

        return result;
    }
}
}