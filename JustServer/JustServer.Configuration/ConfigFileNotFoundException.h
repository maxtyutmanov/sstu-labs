#ifndef CONFIG_FILE_NOT_FOUND_EXCEPTION_H
#define CONFIG_FILE_NOT_FOUND_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace JustServer {
namespace Configuration {

    class ConfigFileNotFoundException : public std::runtime_error {
    public:
        ConfigFileNotFoundException(const std::string& message)
            : std::runtime_error(message) {}
    };

}
}

#endif