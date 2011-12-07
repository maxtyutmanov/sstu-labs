#ifndef INVALID_CONFIGURATION_EXCEPTION_H
#define INVALID_CONFIGURATION_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace JustServer {
namespace Configuration {

    class InvalidConfigurationException : public std::runtime_error {
    public:
        InvalidConfigurationException(const std::string& message) 
            : std::runtime_error(message) { }
    };

}
}

#endif