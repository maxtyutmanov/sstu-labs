#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include "INetworkService.h"
#include "IRequestDispatcher.h"
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <string>
#include <boost/thread.hpp>
using std::string;
using namespace boost::asio::ip;
using std::auto_ptr;

class NetworkService : public INetworkService {
public:
    NetworkService(
        auto_ptr<IRequestDispatcher> requestDispatcher,
        const string& ipAddress,
        const unsigned short portNumber);

    ~NetworkService();

    virtual void Start();

    //TODO: to make this work we need to run io_service in a separate thread
    //never call it. It doesn't work anyway :)
    virtual void Stop();
private:
    void StartAsyncListening();
    void HandleRequest(shared_ptr<tcp::socket> pSocket);

    auto_ptr<IRequestDispatcher> requestDispatcher;
    auto_ptr<tcp::acceptor> listener;
    auto_ptr<boost::asio::io_service> io_service;
    auto_ptr<tcp::endpoint> serverEndpoint;
    auto_ptr<boost::thread> listeningThread;
    bool stopped;
};

#endif