#pragma once

#include <Grammar.h>
#include <map>
#include <string>
#include <vector>

namespace JustCompiler {
namespace ParserGrammar {

    class MyGrammarFactory {
    public:
        static JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Grammar CreateGrammar();

    private:
        static void CreateNonTerminals(JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Grammar& grammar);
        static void CreateTerminals(JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Grammar& grammar);

        static JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Production& AddProduction(
            const std::string& left, 
            const std::string& right, 
            JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Grammar& grammar);

        static void AddNonTerminal(
            const std::string& name,
            int tag,
            JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Grammar& grammar);

        static void AddTerminal(
            const std::string& name,
            int tokenTag,
            JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Grammar& grammar);

        static JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::PSymbol GetSymbol(
            const std::string& name, const JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Grammar& grammar);
    };

}
}