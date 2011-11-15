#ifndef HTTP_MESSAGE_H
#define HTTP_MESSAGE_H

#include "HttpVersion.h"
#include <NameValuePair.h>

#include <string>
#include <vector>
using std::string;
using std::vector;

namespace JustServer {
namespace Http {

    typedef vector<JustServer::Utility::NameValuePair> HeadersCollection;

    //Represents the immutable container for HTTP request message
    class HttpMessage {
    public:
        HttpVersion GetHttpVersion() const;
        bool HasHeader(const string& name) const;
        string GetHeaderValue(const string& name) const;
        string GetBody() const;
    protected:
        HttpMessage(const HttpVersion& httpVersion, const HeadersCollection& headers, const string& body);
    private:
        HttpVersion httpVersion;
        HeadersCollection headers;
        string body;
    };

}
}

#endif