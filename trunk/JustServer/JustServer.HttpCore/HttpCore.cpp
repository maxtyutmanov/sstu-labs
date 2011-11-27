#include "HttpCore.h"
#include <HttpRequestGrammar.h>
#include "HttpResponse.h"
#include "MessageParseError.h"
#include <Lexer.h>
#include <TokenTag.h>
#include <HttpVersionToken.h>

using JustServer::HttpGrammar::HttpRequestGrammar;
using JustServer::HttpGrammar::TokenTag;
using namespace JustServer::HttpGrammar::Tokens;

namespace JustServer {
namespace Http {

    HttpCore::HttpCore(const std::wstring& physicalPath, boost::shared_ptr<JustServer::Http::Security::ISecurityModule> securityModule)
        : physicalPath(physicalPath), securityModule(securityModule) {}

    void HttpCore::AddHttpHandler(shared_ptr<IHttpHandler> handler) {
        httpHandlers.push_back(handler);
    }

    auto_ptr<HttpResponse> HttpCore::HandleRequest(auto_ptr<IInputBuffer> pInputBuffer) const {
        //create and setup the lexer for analyzing text input

        //TODO: should be optimized
        auto_ptr<Lexer> pHttpLexer(HttpRequestGrammar::CreateLexer());
        pHttpLexer->SetInput(pInputBuffer);

        //get tokenized HTTP message

        LexerOutput lexerOutput = pHttpLexer->Tokenize();

        vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
        vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

        bool requestIsInvalid = errors.size() > 0;

        if (requestIsInvalid) {
            //in this case we've got to respond with 400: Bad Request
            return OnInvalidRequest(tokens);
        }
        else {
            //there shouldn't be any exceptions here. But we've got to add exception handling anyway
            //TODO: exception handling
            HttpRequest httpRequest = requestParser.ParseRequest(tokens);
            
            httpRequest.SetApplicationPath(this->physicalPath);

            securityModule->AuthenticateRequest(httpRequest);

            //TODO: this is bad. Security module shouldn't return any response

            auto_ptr<HttpResponse> authorizationResponse = securityModule->AuthorizeRequest(httpRequest);

            if (authorizationResponse.get() != NULL) {
                return authorizationResponse;
            }

            //here we've got to select first appropriate IHttpHandler and
            //pass HttpRequest object to it to generate response

            IHttpHandler* pSelectedHandler = NULL;

            if (TryPickHandler(httpRequest, &pSelectedHandler)) {
                return pSelectedHandler->HandleRequest(httpRequest);
            }
            else {
                //responding with 404 Not Found
                return OnHandlerNotFound(httpRequest);
            }
        }
    }

    bool HttpCore::TryPickHandler(const HttpRequest& httpRequest, IHttpHandler** ppHandler) const {
        vector<shared_ptr<IHttpHandler>>::const_iterator handlersIt;

        for (handlersIt = httpHandlers.begin(); handlersIt != httpHandlers.end(); ++handlersIt) {
            if ((*handlersIt)->CanHandleRequest(httpRequest)) {
                *ppHandler = handlersIt->get();
                return true;
            }
        }

        return false;
    }

    auto_ptr<HttpResponse> HttpCore::OnInvalidRequest(const vector<shared_ptr<Token>>& tokens) const {
        vector<shared_ptr<Token>>::const_iterator tokensIt;

        HttpVersionToken* pHttpVersionToken = NULL;

        for (tokensIt = tokens.begin(); tokensIt != tokens.end(); ++tokensIt) {
            if ((*tokensIt)->GetTag() == TokenTag::HttpVersion) {
                pHttpVersionToken = dynamic_cast<HttpVersionToken*>(tokensIt->get());
                break;
            }
        }

        //HTTP/1.1 is used by default. I know this is bad to hardcode it here...
        HttpVersion httpVersion(1, 1);

        if (pHttpVersionToken != NULL) {
            httpVersion = HttpVersion(pHttpVersionToken->GetMajor(), pHttpVersionToken->GetMinor());
        }

        auto_ptr<HttpResponse> httpResponse(new HttpResponse(httpVersion));
        
        httpResponse->AppendToResponseBody("<html><head><title>Error</title></head><body><h1 style=\"color:#FF0000\">400 Bad Request</h1></body></html>");
        httpResponse->SetStatusCode(400);
        httpResponse->SetHeader("connection", "close");

        return httpResponse;
    }

    auto_ptr<HttpResponse> HttpCore::OnHandlerNotFound(const HttpRequest& httpRequest) const {
        auto_ptr<HttpResponse> httpResponse(new HttpResponse(httpRequest.GetHttpVersion()));

        httpResponse->AppendToResponseBody("<html><head><title>Error</title></head><body><h1 style=\"color:#FF0000\">404 Not Found</h1></body></html>");
        httpResponse->SetStatusCode(404);
        httpResponse->SetHeader("connection", "close");

        return httpResponse;
    }
}
}