#ifndef DATA_ACCESS_EXCEPTION_H
#define DATA_ACCESS_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace JustServer {
namespace Http {
namespace Security {

    class DataAccessException : public std::runtime_error {
    public:
        DataAccessException(const std::string& message)
            : std::runtime_error(message) {}
    };

}
}
}

#endif