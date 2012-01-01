#pragma once

#include "SyntaxError.h"

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace Errors {

    class GrammarSpecificError : public SyntaxError {
    public:
        GrammarSpecificError(int lineNum, int charNum, int errorCode);

        int GetErrorCode() const;
    private:
        int errorCode;
    };

}
}
}