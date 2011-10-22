#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include "INetworkService.h"
#include "IRequestDispatcher.h"
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <string>
using std::string;
using boost::asio::ip;
using std::auto_ptr;

class NetworkService : public INetworkService {
public:
    NetworkService(
        shared_ptr<IRequestDispatcher> requestDispatcher,
        const string& ipAddress,
        const string& service);

    virtual void Start();
    virtual void Stop();
protected:
    shared_ptr<IRequestDispatcher> requestDispatcher;
    
    auto_ptr<tcp::acceptor> listener;
};

#endif