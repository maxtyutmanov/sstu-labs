#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include "IAppConfigurationManager.h"
#include <tinyxml.h>
#include <string>

namespace JustServer {
namespace Configuration {

    class AppConfigurationManager : public IAppConfigurationManager {
    public:
        AppConfigurationManager(const std::wstring& configFilePath);

        virtual std::vector<boost::shared_ptr<SecuredArea>> GetSecuredAreas() const;
        virtual std::wstring GetAppSetting(const std::string& name) const;
        virtual std::wstring GetConnectionString(const std::string& name) const;
    private:
        TiXmlDocument config;
    };

}
}

#endif