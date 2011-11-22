#ifndef I_HTTP_HANDLER
#define I_HTTP_HANDLER

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "Uri.h"
#include <memory>

namespace JustServer {
namespace Http {

    //Encapsulates logic of serving a particular class of requests
    class IHttpHandler {
    public:
        //Determines whether the handler can provide response 
        //for the specified request
        virtual bool CanHandleRequest(const HttpRequest& request) const = 0;

        //Returns a response for the specified request
        virtual std::auto_ptr<HttpResponse> HandleRequest(const HttpRequest& request) const = 0;
    };

}
}

#endif