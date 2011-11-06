#include "HttpVersion.h"
#include "MessageParseError.h"
#include "ParseErrorCodes.h"
#include <boost/lexical_cast.hpp>

namespace JustServer {
namespace Http {

    HttpVersion::HttpVersion(const unsigned int major, const unsigned int minor)
        : major(major), minor(minor) { }

    unsigned HttpVersion::Major() const {
        return major;
    }

    unsigned HttpVersion::Minor() const {
        return minor;
    }
}
}