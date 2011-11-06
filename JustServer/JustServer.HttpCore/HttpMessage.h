#ifndef HTTP_MESSAGE_H
#define HTTP_MESSAGE_H

#include "HttpVersion.h"
#include "HttpHeader.h"

#include <string>
#include <vector>
using std::string;
using std::vector;

namespace JustServer {
namespace Http {

    typedef vector<HttpHeader> HeadersCollection;

    class HttpMessage {
    public:
        void SetHttpVersion(const HttpVersion& httpVersion);
        HttpVersion GetHttpVersion() const;

        bool HasHeader(const string& name) const;
        string GetHeaderValue(const string& name) const;
        void SetHeader(const string& name, const string& value);

        void AppendToBody(const string& bodyPart);
        string GetBody() const;
    private:
        HttpVersion httpVersion;
        HeadersCollection headers;
        string body;
    };

}
}

#endif