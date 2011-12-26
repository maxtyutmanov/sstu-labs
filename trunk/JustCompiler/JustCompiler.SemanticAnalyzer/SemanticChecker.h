#pragma once

#include "SemanticError.h"
#include <Identifier.h>
#include <SyntaxDirectedParser.h>
#include "SymbolTable.h"
#include <vector>
#include <map>

namespace JustCompiler {
namespace SemanticAnalyzer {

    struct SemanticCheckerOutput {
        PSymbolTable symbolTable;
        std::vector<PSemanticError> errors;
    };

    class SemanticChecker {
    public:
        SemanticCheckerOutput Check(const SyntacticAnalyzer::ParseTree parseTree);

        
    private:
        PSymbolTable CreateSymbolTable(const SyntacticAnalyzer::ParseTree parseTree);

        void FindUndeclaredIdentifiers(
            const SyntacticAnalyzer::PParseTreeNode node, 
            const PSymbolTable symbolTable, 
            std::vector<PSemanticError>& errors);
    };

}
}