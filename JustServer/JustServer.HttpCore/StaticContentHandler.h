#ifndef STATIC_CONTENT_HANDLER
#define STATIC_CONTENT_HANDLER

#include "IHttpHandler.h"
#include "ContentTypeMapping.h"

namespace JustServer {
namespace Http {
namespace StandardHandlers {

    class StaticContentHandler : public IHttpHandler {
    public:
        virtual bool CanHandleRequest(const HttpRequest& request) const;
        virtual std::auto_ptr<HttpResponse> HandleRequest(const HttpRequest& request) const;
    private:
        static ContentTypeMapping contentTypeMapping;
    };

}
}
}

#endif