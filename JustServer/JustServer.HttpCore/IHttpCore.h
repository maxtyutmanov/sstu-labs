#ifndef I_HTTP_CORE
#define I_HTTP_CORE

#include "HttpResponse.h"
#include <IInputBuffer.h>
#include <memory>

namespace JustServer {
namespace Http {

    class IHttpCore {
    public:
        virtual auto_ptr<HttpResponse> HandleRequest(std::auto_ptr<IInputBuffer> pInputBuffer) const = 0;
    };

}
}

#endif