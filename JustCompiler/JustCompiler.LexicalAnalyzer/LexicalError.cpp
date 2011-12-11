#include "LexicalError.h"

namespace JustCompiler {
namespace LexicalAnalyzer {

    LexicalError::LexicalError() {
        //TODO: WTF?
        lineNumber = 0;
        charNumber = 0;
    }

    LexicalError::LexicalError(const int lineNumber, const int charNumber, const int errorCode) {
        this->lineNumber = lineNumber;
        this->charNumber = charNumber;
        this->errorCode = errorCode;
    }

    int LexicalError::GetLineNumber() const {
        return lineNumber;
    }

    int LexicalError::GetCharNumber() const {
        return charNumber;
    }

    int LexicalError::GetErrorCode() const {
        return errorCode;
    }

}
}