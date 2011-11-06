#ifndef MESSAGE_PARSE_ERROR
#define MESSAGE_PARSE_ERROR

#include <exception>
#include <string>
using std::string;

namespace JustServer {
namespace Http {

    class MessageParseError : public std::exception {
    public:
        MessageParseError(const string& message)
            : std::exception(message) {

            this->errorCode = -1;
        }

        MessageParseError(const int errorCode) {
            this->errorCode = errorCode;
        }
    private:
        int errorCode;
    };

}
}

#endif