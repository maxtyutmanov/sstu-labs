#ifndef MESSAGE_PARSE_ERROR
#define MESSAGE_PARSE_ERROR

#include <stdexcept>
#include <string>

namespace JustServer {
namespace Http {

    class MessageParseError : public std::runtime_error {
    public:
        MessageParseError(const std::string& message)
            : std::runtime_error(message) { }
    };

}
}

#endif