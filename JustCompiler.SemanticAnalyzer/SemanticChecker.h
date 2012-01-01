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
        PSymbolTable CreateSymbolTable(const SyntacticAnalyzer::ParseTree parseTree, SemanticCheckerOutput& output);

        void FindUndeclaredIdentifiers(
            const SyntacticAnalyzer::ParseTree parseTree,
            SemanticCheckerOutput& output);

        static bool IsDeclaration(const SyntacticAnalyzer::PParseTreeNode node);
        static bool IsIdentifier(const SyntacticAnalyzer::PParseTreeNode node);
        static bool IsStmtList(const SyntacticAnalyzer::PParseTreeNode node);
    };

}
}