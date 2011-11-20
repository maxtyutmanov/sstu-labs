#include "ReasonPhraseMapping.h"
#include "UnknownStatusCodeException.h"

using namespace std;

namespace JustServer {
namespace Http {

    ReasonPhraseMapping::ReasonPhraseMapping() {
        mapping[100] = "Continue";
        mapping[101] = "Switching protocols";
        mapping[200] = "OK";
        mapping[201] = "Created";
        mapping[202] = "Accepted";
        mapping[203] = "Non-Authoritative information";
        mapping[204] = "No Content";
        mapping[205] = "Reset Content";
        mapping[206] = "Partial Content";
        mapping[300] = "Multiple Choices";
        mapping[301] = "Moved Permanently";
        mapping[302] = "Found";
        mapping[303] = "See Other";
        mapping[304] = "Not Modified";
        mapping[305] = "Use Proxy";
        mapping[307] = "Temporary Request";
        mapping[400] = "Bad Request";
        mapping[401] = "Unauthorized";
        mapping[402] = "Payment Required";
        mapping[403] = "Forbidden";
        mapping[404] = "Not Found";
        mapping[405] = "Method Not Allowed";
        mapping[406] = "Not Acceptable";
        mapping[407] = "Proxy Authentication Required";
        mapping[408] = "Request Time-Out";
        mapping[409] = "Conflict";
        mapping[410] = "Gone";
        mapping[411] = "Length Required";
        mapping[412] = "Precondition Failed";
        mapping[413] = "Request Entity Too Large";
        mapping[414] = "Request-URI Too Large";
        mapping[415] = "Unsupported Media Type";
        mapping[416] = "Requested range not satisfiable";
        mapping[417] = "Expectation Failed";
        mapping[500] = "Internal Server Error";
        mapping[501] = "Not Impelemented";
        mapping[502] = "Bad Gateway";
        mapping[503] = "Service Unavailable";
        mapping[504] = "Gateway Time-out";
        mapping[505] = "HTTP Version not supported";
    }

    string ReasonPhraseMapping::GetReasonPhrase(int code) const {
        map<int, string>::const_iterator foundIt = mapping.find(code);

        if (foundIt != mapping.end()) {
            return foundIt->second;
        }
        else {
            throw UnknownStatusCodeException(code);
        }
    }

}
}