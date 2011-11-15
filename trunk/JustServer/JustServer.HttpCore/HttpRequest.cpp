#include "HttpRequest.h"
using namespace std;

namespace JustServer {
namespace Http {

    HttpRequest::HttpRequest(
        const string& verb,
        const Uri& requestUri,
        const HttpVersion& httpVersion,
        const HeadersCollection& headers,
        const string& body)
        : HttpMessage(httpVersion, headers, body), verb(verb), requestUri(requestUri) {}

    string HttpRequest::GetVerb() const {
        return verb;
    }

    Uri HttpRequest::GetRequestUri() const {
        return requestUri;
    }
}
}