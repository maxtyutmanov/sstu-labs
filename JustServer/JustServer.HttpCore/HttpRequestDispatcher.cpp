#include "HttpRequestDispatcher.h"
#include "HttpCore.h"
#include "LexerInputBuffer.h"

#include <vector>
#include <string>
#include <sstream>
#include <IInputBuffer.h>
using std::string;
using std::vector;

namespace JustServer {
namespace Http {

    HttpRequestDispatcher::HttpRequestDispatcher() {
        pHttpCore.reset(new HttpCore());
    }

    void HttpRequestDispatcher::DispatchRequest(shared_ptr<tcp::socket> pSocket) {
        try {
            string receiveBuf;
            receiveBuf.reserve(1024);   //to config
            vector<char> tmpReceiveBuf(128);

            //Receiving request from client

            boost::system::error_code recEc;

            while (true) {
                size_t rcvdBytes = pSocket->receive(boost::asio::buffer(tmpReceiveBuf), 0, recEc);

                if (recEc) {
                    pSocket->close(recEc);
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

            //TODO: this is a temporary solution!

            std::istringstream inputStream(receiveBuf);
            auto_ptr<IInputBuffer> pInputBuffer(new LexerInputBuffer(inputStream));

            //Getting a response from HTTP subsystem

            auto_ptr<HttpResponse> response = pHttpCore->HandleRequest(pInputBuffer);
            string serializedResponse = response->Serialize();

            //Sending serialized response to the client

            boost::system::error_code sendEc;

            size_t bytesTransferred = 0;

            while (bytesTransferred != serializedResponse.size()) {
                size_t sentThisTime = pSocket->write_some(
                    boost::asio::buffer(serializedResponse.data() + bytesTransferred, serializedResponse.size() - bytesTransferred),
                    sendEc);

                if (sendEc) {
                    pSocket->close(sendEc);
                    return;
                }

                bytesTransferred += sentThisTime;
            }

            pSocket->close();
        }
        catch (const std::exception &ex) {
            boost::system::error_code ec;

            pSocket->close(ec);
        }

    }
}
}