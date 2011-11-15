#ifndef HEADER_NOT_FOUND_EXCEPTION_H
#define HEADER_NOT_FOUND_EXCEPTION_H

#include <exception>
#include <string>

namespace JustServer {
namespace Http {

    class HeaderNotFoundException : std::exception {
    public:
        HeaderNotFoundException(const std::string& headerName)
            : std::exception("Header wasn't found in HTTP message") {}
    };

}
}

#endif