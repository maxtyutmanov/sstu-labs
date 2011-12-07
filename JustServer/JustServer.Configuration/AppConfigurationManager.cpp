#include "AppConfigurationManager.h"
#include <fstream>
#include <string>
#include "InvalidConfigurationException.h"
#include <EncodingUtility.h>

using namespace std;
using JustServer::Utility::EncodingUtility;

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

    wstring AppConfigurationManager::GetAppSetting(const string& name) const {
        const TiXmlElement* configuration = config.FirstChildElement("configuration");

        if (configuration == NULL) {
            throw InvalidConfigurationException("configuration element is missing");
        }

        const TiXmlElement* appSettings = configuration->FirstChildElement("appSettings");

        if (appSettings == NULL) {
            //TODO: bad behaviour
            return L"";
        }

        const TiXmlElement* currentSetting = appSettings->FirstChildElement("setting");

        while (currentSetting != NULL) {
            const char* settingName = currentSetting->Attribute("name");

            if (settingName == name) {
                const char* settingValue = currentSetting->Attribute("value");

                if (settingValue != NULL) {
                    return wstring(EncodingUtility::Utf8ToWideChar(settingValue));
                }
                else {
                    //TODO: this is bad
                    return L"";
                }
            }

            currentSetting = currentSetting->NextSiblingElement();
        }

        return L"";
    }

    wstring AppConfigurationManager::GetConnectionString(const string& name) const {
        const TiXmlElement* configuration = config.FirstChildElement("configuration");

        if (configuration == NULL) {
            throw InvalidConfigurationException("configuration element is missing");
        }

        const TiXmlElement* connectionStrings = configuration->FirstChildElement("connectionStrings");

        if (connectionStrings == NULL) {
            //TODO: bad behaviour
            return L"";
        }

        const TiXmlElement* currentConnectionString = connectionStrings->FirstChildElement("connectionString");

        while (currentConnectionString != NULL) {
            const char* conStrName = currentConnectionString->Attribute("name");

            if (conStrName == name) {
                const char* conStrValue = currentConnectionString->Attribute("value");

                if (conStrValue != NULL) {
                    return wstring(EncodingUtility::Utf8ToWideChar(conStrValue));
                }
                else {
                    //TODO: this is bad
                    return L"";
                }
            }

            currentConnectionString = currentConnectionString->NextSiblingElement();
        }

        return L"";
    }
}
}