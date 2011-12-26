#pragma once

namespace JustCompiler {
namespace SyntacticAnalyzer {

    struct ErrorClass {
        enum Enum {
            GrammarSpecific,
            TokenExpected,
            UnexpectedEndOfFile,
            TextAfterEndOfProgram,
            UnexpectedToken
        };
    };

}
}