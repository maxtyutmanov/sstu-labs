#pragma once

#include <Grammar.h>
#include <map>
#include <string>

namespace JustCompiler {
namespace Tests {

    class TestGrammarFactory {
    public:
        static JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Grammar CreateExpressionsGrammar();

        /*static std::map<std::string, JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::PNonTerminal> N;
        static std::map<std::string, JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::PTerminal> T;*/
    private:
        static void CreateNonTerminals(JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Grammar& grammar);
        static void CreateTerminals(JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Grammar& grammar);
        static void ArithmeticExpressions(JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Grammar& grammar);
    };

}
}