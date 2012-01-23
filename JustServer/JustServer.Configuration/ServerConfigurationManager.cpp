#include "ServerConfigurationManager.h"
#include "InvalidConfigurationException.h"
#include <fstream>
#include <EncodingUtility.h>
#include "ConfigFileNotFoundException.h"

using namespace std;
using JustServer::Utility::EncodingUtility;

namespace JustServer {
namespace Configuration {

    ServerConfigurationManager::ServerConfigurationManager(const wstring& configFilePath) {
        ifstream configFile(configFilePath);

        if (configFile.good()) {
            //read all text from the configuration file

            //TODO: optimize
            string fileData = string(
                istreambuf_iterator<char>(configFile),
                istreambuf_iterator<char>());

            //TODO: error handling
            config.Parse(fileData.c_str());
        }
        else {
            throw ConfigFileNotFoundException("serverConfig.xml wasn't found in the current directory");
        }
    }

    vector<WebApplicationSection> ServerConfigurationManager::GetApplicationsSections() const {
        const TiXmlElement* configuration = config.FirstChildElement("configuration");

        if (configuration == NULL) {
            throw InvalidConfigurationException("configuration element is missing");
        }

        const TiXmlElement* webServer = configuration->FirstChildElement("webServer");

        if (webServer == NULL) {
            throw InvalidConfigurationException("webServer element is missing");
        }
        
        vector<WebApplicationSection> sections;

        const TiXmlElement* currentWebApp = webServer->FirstChildElement("webApplication");

        while (currentWebApp != NULL) {
            const char* physicalPath = currentWebApp->Attribute("physicalPath");

            if (physicalPath == NULL) {
                throw InvalidConfigurationException("physicalPath attribute is missing");
            }

            wstring wPhysicalPath = EncodingUtility::Utf8ToWideChar(physicalPath);

            int port;

            if (currentWebApp->Attribute("port", &port) == NULL) {
                throw InvalidConfigurationException("port attribute is missing");
            }

            //TODO: danger!!! unsafe cast
            sections.push_back(WebApplicationSection(wPhysicalPath, (unsigned short)port));

            currentWebApp = currentWebApp->NextSiblingElement();
        }

        return sections;
    }
}
}