#pragma once

#include "SyntaxError.h"
#include <Token.h>
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace Errors {

    class UnexpectedToken;
    typedef boost::shared_ptr<UnexpectedToken> PUnexpectedToken;

    class UnexpectedToken : public SyntaxError {
    public:
        UnexpectedToken(int lineNum, int charNum, JustCompiler::LexicalAnalyzer::PToken token, const std::vector<int>& expectedTokenTags)
            : SyntaxError(lineNum, charNum, ErrorClass::UnexpectedToken), token(token), expectedTokenTags(expectedTokenTags) {}

        JustCompiler::LexicalAnalyzer::PToken GetToken() const {
            return token;
        }

        std::vector<int> ExpectedTokenTags() const {
            return expectedTokenTags;
        }
    private:
        JustCompiler::LexicalAnalyzer::PToken token;
        std::vector<int> expectedTokenTags;
    };

}
}
}