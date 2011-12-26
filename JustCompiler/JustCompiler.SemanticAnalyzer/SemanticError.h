#pragma once

#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SemanticAnalyzer {

    class SemanticError;
    typedef boost::shared_ptr<SemanticError> PSemanticError;

    class SemanticError {
    public:
        SemanticError(int errorCode, int lineNum, int charNum) 
            : errorCode(errorCode), lineNum(lineNum), charNum(charNum) {
        }

        int ErrorCode() const {
            return errorCode;
        }

        int LineNum() const {
            return lineNum;
        }

        int CharNum() const {
            return charNum;
        }
    private:
        int errorCode;
        int lineNum;
        int charNum;
    };

}
}