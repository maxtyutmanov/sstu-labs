#include "NetworkService.h"
#include <string>
#include <boost/asio/placeholders.hpp>
using std::string;

NetworkService::NetworkService(
    std::auto_ptr<IRequestDispatcher> requestDispatcher,
    const string& ipAddress,
    const unsigned short portNumber) {

    //must clean up a mess in the case when initialization of some member field fails

    io_service.reset(new boost::asio::io_service());

    try {
        serverEndpoint.reset(new tcp::endpoint(tcp::v4(), portNumber));
    }
    catch (const boost::system::system_error &ex) {
        delete io_service.release();
        throw ex;
    }

    try {
        listener.reset(new tcp::acceptor(*io_service, *serverEndpoint, true));
    }
    catch (const boost::system::system_error &ex) {
        delete io_service.release();
        delete serverEndpoint.release();
        throw ex;
    }

    try {
        listener->listen(10);
    }
    catch (const boost::system::system_error &ex) {
        delete io_service.release();
        delete serverEndpoint.release();
        delete listener.release();
        throw ex;
    }

    this->requestDispatcher = requestDispatcher;

    isRunning = false;
}

NetworkService::~NetworkService() {
    try {
        this->StopImpl();

        //TODO: that's the spike. Otherwise memory access 
        //violation exception would be thrown while destructing listener
        //after other members' (especially io_service) destruction
        //(and I don't know why the hell it's destructed AFTER other members!)
        delete listener.release();
    }
    catch (const boost::system::system_error &ex) {
        //TODO: mmm... :-)
    }
}

void NetworkService::Start() {
    if (!isRunning) {
        StartAsyncListening();
        
        isRunning = true;
        ioserviceThread.reset(new boost::thread(&NetworkService::RunIoservice, this));
    }
}

void NetworkService::Stop() {
    StopImpl();
}

void NetworkService::StartAsyncListening() {
    shared_ptr<tcp::socket> pSocket(new tcp::socket(*io_service));
    
    listener->async_accept(*pSocket, boost::bind(&NetworkService::HandleRequest, this, pSocket, boost::asio::placeholders::error));
}

void NetworkService::HandleRequest(shared_ptr<tcp::socket> pSocket, const boost::system::error_code &ec) {
    if (ec) {

        //checking for error code, and if value = operation_aborted then listener->cancel() has been called
        //and we must stop listening for new connections
        if (ec.value() != boost::asio::error::operation_aborted) {
            StartAsyncListening();
        }
        else {
            //pSocket.
        }

        return;
    }

    //We don't care about app protocol-specific communication details,
    //just letting the requestDispatcher to deal with them

    //TODO: maybe it'll be better to return smth from requestDispatcher.
    //TODO: btw, has this got to be async?
    requestDispatcher->DispatchRequest(pSocket);

    //and starting to listen for incoming connections again
    StartAsyncListening();
}

void NetworkService::RunIoservice() {
    io_service->run();
}

void NetworkService::StopImpl() {
    if (isRunning) {
        boost::system::error_code ec;

        listener->cancel();

        ioserviceThread->join();
        //making io_service reusable
        io_service->stop();
        io_service->reset();

        isRunning = false;
    }
}