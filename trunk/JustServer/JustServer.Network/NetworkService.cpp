#include "NetworkService.h"


NetworkService::NetworkService(
    auto_ptr<IRequestDispatcher> requestDispatcher,
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

    stopped = true;
}

NetworkService::~NetworkService() {
    try {
        this->Stop();
    }
    catch (const boost::system::system_error &ex) {
        //TODO: who cares? :-)
    }
}

void NetworkService::Start() {
    if (stopped) {
        StartAsyncListening();
        
        //TODO: should be careful about this call
        io_service->run();
    }
}

void NetworkService::Stop() {
    if (!stopped) {
        listener->cancel();

        stopped = true;
    }
}

void NetworkService::StartAsyncListening() {
    shared_ptr<tcp::socket> pSocket(new tcp::socket(*io_service));

    listener->async_accept(*pSocket, boost::bind(&NetworkService::HandleRequest, this, pSocket));
    stopped = false;
}

void NetworkService::HandleRequest(shared_ptr<tcp::socket> pSocket) {
    //We don't care about app protocol-specific communication details,
    //just letting the requestDispatcher to deal with them

    //TODO: maybe it'll be better to return smth from requestDispatcher.
    //TODO: btw, has this got to be async?
    requestDispatcher->DispatchRequest(pSocket);

    //and starting to listen for incoming connections again
    StartAsyncListening();
}