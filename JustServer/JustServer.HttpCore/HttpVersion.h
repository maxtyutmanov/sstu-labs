#ifndef HTTP_VERSION_H
#define HTTP_VERSION_H

#include <string>
#include <memory>
using std::string;
using std::auto_ptr;

namespace JustServer {
namespace Http {

    class HttpVersion {
    public:
        HttpVersion(const unsigned major, const unsigned minor);

        unsigned int Minor() const;
        unsigned int Major() const;
    private:
        unsigned minor;
        unsigned major;
    };

}
}

#endif