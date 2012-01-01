#pragma once

#include "IParser.h"
#include "Grammar.h"
#include "ParserTable.h"
#include "SymbolFunction.h"
#include <stack>

namespace JustCompiler {
namespace SyntacticAnalyzer {

    //top-down syntactic analyzer directed by precalculated table
    class SyntaxDirectedParser : public IParser {
    public:
        SyntaxDirectedParser(
            const JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Grammar& grammar,
            const JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::ParserTable& parserTable);

        virtual std::auto_ptr<ParserOutput> Parse(boost::shared_ptr<JustCompiler::LexicalAnalyzer::ITokenStream> tokenStream);
    private:
        //fields
        JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Grammar grammar;
        JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::ParserTable parserTable;
        std::stack<PParseTreeNode> parserStack;
    };

}
}