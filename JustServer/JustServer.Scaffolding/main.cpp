#include "EchoDispatcher.h"
#include <NetworkService.h>
#include <iostream>
#include <locale>
using std::cin;
using std::cout;
using std::auto_ptr;

using namespace JustServer::Net;
using namespace boost::asio::ip;


int main(int argc, char** argv) {
    cout.imbue(std::locale("rus_rus.866"));

    std::auto_ptr<IRequestDispatcher> dispatcher(new EchoDispatcher());

    auto_ptr<tcp::endpoint> pEndpoint(new tcp::endpoint(tcp::v4(), 5555));

    NetworkService ns(dispatcher, pEndpoint);

    ns.Start();

    cin.get();
    
    return 0;
}