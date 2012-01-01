#pragma once

#include <Identifier.h>
#include "SemanticError.h"

#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SemanticAnalyzer {
namespace Errors {

    class UndeclaredIdentifier;
    typedef boost::shared_ptr<UndeclaredIdentifier> PUndeclaredIdentifier;

    class UndeclaredIdentifier : public SemanticError {
    public:
        UndeclaredIdentifier(int lineNum, int charNum, LexicalAnalyzer::Tokens::PIdentifier id)
            : SemanticError(SemanticErrorCode::UndeclaredIdentifier, lineNum, charNum), id(id) {}

        LexicalAnalyzer::Tokens::PIdentifier GetId() const {
            return id;
        }
    private:
        LexicalAnalyzer::Tokens::PIdentifier id;
    };

}
}
}