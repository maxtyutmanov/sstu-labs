#ifndef I_CONFIGURATION_MANAGER_H
#define I_CONFIGURATION_MANAGER_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include "SecuredArea.h"

namespace JustServer {
namespace Configuration {

    class IAppConfigurationManager {
    public:
        virtual std::vector<boost::shared_ptr<SecuredArea>> GetSecuredAreas() const = 0;
    };

}
}

#endif