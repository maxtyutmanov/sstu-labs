#pragma once

#include <NonTerminal.h>
#include <string>

namespace JustCompiler {
namespace ParserGrammar {

    class NonTerminalWithDesc;
    typedef boost::shared_ptr<NonTerminalWithDesc> PNonTerminalWithDesc;

    class NonTerminalWithDesc : public JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::NonTerminal {
    public:
        NonTerminalWithDesc(int tag, const std::string& desc) 
            :JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::NonTerminal(tag) {

            this->desc = desc;
        }

        std::wstring GetDesc() const {
            std::wstring result;

            for (size_t i = 0; i < desc.size(); ++i) {
                result.push_back(desc[i]);
            }

            return result;
        }
    private:
        std::string desc;
    };

}
}