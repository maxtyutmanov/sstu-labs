#pragma once

#include <boost/shared_ptr.hpp>
#include "SemanticErrorCode.h"

namespace JustCompiler {
namespace SemanticAnalyzer {

    class SemanticError;
    typedef boost::shared_ptr<SemanticError> PSemanticError;

    class SemanticError {
    public:
        SemanticError(SemanticErrorCode::Enum errorCode, int lineNum, int charNum) 
            : errorCode(errorCode), lineNum(lineNum), charNum(charNum) {
        }

        virtual int ErrorCode() const {
            return errorCode;
        }

        int LineNum() const {
            return lineNum;
        }

        int CharNum() const {
            return charNum;
        }
    private:
        SemanticErrorCode::Enum errorCode;
        int lineNum;
        int charNum;
    };

}
}