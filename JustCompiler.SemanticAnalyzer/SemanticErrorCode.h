#pragma once

namespace JustCompiler {
namespace SemanticAnalyzer {

    struct SemanticErrorCode {
        enum Enum {
            UndeclaredIdentifier,
            Redefinition
        };
    };

}
}