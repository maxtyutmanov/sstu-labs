#pragma once

#include <stdexcept>
#include <string>

namespace ImTrcr {
namespace Imaging {

    class InvalidBmpStreamException : public std::runtime_error {
    public: 
        InvalidBmpStreamException(const std::string& message) 
            : std::runtime_error(message) {}
    };

}
}