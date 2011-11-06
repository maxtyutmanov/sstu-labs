#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <string>
using std::string;

namespace JustServer {
namespace Http {

    //Represents a serializable container for response info
    class HttpResponse {
    public:
        string Serialize() const;
    };

}
}

#endif