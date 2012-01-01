#include "SyntaxError.h"

namespace JustCompiler {
namespace SyntacticAnalyzer {

    SyntaxError::SyntaxError(int lineNum, int charNum, ErrorClass::Enum errorClass)
        :lineNum(lineNum), charNum(charNum), errorClass(errorClass) {}

    ErrorClass::Enum SyntaxError::GetErrorClass() const {
        return errorClass;
    }

    int SyntaxError::GetLineNum() const {
        return lineNum;
    }

    int SyntaxError::GetCharNum() const {
        return charNum;
    }
}
}