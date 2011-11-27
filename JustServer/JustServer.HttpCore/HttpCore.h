#ifndef HTTPCORE_H
#define HTTPCORE_H

#include "IHttpCore.h"
#include "HttpRequestParser.h"
#include "IHttpHandler.h"
#include "ISecurityModule.h"
#include <vector>
#include <boost/shared_ptr.hpp>
#include <memory>

namespace JustServer {
namespace Http {

    class HttpCore : public IHttpCore {
    public:
        HttpCore(const std::wstring& physicalPath, boost::shared_ptr<JustServer::Http::Security::ISecurityModule> securityModule);

        void AddHttpHandler(boost::shared_ptr<IHttpHandler> handler);

        virtual auto_ptr<HttpResponse> HandleRequest(std::auto_ptr<IInputBuffer> pInputBuffer) const;
    private:
        HttpRequestParser requestParser;
        std::vector<boost::shared_ptr<IHttpHandler>> httpHandlers;
        boost::shared_ptr<JustServer::Http::Security::ISecurityModule> securityModule;

        bool TryPickHandler(const HttpRequest& httpRequest, IHttpHandler** ppHandler) const;
        std::auto_ptr<HttpResponse> OnInvalidRequest(const std::vector<boost::shared_ptr<Token>>& httpRequestTokens) const;
        std::auto_ptr<HttpResponse> OnHandlerNotFound(const HttpRequest& request) const;

        std::wstring physicalPath;
    };

}
}

#endif