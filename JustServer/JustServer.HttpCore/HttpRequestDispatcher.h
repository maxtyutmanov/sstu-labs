#ifndef HTTP_REQUEST_DISPATCHER_H
#define HTTP_REQUEST_DISPATCHER_H

#include <IRequestDispatcher.h>
#include "HttpCore.h"
#include <memory>
#include <string>

using namespace boost::asio::ip;
using std::auto_ptr;
using std::string;

namespace JustServer {
namespace Http {

    class HttpRequestDispatcher : public JustServer::Net::IRequestDispatcher {
    public:
        HttpRequestDispatcher();

        virtual void DispatchRequest(shared_ptr<tcp::socket> pSocket);
    private:
        auto_ptr<HttpCore> pHttpCore;
    };

}
}

#endif