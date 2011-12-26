#pragma once

#include <Terminal.h>
#include <string>

namespace JustCompiler {
namespace ParserGrammar {

    class TerminalWithDesc : public JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Terminal {
    public:
        TerminalWithDesc(int tokenTag, const std::string& desc) 
            :JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Terminal(tokenTag) {

            this->desc = desc;
        }
    private:
        std::string desc;
    };

}
}