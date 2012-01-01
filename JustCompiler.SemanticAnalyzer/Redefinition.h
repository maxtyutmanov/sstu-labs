#pragma once

#include <Identifier.h>
#include "SemanticError.h"

#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SemanticAnalyzer {
namespace Errors {

    class Redefinition;
    typedef boost::shared_ptr<Redefinition> PRedefinition;

    class Redefinition : public SemanticError {
    public:
        Redefinition(int lineNum, int charNum, LexicalAnalyzer::Tokens::PIdentifier id)
            : SemanticError(SemanticErrorCode::Redefinition, lineNum, charNum), id(id) {}

        LexicalAnalyzer::Tokens::PIdentifier GetId() const {
            return id;
        }
    private:
        LexicalAnalyzer::Tokens::PIdentifier id;
    };

}
}
}