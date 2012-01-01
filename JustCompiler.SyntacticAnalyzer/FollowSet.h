#pragma once

#include "NonTerminal.h"
#include "Terminal.h"
#include <boost/shared_ptr.hpp>
#include <vector>

namespace JustCompiler {
namespace SyntacticAnalyzer {

    class FollowSet {
    public:
        FollowSet(boost::shared_ptr<JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::NonTerminal> source)
            :source(source) {}

        boost::shared_ptr<JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::NonTerminal> GetSource() const {
            return source;
        }

        void AddFollow(boost::shared_ptr<JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Terminal> terminal) {
            setInternal.push_back(terminal);
        }

        const std::vector<boost::shared_ptr<JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Terminal>>& Set() const {
            return setInternal;
        }
    private:
        boost::shared_ptr<JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::NonTerminal> source;
        std::vector<boost::shared_ptr<JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Terminal>> setInternal;
    };

}
}