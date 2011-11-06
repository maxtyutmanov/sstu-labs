#ifndef HTTP_HEADER_H
#define HTTP_HEADER_H

#include <string>
using std::string;

namespace JustServer {
namespace Http {

    struct HttpHeader {
        string name;
        string value;
    };

}
}

#endif