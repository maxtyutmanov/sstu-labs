#include "HttpRequest.h"
#include <boost/algorithm/string.hpp>
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

    wstring HttpRequest::GetPhysicalPath() const {
        return physicalPath;
    }

    void HttpRequest::SetApplicationPath(const wstring& appPath) {
        //TODO: optimize

        string requestPath = this->GetRequestUri().GetAbsolutePath();

        if (requestPath.length() > 1 && requestPath[0] == '/') {
            requestPath.erase(requestPath.begin());
        }

        std::replace_if(requestPath.begin(), requestPath.end(), boost::is_any_of("/"), '\\');

        //copy to wide char string

        wstring requestPathW(requestPath.begin(), requestPath.end());

        physicalPath = appPath + requestPathW;
    }

    boost::shared_ptr<Security::IUser> HttpRequest::GetCurrentUser() const {
        return currentUser;
    }

    void HttpRequest::SetCurrentUser(boost::shared_ptr<Security::IUser> user) {
        currentUser = user;
    }
}
}