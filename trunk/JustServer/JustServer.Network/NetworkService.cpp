#include "NetworkService.h"

NetworkService::NetworkService(
    shared_ptr<IRequestDispatcher> requestDispatcher,
    const string& ipAddress,
    const string& service) {


    listener.reset(new tcp::acceptor(boost::asio::io_service()));
}

void NetworkService::Start() {
    
}