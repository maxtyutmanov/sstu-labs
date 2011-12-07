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
#include <SqlServerLogger.h>
#include <Locator.h>
#include <ServerConfigurationManager.h>
#include <WebApplicationSection.h>

using namespace std;
using namespace JustServer::Net;
using namespace boost::asio::ip;
using namespace JustServer::Http;
using namespace JustServer::Http::Security;
using namespace JustServer::Configuration;
using namespace JustServer::Logging;
using namespace JustServer::ServiceLocation;
using JustServer::Configuration::WebApplicationSection;

boost::shared_ptr<NetworkService> RunWebApplication(const WebApplicationSection& appConfigSection);

int main(int argc, char** argv) {
    ServerConfigurationManager serverConfigManager(L"serverConfig.xml");
    vector<WebApplicationSection> webAppSections = serverConfigManager.GetApplicationsSections();

    vector<boost::shared_ptr<NetworkService>> runningNetworkServices;
    runningNetworkServices.reserve(webAppSections.size());
    vector<WebApplicationSection>::const_iterator wasIt;

    for (wasIt = webAppSections.begin(); wasIt != webAppSections.end(); ++wasIt) {
        boost::shared_ptr<NetworkService> ns = RunWebApplication(*wasIt);
        runningNetworkServices.push_back(ns);
    }

    cin.get();
    
    vector<boost::shared_ptr<NetworkService>>::iterator nsIt;

    for (nsIt = runningNetworkServices.begin(); nsIt != runningNetworkServices.end(); ++nsIt) {
        (*nsIt)->Stop();
    }

    return 0;
}

boost::shared_ptr<NetworkService> RunWebApplication(const WebApplicationSection& appConfigSection) {
    wstring physicalPath = appConfigSection.GetPhysicalPath();
    wstring configFilePath = physicalPath + L"appConfig.xml";

    boost::shared_ptr<IAppConfigurationManager> appConfigManager(new AppConfigurationManager(configFilePath));
    boost::shared_ptr<IUserRepository> userRepository(new UserRepository(appConfigManager->GetAppSetting("usersDbPath")));
    boost::shared_ptr<ISecurityModule> securityModule(new BasicAuthenticationModule(appConfigManager, userRepository));

    ILogger* logger = new SqlServerLogger(appConfigManager->GetConnectionString("SqlServerLogger"));
    Locator::Register(logger);

    HttpCore* httpCore = new HttpCore(physicalPath, securityModule);
    boost::shared_ptr<IHttpHandler> staticHandler(new JustServer::Http::StandardHandlers::StaticContentHandler());
    httpCore->AddHttpHandler(staticHandler);

    std::auto_ptr<IRequestDispatcher> dispatcher(new HttpRequestDispatcher(auto_ptr<IHttpCore>(httpCore)));

    auto_ptr<tcp::endpoint> pEndpoint(new tcp::endpoint(tcp::v4(), appConfigSection.GetPort()));

    boost::shared_ptr<NetworkService> networkService(new NetworkService(dispatcher, pEndpoint));

    networkService->Start();

    return networkService;
}