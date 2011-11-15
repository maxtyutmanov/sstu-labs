#ifndef HTTPCORE_H
#define HTTPCORE_H

#include "HttpResponse.h"
#include "HttpRequestParser.h"
#include <IInputBuffer.h>
#include <Lexer.h>

namespace JustServer {
namespace Http {

    class HttpCore {
    public:
        HttpCore();

        auto_ptr<HttpResponse> HandleRequest(auto_ptr<IInputBuffer> pInputBuffer);
    private:
        auto_ptr<Lexer> pHttpLexer;
        HttpRequestParser requestParser;
    };

}
}

#endif