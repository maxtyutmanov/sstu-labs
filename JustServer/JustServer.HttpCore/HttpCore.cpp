#include "HttpCore.h"
#include <HttpRequestGrammar.h>
#include "HttpResponse.h"
#include "MessageParseError.h"
#include <Lexer.h>

using JustServer::HttpGrammar::HttpRequestGrammar;

namespace JustServer {
namespace Http {

    auto_ptr<HttpResponse> HttpCore::HandleRequest(auto_ptr<IInputBuffer> pInputBuffer) {
        auto_ptr<Lexer> pHttpLexer(HttpRequestGrammar::CreateLexer());
        pHttpLexer->SetInput(pInputBuffer);

        LexerOutput lexerOutput = pHttpLexer->Tokenize();

        vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
        vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

        bool invalidRequest = errors.size() > 0;

        auto_ptr<HttpResponse> response;
        string payload;

        if (invalidRequest) {
            response.reset(new HttpResponse(HttpVersion(1, 1)));

            response->SetStatusCode(400);
            payload = "<html><head><title>ERROR!</title></head><body>404 BAD REQUEST</body></html>";
        }
        else {
            HttpRequest httpRequest = requestParser.ParseRequest(tokens);

            response.reset(new HttpResponse(httpRequest.GetHttpVersion()));
            payload = "<html><head><title>Hey, it works!</title></head><body>200 SUCCESS!!!!!!!!!!!!</body></html>";
        }

        response->AppendToResponseBody(payload);
        response->SetContentLength(payload.length());
        response->SetHeader("connection", "close");

        //TODO: stub
        return response;
    }
}
}