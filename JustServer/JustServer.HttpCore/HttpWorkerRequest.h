#ifndef HTTPWORKERREQUEST_H
#define HTTPWORKERREQUEST_H

#include <map>
#include <string>
using std::map;
using std::wstring;
using std::string;

typedef HttpHeadersCollection map<string, string>;

//Intermediate representation of http message for carrying it between layers
class HttpWorkerRequest {
public:
    HttpWorkerRequest();

    void SetRequestString(const string& requestString);
    void AddHeader(const string& name, const string& value);
    void AppendToBody(const wstring& bodyPart);

    const string& GetRequestString() const;
    const HttpHeadersCollection& GetHeaders() const;
    const wstring& GetBody() const;
private:
    HttpHeadersCollection headers;
};

#endif