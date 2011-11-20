#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "HttpMessage.h"
#include "ReasonPhraseMapping.h"
#include <vector>
#include <boost/shared_ptr.hpp>

namespace JustServer {
namespace Http {

    //Represents a serializable container for response info
    class HttpResponse : public HttpMessage {
    public:
        HttpResponse(const HttpVersion& httpVersion);

        void SetHeader(const std::string& name, const std::string& value);
        void RemoveHeader(const std::string& name);

        void AppendToResponseBody(const std::string& data);
        void ClearResponseBody();

        void SetContentLength(size_t length);

        void SetStatusCode(int statusCode);
        int GetStatusCode() const;

        std::string Serialize() const;
    private:
        int statusCode;
        static ReasonPhraseMapping reasonPhraseMapping;
    };

}
}

#endif