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
        std::auto_ptr<IRequestDispatcher> requestDispatcher,
        const string& ipAddress,
        const unsigned short portNumber);

    ~NetworkService();

    virtual void Start();

    //TODO: to make this work we need to run io_service in a separate thread
    //never call it. It doesn't work anyway :)
    virtual void Stop();
private:
    void StartAsyncListening();
    void HandleRequest(boost::shared_ptr<tcp::socket> pSocket, const boost::system::error_code &ec);
    void RunIoservice();

    //to avoid pure virtual function call in desctructor
    void StopImpl();

    std::auto_ptr<tcp::acceptor> listener;
    std::auto_ptr<IRequestDispatcher> requestDispatcher;
    std::auto_ptr<boost::asio::io_service> io_service;
    std::auto_ptr<tcp::endpoint> serverEndpoint;
    std::auto_ptr<boost::thread> ioserviceThread;
    bool isRunning;
};

#endif