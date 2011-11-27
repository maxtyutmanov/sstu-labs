#include "BasicAuthenticationModule.h"
#include "User.h"
#include <Base64Utility.h>

using namespace JustServer::Configuration;
using namespace std;
using JustServer::Utility::Base64Utility;

namespace JustServer {
namespace Http {
namespace Security {

    BasicAuthenticationModule::BasicAuthenticationModule(
        boost::shared_ptr<IAppConfigurationManager> configurationManager,
        boost::shared_ptr<IUserRepository> userRepository)
        : configurationManager(configurationManager), userRepository(userRepository) {}

    void BasicAuthenticationModule::AuthenticateRequest(HttpRequest& request) const {
        const char* headerName = "authorization";

        if (request.HasHeader(headerName)) {
            string headerValue = request.GetHeaderValue(headerName);

            //we must remove the word "Basic" and the following space from the header value
            string::const_iterator spaceIt = find(
                headerValue.begin(), headerValue.end(), ' ');

            if (spaceIt != headerValue.end())
            {
                ++spaceIt;

                string credentialsBase64(spaceIt, headerValue.end());

                string decodedHeaderValue;
                decodedHeaderValue.reserve((size_t)(ceil(credentialsBase64.size() / 4.0) * 3));

                if (Base64Utility::TryDecodeBase64(credentialsBase64, decodedHeaderValue)) {
                    string username;
                    string password;

                    if (TryParseCredentials(decodedHeaderValue, username, password)) {
                        auto_ptr<User> user = userRepository->GetUser(username, password);

                        if (user.get() != NULL) {
                            request.SetCurrentUser(boost::shared_ptr<User>(user.release()));
                        }
                    }
                }
            }
        }
    }

    auto_ptr<HttpResponse> BasicAuthenticationModule::AuthorizeRequest(const HttpRequest& request) const {
        //precondition: authentication must occur before authorization

        string requestPath = request.GetRequestUri().GetAbsolutePath();

        vector<boost::shared_ptr<SecuredArea>> securedAreas = configurationManager->GetSecuredAreas();

        vector<boost::shared_ptr<SecuredArea>>::const_iterator areasIt;

        //select the appropriate securedArea for this request (if any)
        SecuredArea* pCurrentArea = NULL;
        
        for (areasIt = securedAreas.begin(); areasIt != securedAreas.end(); ++areasIt) {
            string securedPath = (*areasIt)->GetPath();
            
            if (requestPath.find(securedPath) == 0) {
                //request path starts with secured path

                if (pCurrentArea != NULL) {
                    //we must select the longest appropriate secured path ('cause nested secured paths are allowed)
                    if (securedPath.length() > pCurrentArea->GetPath().length()) {
                        pCurrentArea = areasIt->get();
                    }
                }
                else {
                    pCurrentArea = areasIt->get();
                }
            }
        }

        if (pCurrentArea != NULL) {
            //requested path is secured, let's check user's roles

            const vector<string>& allowedRoles = pCurrentArea->GetRoles();

            if (allowedRoles.size() == 0) {
                auto_ptr<HttpResponse> response(new HttpResponse(request.GetHttpVersion()));
                response->SetHeader("connection", "close");
                response->AppendToResponseBody("<html><head><title>404 Not Found</title></head><body><h1>404 Not Found</h1></body></html>");
                response->SetStatusCode(404);

                return response;
            }

            IUser* pCurrentUser = request.GetCurrentUser().get();

            if (pCurrentUser != NULL) {
                User* pCurrentUserWithRoles = dynamic_cast<User*>(pCurrentUser);

                vector<string>::const_iterator rolesIt;

                for (rolesIt = allowedRoles.begin(); rolesIt != allowedRoles.end(); ++rolesIt) {
                    if (pCurrentUserWithRoles->IsInRole(*rolesIt)) {
                        //user is in required role => user is authorized

                        return auto_ptr<HttpResponse>();
                    }
                }
            }

            //user hasn't sent their credintials yet or credentials provided were not valid => send 401 Authenticate
            //TODO: extract to separate method

            auto_ptr<HttpResponse> response(new HttpResponse(request.GetHttpVersion()));
            response->SetHeader("WWW-Authenticate", "Basic realm=\"" + pCurrentArea->GetName() + "\"");
            response->SetHeader("connection", "close");
            response->SetStatusCode(401);

            return response;
        }
        else {
            //the resource being requested is not secured => user is authorized

            return auto_ptr<HttpResponse>();
        }
    }

    bool BasicAuthenticationModule::TryParseCredentials(const string& credentials, string& username, string& password) {
        string::const_iterator colonIt = find(credentials.begin(), credentials.end(), ':');

        if (colonIt != credentials.end()) {
            username.clear();
            password.clear();

            username.assign(credentials.begin(), colonIt);
            
            //step through the colon
            ++colonIt;

            password.assign(colonIt, credentials.end());

            return true;
        }
        else {
            return false;
        }
    }

}
}
}