#ifndef HTTPWORKERREQUEST_H
#define HTTPWORKERREQUEST_H

#include <map>
#include <string>
#include <memory>

namespace JustServer {
namespace Http {

    using std::map;
    using std::wstring;
    using std::string;
    using std::auto_ptr;

    typedef std::map<std::string, std::wstring> HttpHeadersCollection;

    //Intermediate representation of http message for carrying it between subsystems
    class HttpWorkerRequest {
    public:
        void SetRequestString(const string& requestString);
        string GetRequestString() const;

        void SetHeader(const string& name, const wstring& value);
        bool TryGetHeader(const string& name, auto_ptr<wstring> headerValue) const;

        //not decoded body of HTTP message (just a bunch of raw bytes)
        string GetBody() const;
        void AppendToBody(const string& bodyPart);
    private:
        HttpHeadersCollection headers;
        string requestString;
        string body;
    };

}
}

#endif