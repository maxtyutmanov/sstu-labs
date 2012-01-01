#include "GrammarSpecificError.h"

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace Errors {

    GrammarSpecificError::GrammarSpecificError(int lineNum, int charNum, int errorCode)
        :SyntaxError(lineNum, charNum, ErrorClass::GrammarSpecific), errorCode(errorCode) {}

    int GrammarSpecificError::GetErrorCode() const {
        return errorCode;
    }
}
}
}