#ifndef HTTPREQUESTHANDLER_H
#define HTTPREQUESTHANDLER_H

#include <IRequestDispatcher.h>

class HttpRequestHandler : IRequestDispatcher {
public:
    virtual void DispatchRequest(shared_ptr<boost::asio::ip::tcp::socket> connDescriptor);
};

#endif