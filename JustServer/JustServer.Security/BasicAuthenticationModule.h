#ifndef BASIC_AUTHENTICATION_MODULE
#define BASIC_AUTHENTICATION_MODULE

#include <ISecurityModule.h>
#include <IAppConfigurationManager.h>
#include "IUserRepository.h"
#include <boost/shared_ptr.hpp>

namespace JustServer {
namespace Http {
namespace Security {

    class BasicAuthenticationModule : public ISecurityModule {
    public:
        BasicAuthenticationModule(
            boost::shared_ptr<JustServer::Configuration::IAppConfigurationManager> configurationManager,
            boost::shared_ptr<IUserRepository> userRepository);

        virtual void AuthenticateRequest(HttpRequest& request) const;
        virtual std::auto_ptr<HttpResponse> AuthorizeRequest(const HttpRequest& request) const;
    private:
        boost::shared_ptr<JustServer::Configuration::IAppConfigurationManager> configurationManager;
        boost::shared_ptr<IUserRepository> userRepository;

        static bool TryParseCredentials(const std::string& credentials, std::string& username, std::string& password);
    };

}
}
}

#endif