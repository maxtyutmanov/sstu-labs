#ifndef HTTPCORE_H
#define HTTPCORE_H

#include "HttpResponse.h"
#include "HttpRequestParser.h"
#include <IInputBuffer.h>

namespace JustServer {
namespace Http {

    class HttpCore {
    public:
        auto_ptr<HttpResponse> HandleRequest(auto_ptr<IInputBuffer> pInputBuffer);
    private:
        HttpRequestParser requestParser;
    };

}
}

#endif