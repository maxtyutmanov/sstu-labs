#ifndef HTTP_REQUEST_DISPATCHER_H
#define HTTP_REQUEST_DISPATCHER_H

#include "IHttpCore.h"
#include <IRequestDispatcher.h>
#include <memory>
#include <string>

namespace JustServer {
namespace Http {

    class HttpRequestDispatcher : public JustServer::Net::IRequestDispatcher {
    public:
        HttpRequestDispatcher(std::auto_ptr<IHttpCore> pHttpCore);

        virtual void DispatchRequest(boost::shared_ptr<tcp::socket> pSocket);
    private:
        std::auto_ptr<IHttpCore> pHttpCore;
    };

}
}

#endif