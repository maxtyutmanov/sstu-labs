#ifndef HTTPCORE_H
#define HTTPCORE_H

#include "HttpResponse.h"
#include "HttpRequestParser.h"
#include "IHttpHandler.h"
#include <IInputBuffer.h>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <memory>

namespace JustServer {
namespace Http {

    class HttpCore {
    public:
        void AddHttpHandler(boost::shared_ptr<IHttpHandler> handler);

        auto_ptr<HttpResponse> HandleRequest(std::auto_ptr<IInputBuffer> pInputBuffer) const;
    private:
        HttpRequestParser requestParser;
        std::vector<boost::shared_ptr<IHttpHandler>> httpHandlers;

        bool TryPickHandler(const HttpRequest& httpRequest, IHttpHandler** ppHandler) const;

        std::auto_ptr<HttpResponse> OnInvalidRequest(const std::vector<boost::shared_ptr<Token>>& httpRequestTokens) const;
        std::auto_ptr<HttpResponse> OnHandlerNotFound(const HttpRequest& request) const;
    };

}
}

#endif