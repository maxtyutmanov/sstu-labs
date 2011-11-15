#ifndef HTTP_REQUEST_PARSER_H
#define HTTP_REQUEST_PARSER_H

#include <Token.h>
#include "HttpRequest.h"
#include <vector>
#include <boost/shared_ptr.hpp>

namespace JustServer {
namespace Http {

    class HttpRequestParser {
    public:
        HttpRequest ParseRequest(const std::vector<boost::shared_ptr<Token>>& requestTokens) const;
    };

}
}

#endif