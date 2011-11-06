#ifndef HTTPCORE_H
#define HTTPCORE_H

#include "HttpResponse.h"
#include "HttpWorkerRequest.h"

namespace JustServer {
namespace Http {

    class HttpCore {
    public:
        HttpCore();

        HttpResponse HandleRequest(const HttpWorkerRequest& workerRequest);
    };

}
}

#endif