#include "AppConfigurationManager.h"
#include <fstream>
#include <string>

using namespace std;

namespace JustServer {
namespace Configuration {

    AppConfigurationManager::AppConfigurationManager(const wstring& configFilePath) {
        //TODO: error handling

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
    }

    vector<boost::shared_ptr<SecuredArea>> AppConfigurationManager::GetSecuredAreas() const {
        vector<boost::shared_ptr<SecuredArea>> areas;
        
        //TODO: error handling

        const TiXmlElement* configuration = config.FirstChildElement("configuration");
        const TiXmlElement* securedAreas = configuration->FirstChildElement("securedAreas");
         
        const TiXmlElement* curSecuredArea = securedAreas->FirstChildElement();

        while (curSecuredArea != NULL) {
            string areaName = curSecuredArea->Attribute("name");
            string areaPath = curSecuredArea->Attribute("path");

            vector<string> roles;

            const TiXmlElement* curRole = curSecuredArea->FirstChildElement();

            while (curRole != NULL) {
                roles.push_back(curRole->Attribute("name"));

                curRole = curRole->NextSiblingElement();
            }

            areas.push_back(boost::shared_ptr<SecuredArea>(new SecuredArea(areaName, areaPath, roles)));

            curSecuredArea = curSecuredArea->NextSiblingElement();
        }

        return areas;
    }
}
}