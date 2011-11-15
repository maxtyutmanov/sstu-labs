#include "HttpMessage.h"
#include "HeaderNotFoundException.h"
using namespace std;
using JustServer::Utility::NameValuePair;

namespace JustServer {
namespace Http {

    HttpMessage::HttpMessage(const HttpVersion& httpVersion, const HeadersCollection& headers, const string& body)
        :httpVersion(httpVersion), headers(headers), body(body) {}

    HttpVersion HttpMessage::GetHttpVersion() const {
        return httpVersion;
    }

    bool HttpMessage::HasHeader(const string& name) const {
        vector<NameValuePair>::const_iterator foundIt;

        for (foundIt = headers.begin(); foundIt != headers.end(); ++foundIt) {
            if (foundIt->name == name) {
                return true;
            }
        }

        return false;
    }

    string HttpMessage::GetHeaderValue(const string& name) const {
        vector<NameValuePair>::const_iterator foundIt;

        for (foundIt = headers.begin(); foundIt != headers.end(); ++foundIt) {
            if (foundIt->name == name) {
                return foundIt->value;
            }
        }

        throw HeaderNotFoundException(name);
    }

    string HttpMessage::GetBody() const {
        return body;
    }
}
}