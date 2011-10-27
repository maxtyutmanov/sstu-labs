#ifndef HTTPREQUESTHANDLER_H
#define HTTPREQUESTHANDLER_H

#include <IRequestDispatcher.h>

using namespace boost::asio::ip;

class HttpRequestHandler : IRequestDispatcher {
public:
    virtual void DispatchRequest(shared_ptr<boost::asio::ip::tcp::socket> pSocket);
};

#endif