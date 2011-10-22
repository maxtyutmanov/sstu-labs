#ifndef IREQUESTHANDLER_H
#define IREQUESTHANDLER_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/shared_ptr.hpp>
using namespace boost::asio::ip;
using boost::shared_ptr;

class IRequestDispatcher {
public:
    virtual void DispatchRequest(shared_ptr<tcp::socket> connDescriptor) = 0;
};

#endif