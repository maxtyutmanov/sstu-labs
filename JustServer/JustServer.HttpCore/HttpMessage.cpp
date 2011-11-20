#include "HttpMessage.h"
#include "HeaderNotFoundException.h"
#include <iterator>
#include <algorithm>
using namespace std;
using JustServer::Utility::NameValuePair;

namespace JustServer {
namespace Http {

    HttpMessage::HttpMessage(const HttpVersion& httpVersion, const HeadersCollection& headers, const string& body)
        :httpVersion(httpVersion), body(body) {

        HeadersCollection::const_iterator headersIt;

        for (headersIt = headers.begin(); headersIt != headers.end(); ++headersIt) {
            SetHeader(headersIt->name, headersIt->value);
        }
    }

    void HttpMessage::SetHeader(const string& name, const string& value) {
        //transforming header field name to lower case ('cause HTTP header names are case-insensitive)

        string lowerCaseName;
        lowerCaseName.reserve(name.length());

        transform(name.begin(), name.end(), back_inserter(lowerCaseName), ptr_fun<int, int>(tolower));

        headers[lowerCaseName] = value;
    }

    HttpVersion HttpMessage::GetHttpVersion() const {
        return httpVersion;
    }

    bool HttpMessage::HasHeader(const string& name) const {
        map<string, string>::const_iterator foundIt = headers.find(name);

        return foundIt != headers.end();
    }

    string HttpMessage::GetHeaderValue(const string& name) const {
        map<string, string>::const_iterator foundIt = headers.find(name);

        if (foundIt != headers.end()) {
            return foundIt->second;
        }
        else {
            throw HeaderNotFoundException(name);
        }
    }

    string HttpMessage::GetBody() const {
        return body;
    }
}
}