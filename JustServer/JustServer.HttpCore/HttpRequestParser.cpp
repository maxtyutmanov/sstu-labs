#include "HttpRequestParser.h"
#include "MessageParseError.h"
#include "Uri.h"
#include "HttpVersion.h"
#include <HttpTextToken.h>
#include <HttpVersionToken.h>
#include <UriToken.h>
#include <HeaderToken.h>
#include <TokenTag.h>

using namespace JustServer::HttpGrammar;
using namespace JustServer::HttpGrammar::Tokens;
using namespace std;

namespace JustServer {
namespace Http {

    HttpRequest HttpRequestParser::ParseRequest(const std::vector<boost::shared_ptr<Token>>& requestTokens) const {
        //3 tokens: http verb, uri, version
        if (requestTokens.size() < 3) {
            throw MessageParseError("Not enough tokens in HTTP request");
        }

        if (requestTokens[0]->GetTag() == TokenTag::HttpVerb) {
            //TODO: runtime errors may occur here! this is unsafe cast. Use dynamic_cast instead
            HttpTextToken* pVerbToken = (HttpTextToken *)(requestTokens[0].get());
            string verb = pVerbToken->GetText();

            if (requestTokens[1]->GetTag() == TokenTag::Uri) {
                UriToken* pUriToken = (UriToken *)(requestTokens[1].get());
                //TODO: custom port
                Uri uri(pUriToken->GetScheme(), pUriToken->GetHost(), pUriToken->GetAbsolutePath(), pUriToken->GetQuery());

                if (pUriToken->GetPort() != UriToken::UnspecifiedPort) {
                    uri = Uri(pUriToken->GetScheme(), pUriToken->GetHost(), pUriToken->GetAbsolutePath(), pUriToken->GetPort(), pUriToken->GetQuery());
                }

                if (requestTokens[2]->GetTag() == TokenTag::HttpVersion) {
                    HttpVersionToken* pVersionToken = (HttpVersionToken *)(requestTokens[2].get());
                    HttpVersion version(pVersionToken->GetMajor(), pVersionToken->GetMinor());

                    HeadersCollection headers;
                    int currentIndex = 3;

                    while (true) {
                        if (currentIndex >= requestTokens.size() ||
                            requestTokens[currentIndex]->GetTag() != TokenTag::Header) {
                            break;
                        }

                        HeaderToken* pHeaderToken = (HeaderToken*)(requestTokens[currentIndex].get());
                        headers.push_back(NameValuePair(pHeaderToken->GetName(), pHeaderToken->GetValue()));

                        ++currentIndex;
                    }

                    //there is a body in this request
                    if (currentIndex < requestTokens.size()) {
                        if (requestTokens[currentIndex]->GetTag() == TokenTag::Body) {
                            HttpTextToken* pBodyToken = (HttpTextToken*)(requestTokens[currentIndex].get());
                            string body = pBodyToken->GetText();

                            return HttpRequest(verb, uri, version, headers, body);
                        }
                    }
                    else {
                        //there's no body in request

                        return HttpRequest(verb, uri, version, headers, "");
                    }
                }
            }
        }

        throw MessageParseError("Wrong format of HTTP message");
    }

}
}