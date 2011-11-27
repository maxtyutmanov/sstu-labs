#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "HttpMessage.h"
#include "Uri.h"
#include "IUser.h"
#include <vector>
#include <boost/shared_ptr.hpp>

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
        std::wstring GetPhysicalPath() const;
        void SetApplicationPath(const std::wstring& appPath);
        boost::shared_ptr<Security::IUser> GetCurrentUser() const;
        void SetCurrentUser(boost::shared_ptr<Security::IUser> user);
    private:
        std::string verb;
        Uri requestUri;
        std::wstring physicalPath;
        boost::shared_ptr<Security::IUser> currentUser;
    };

}
}

#endif