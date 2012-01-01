#pragma once

#include <Terminal.h>
#include <string>

namespace JustCompiler {
namespace ParserGrammar {

    class TerminalWithDesc;
    typedef boost::shared_ptr<TerminalWithDesc> PTerminalWithDesc;

    class TerminalWithDesc : public JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Terminal {
    public:
        TerminalWithDesc(int tokenTag, const std::string& desc) 
            :JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Terminal(tokenTag) {

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