//#include "EchoDispatcher.h"
#include <HttpCore.h>
#include <HttpRequestDispatcher.h>
#include <NetworkService.h>
#include <iostream>
#include <locale>
#include <memory>
#include <StaticContentHandler.h>
#include <BasicAuthenticationModule.h>
#include <AppConfigurationManager.h>
#include <UserRepository.h>

using namespace std;
using namespace JustServer::Net;
using namespace boost::asio::ip;
using namespace JustServer::Http;
using namespace JustServer::Http::Security;
using namespace JustServer::Configuration;


int main(int argc, char** argv) {
    boost::shared_ptr<IAppConfigurationManager> configurationManager(new AppConfigurationManager(L"C:\\Users\\������\\Documents\\Visual Studio 2010\\WebSites\\Lab2\\config.xml"));
    boost::shared_ptr<IUserRepository> userRepository(new UserRepository(L"C:\\Users\\������\\Documents\\Visual Studio 2010\\WebSites\\Lab2\\Data\\users.db"));

    boost::shared_ptr<ISecurityModule> securityModule(new BasicAuthenticationModule(configurationManager, userRepository));

    HttpCore* pHttpCore = new HttpCore(L"C:\\Users\\������\\Documents\\Visual Studio 2010\\WebSites\\Lab2\\", securityModule);
    boost::shared_ptr<IHttpHandler> staticHandler(new JustServer::Http::StandardHandlers::StaticContentHandler());
    pHttpCore->AddHttpHandler(staticHandler);

    std::auto_ptr<IRequestDispatcher> dispatcher(new HttpRequestDispatcher(auto_ptr<IHttpCore>(pHttpCore)));

    auto_ptr<tcp::endpoint> pEndpoint(new tcp::endpoint(tcp::v4(), 5555));

    NetworkService ns(dispatcher, pEndpoint);

    ns.Start();

    cin.get();

    ns.Stop();

    cin.get();

    ns.Start();

    cin.get();
    
    return 0;
}