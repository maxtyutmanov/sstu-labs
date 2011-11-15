#include "HttpCore.h"
#include <HttpRequestGrammar.h>
#include "MessageParseError.h"

using JustServer::HttpGrammar::HttpRequestGrammar;

namespace JustServer {
namespace Http {

    HttpCore::HttpCore() {
        pHttpLexer = HttpRequestGrammar::CreateLexer();
    }

    auto_ptr<HttpResponse> HttpCore::HandleRequest(auto_ptr<IInputBuffer> pInputBuffer) {
        pHttpLexer->SetInput(pInputBuffer);

        LexerOutput lexerOutput = pHttpLexer->Tokenize();

        vector<shared_ptr<Token>> tokens = lexerOutput.get<0>();
        vector<shared_ptr<LexicalError>> errors = lexerOutput.get<1>();

        if (errors.size() > 0) {
            throw MessageParseError("Errors detected during the lexical analysis of HTTP request");
        }

        HttpRequest httpRequest = requestParser.ParseRequest(tokens);
    }
}
}