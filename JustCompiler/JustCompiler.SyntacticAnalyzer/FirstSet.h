#pragma once

#include "SymbolString.h"
#include "Terminal.h"
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {

    class FirstSet {
    public:
        FirstSet(const JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::SymbolString& source)
            : source(source) {}

        const JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::SymbolString& Source() const {
            return source;
        }

        void AddFirst(boost::shared_ptr<JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Terminal> terminal) {
            setInternal.push_back(terminal);
        }

        const std::vector<boost::shared_ptr<JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Terminal>>& Set() const {
            return setInternal;
        }
    private:
        JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::SymbolString source;
        std::vector<boost::shared_ptr<JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Terminal>> setInternal;
    };

}
}