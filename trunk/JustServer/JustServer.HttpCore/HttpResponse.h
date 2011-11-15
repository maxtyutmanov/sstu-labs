#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "HttpMessage.h"
#include <vector>
using std::vector;

namespace JustServer {
namespace Http {

    //Represents a serializable container for response info
    class HttpResponse : public HttpMessage {
    public:
        vector<char> Serialize() const;
    };

}
}

#endif