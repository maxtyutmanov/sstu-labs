#pragma once

#include "SyntaxError.h"
#include <Token.h>
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace Errors {

    class TokenExpected;
    typedef boost::shared_ptr<TokenExpected> PTokenExpected;

    class TokenExpected : public SyntaxError {
    public:
        TokenExpected(int lineNum, int charNum, int expectedTokenTag)
            : SyntaxError(lineNum, charNum, ErrorClass::TokenExpected), expectedTokenTag(expectedTokenTag) {}

        int ExpectedTokenTag() const {
            return expectedTokenTag;
        }
    private:
        int expectedTokenTag;
    };

}
}
}