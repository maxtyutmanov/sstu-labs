#include "HttpResponse.h"
#include <boost/lexical_cast.hpp>
#include <string>
using namespace std;

namespace JustServer {
namespace Http {

    ReasonPhraseMapping HttpResponse::reasonPhraseMapping;

    HttpResponse::HttpResponse(const HttpVersion& httpVersion)
        :HttpMessage(httpVersion, HeadersCollection(), "") {

        //200 is OK (status by default)
        statusCode = 200;
        SetContentLength(0);
    }

    void HttpResponse::SetHeader(const string& name, const string& value) {
        HttpMessage::SetHeader(name, value);
    }

    void HttpResponse::RemoveHeader(const string& name) {
        map<string, string>::const_iterator foundIt = headers.find(name);

        if (foundIt != headers.end()) {
            headers.erase(foundIt);
        }
    }

    void HttpResponse::AppendToResponseBody(const string& data) {
        body.append(data);

        SetContentLength(data.length());
    }

    void HttpResponse::ClearResponseBody() {
        body.clear();
        SetContentLength(0);
    }

    void HttpResponse::SetContentLength(size_t length) {
        HttpMessage::SetHeader("content-length", boost::lexical_cast<string, size_t>(length));
    }

    void HttpResponse::SetStatusCode(int statusCode) {
        this->statusCode = statusCode;
    }

    string HttpResponse::Serialize() const {
        string responseStr;

        //status line

        responseStr.append("HTTP/" + boost::lexical_cast<string, unsigned int>(GetHttpVersion().Major()) + "." + 
            boost::lexical_cast<string, unsigned int>(GetHttpVersion().Minor()) + " ");

        responseStr.append(boost::lexical_cast<string, int>(statusCode) + " ");

        responseStr.append(reasonPhraseMapping.GetReasonPhrase(statusCode));

        responseStr.append("\r\n");

        //headers

        map<string, string>::const_iterator headersIt;

        for (headersIt = headers.begin(); headersIt != headers.end(); ++headersIt) {
            //first it header's name, second is its value

            responseStr.append(headersIt->first + ": " + headersIt->second);
            responseStr.append("\r\n");
        }

        //end of headers
        responseStr.append("\r\n");

        //entity body
        responseStr.append(body);
        
        return responseStr;
    }

    
}
}