#ifndef HEADER_NOT_FOUND_EXCEPTION_H
#define HEADER_NOT_FOUND_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace JustServer {
namespace Http {

    class HeaderNotFoundException : std::runtime_error {
    public:
        HeaderNotFoundException(const std::string& headerName)
            : std::runtime_error("Header wasn't found in HTTP message") {}
    };

}
}

#endif