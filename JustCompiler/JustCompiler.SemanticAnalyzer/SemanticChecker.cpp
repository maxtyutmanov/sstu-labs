#include "SemanticChecker.h"
#include <NonTerminalTag.h>

using namespace std;
using namespace JustCompiler::SyntacticAnalyzer;
using namespace JustCompiler::LexicalAnalyzer::Tokens;

namespace JustCompiler {
namespace SemanticAnalyzer {

    SemanticCheckerOutput SemanticChecker::Check(const ParseTree parseTree) {
        SemanticCheckerOutput output;
        output.symbolTable = CreateSymbolTable(parseTree);

        FindUndeclaredIdentifiers(parseTree.GetRoot(), output.symbolTable, output.errors);
    }

    PSymbolTable SemanticChecker::CreateSymbolTable(const ParseTree parseTree) {

    }
}
}