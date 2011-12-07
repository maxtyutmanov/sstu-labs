#ifndef SERVER_CONFIGURATION_MANAGER
#define SERVER_CONFIGURATION_MANAGER

#include <string>
#include <vector>
#include <tinyxml.h>
#include "WebApplicationSection.h"

namespace JustServer {
namespace Configuration {

    class ServerConfigurationManager {
    public:
        ServerConfigurationManager(const std::wstring& configFilePath);

        std::vector<WebApplicationSection> GetApplicationsSections() const;
    private:
        TiXmlDocument config;
    };

}
}

#endif