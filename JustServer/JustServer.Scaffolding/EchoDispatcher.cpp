#include "EchoDispatcher.h"
#include <vector>
#include <string>
#include <iostream>
using std::vector;
using std::string;
using std::cout;
using std::endl;

void EchoDispatcher::DispatchRequest(shared_ptr<tcp::socket> pSocket) {
    //step 1. Receiving request from client

    vector<char> receiveBuf;
    receiveBuf.reserve(1024);

    while (true) {
        vector<char> tmpBuf(100);
        boost::system::error_code ec;

        size_t receivedBytes = pSocket->receive(boost::asio::buffer(tmpBuf), 0, ec);

        if (ec) {
            cout << ec.message() << endl;
            pSocket->close(ec);
            return;
        }

        for (size_t i = 0; i < receivedBytes; ++i) {
            receiveBuf.push_back(tmpBuf[i]);
        }

        if (receivedBytes < tmpBuf.size()) {
            break;
        }
    }

    //step 2. Writing the request text to the console

    string receivedText;
    receivedText.resize(receiveBuf.size());

    for (size_t i = 0; i < receiveBuf.size(); ++i) {
        receivedText[i] = receiveBuf[i];
    }

    cout << receivedText << endl;

    //step 3. Echo response

    boost::system::error_code ec;

    //TODO: made assumption that the whole message could be sent by calling send() only once
    size_t bytesSent = pSocket->send(boost::asio::buffer(receiveBuf), 0, ec);

    if (ec) {
        cout << ec.message() << endl;
        pSocket->close();
    }
}