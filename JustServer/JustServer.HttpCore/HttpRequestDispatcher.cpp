#include "HttpRequestDispatcher.h"
#include "HttpCore.h"
#include "LexerInputBuffer.h"

#include <vector>
#include <string>
#include <sstream>
#include <IInputBuffer.h>
#include "StaticContentHandler.h"
#include <ILogger.h>
#include <Locator.h>
using std::string;
using std::vector;

using namespace boost::asio::ip;
using namespace std;
using JustServer::ServiceLocation::Locator;
using JustServer::Logging::EventType;

namespace JustServer {
namespace Http {

    HttpRequestDispatcher::HttpRequestDispatcher(auto_ptr<IHttpCore> pHttpCore) {
        this->pHttpCore = pHttpCore;
    }

    void HttpRequestDispatcher::DispatchRequest(boost::shared_ptr<tcp::socket> pSocket) {
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

            tcp::endpoint remoteEndp = pSocket->remote_endpoint();
            boost::asio::ip::address remoteAddr = remoteEndp.address();
            string addressStr = remoteAddr.to_string();
            wstring addressWstr(addressStr.begin(), addressStr.end());

            pSocket->close();

            Locator::GetLogger()->LogMessage(EventType::RequestHandled, L"Запрос клиента " + addressWstr + L" обработан, данные отправлены");
        }
        catch (const std::exception &ex) {
            boost::system::error_code ec;
            pSocket->close(ec);

            std::string errorMsg = ex.what();
            std::wstring werror(errorMsg.begin(), errorMsg.end());

            Locator::GetLogger()->LogMessage(EventType::Error, L"Исключение во время обработки запроса: " + werror);
        }

    }
}
}