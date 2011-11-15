#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "HttpMessage.h"
#include "Uri.h"
#include <vector>

namespace JustServer {
namespace Http {

    //Represents a container for the HTTP request info
    class HttpRequest : public HttpMessage {
    public:
        HttpRequest(
            const string& verb,
            const Uri& requestUri,
            const HttpVersion& httpVersion,
            const HeadersCollection& headers,
            const string& body);

        std::string GetVerb() const;
        Uri GetRequestUri() const;
    private:
        std::string verb;
        Uri requestUri;
    };

}
}

#endif