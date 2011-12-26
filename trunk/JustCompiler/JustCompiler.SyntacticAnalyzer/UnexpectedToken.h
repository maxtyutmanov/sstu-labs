#pragma once

#include "SyntaxError.h"
#include <Token.h>
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace Errors {

    class UnexpectedToken : public SyntaxError {
    public:
        UnexpectedToken(int lineNum, int charNum, boost::shared_ptr<JustCompiler::LexicalAnalyzer::Token> token)
            : SyntaxError(lineNum, charNum, ErrorClass::UnexpectedToken), token(token) {}

        boost::shared_ptr<JustCompiler::LexicalAnalyzer::Token> GetToken() const {
            return token;
        }
    private:
        boost::shared_ptr<JustCompiler::LexicalAnalyzer::Token> token;
    };

}
}
}