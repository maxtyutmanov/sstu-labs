#include "HttpWorkerRequest.h"

namespace JustServer {
namespace Http {

    void HttpWorkerRequest::SetRequestString(const string& requestString) {
        this->requestString = requestString;
    }

    string HttpWorkerRequest::GetRequestString() const {
        return requestString;
    }

    void HttpWorkerRequest::SetHeader(const string& name, const wstring& value) {
        headers[name] = value;
    }

    bool HttpWorkerRequest::TryGetHeader(const string& name, auto_ptr<wstring> headerValue) const {
        HttpHeadersCollection::const_iterator found = headers.find(name);

        if (found != headers.end()) {
            //TODO: dynamic allocation, perfomance overhead
            headerValue.reset(new wstring(found->second));
            return true;
        }
        else {
            return false;
        }
    }

    string HttpWorkerRequest::GetBody() const {
        return body;
    }

    void HttpWorkerRequest::AppendToBody(const string& bodyPart) {
        body.reserve(body.size() + bodyPart.size());

        for (size_t i = 0; i < bodyPart.size(); ++i) {
            body.push_back(bodyPart[i]);
        }
    }
}
}