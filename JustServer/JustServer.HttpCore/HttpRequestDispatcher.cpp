#include "HttpRequestDispatcher.h"
#include "HttpCore.h"

#include <vector>
#include <string>
using std::string;
using std::vector;

namespace JustServer {
namespace Http {

    void HttpRequestDispatcher::DispatchRequest(shared_ptr<tcp::socket> pSocket) {
        string receiveBuf;
        receiveBuf.reserve(1024);   //to config
        vector<char> tmpReceiveBuf(128);

        //step 1. Receive request from client

        boost::system::error_code ec;

        while (true) {
            size_t rcvdBytes = pSocket->receive(boost::asio::buffer(tmpReceiveBuf), 0, ec);

            if (ec) {
                pSocket->close();
                return;
            }

            for (size_t i = 0; i < rcvdBytes; ++i) {
                receiveBuf.push_back(tmpReceiveBuf[i]);
            }

            //TODO: check for buffer overrun

            if (rcvdBytes < tmpReceiveBuf.size()) {
                break;
            }
        }

        //step 2. 


    }

    size_t HttpRequestDispatcher::EndOfRequestLineIndex(const string& readInput) {
        //readInput.find_first_of(""
    }
}
}