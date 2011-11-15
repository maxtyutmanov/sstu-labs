#ifndef MESSAGE_PARSE_ERROR
#define MESSAGE_PARSE_ERROR

#include <exception>
#include <string>

namespace JustServer {
namespace Http {

    class MessageParseError : public std::exception {
    public:
        MessageParseError(const std::string& message)
            : std::exception(message.c_str()) { }
    };

}
}

#endif