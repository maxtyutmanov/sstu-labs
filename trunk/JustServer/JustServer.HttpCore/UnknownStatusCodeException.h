#ifndef UNKNOWN_STATUS_CODE_EXCEPTION_H
#define UNKNOWN_STATUS_CODE_EXCEPTION_H

#include <stdexcept>
#include <string>
#include <boost/lexical_cast.hpp>

namespace JustServer {
namespace Http {

    class UnknownStatusCodeException : public std::runtime_error {
    public:
        UnknownStatusCodeException(const std::string& errorMessage)
            : std::runtime_error(errorMessage) {}

        UnknownStatusCodeException(int statusCode)
            : std::runtime_error(std::string("Unknown HTTP response status code: " + boost::lexical_cast<std::string, int>(statusCode))) {}
    };

}
}

#endif