#ifndef I_SECURITY_MODULE_H
#define I_SECURITY_MODULE_H

#include "HttpRequest.h"
#include "HttpResponse.h"
#include <memory>

namespace JustServer {
namespace Http {
namespace Security {

    class ISecurityModule {
    public:
        virtual void AuthenticateRequest(HttpRequest& request) const = 0;
        virtual std::auto_ptr<HttpResponse> AuthorizeRequest(const HttpRequest& request) const = 0;
    };

}
}
}

#endif