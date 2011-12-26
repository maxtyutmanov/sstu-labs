#pragma once

#include <NonTerminal.h>
#include <string>

namespace JustCompiler {
namespace ParserGrammar {

    class NonTerminalWithDesc : public JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::NonTerminal {
    public:
        NonTerminalWithDesc(int tag, const std::string& desc) 
            :JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::NonTerminal(tag) {

            this->desc = desc;
        }
    private:
        std::string desc;
    };

}
}