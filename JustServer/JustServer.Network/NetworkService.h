#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include "INetworkService.h"
#include "IRequestDispatcher.h"
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <string>
#include <boost/thread.hpp>
#include <manual_reset_event.h>
#include <boost/noncopyable.hpp>
using std::string;
using namespace boost::asio::ip;
using std::auto_ptr;

namespace JustServer {
namespace Net {

    class NetworkService : 
        public INetworkService,
        private boost::noncopyable {
    public:
        NetworkService(
            std::auto_ptr<IRequestDispatcher> pRequestDispatcher,
            std::auto_ptr<tcp::endpoint> pEndpoint);

        ~NetworkService();

        virtual void Start();
        virtual void Stop();
    private:
        void StartAsyncListening();
        void HandleRequest(boost::shared_ptr<tcp::socket> pSocket, const boost::system::error_code &ec);
        void RunIoservice();

        std::auto_ptr<tcp::acceptor> listener;
        std::auto_ptr<IRequestDispatcher> requestDispatcher;
        std::auto_ptr<boost::asio::io_service> io_service;
        std::auto_ptr<tcp::endpoint> serverEndpoint;
        std::auto_ptr<boost::thread> ioserviceThread;
        std::auto_ptr<boost::mutex> startStopLock;
        std::auto_ptr<manual_reset_event> startedEvent;
        bool isRunning;
    };

}
}

#endif