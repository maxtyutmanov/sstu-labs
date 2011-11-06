#ifndef HTTP_MESSAGE_GRAMMAR_H
#define HTTP_MESSAGE_GRAMMAR_H

#include <Global.h>
#include <Lexer.h>
#include <FaState.h>
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

namespace JustServer {
namespace HttpGrammar {
    
    class HttpMessageGrammar {
    public:
        static auto_ptr<Lexer> CreateLexer();
    };

}
}

#endif