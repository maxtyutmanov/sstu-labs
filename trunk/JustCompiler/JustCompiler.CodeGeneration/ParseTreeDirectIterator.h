#pragma once

#include <ParseTree.h>
#include <vector>

namespace JustCompiler {
namespace CodeGeneration {

    struct TraverseStepType {
        enum Enum {
            Bubbling,
            Tunneling
        };
    };

    struct TraverseStepInfo {
        JustCompiler::SyntacticAnalyzer::PParseTreeNode node;
        TraverseStepType::Enum stepType;
    };

    class ParseTreeDirectIterator {
    public:
        std::vector<TraverseStepInfo> Iterate(const JustCompiler::SyntacticAnalyzer::ParseTree parseTree);

    private:
        void IterateHelper(const JustCompiler::SyntacticAnalyzer::PParseTreeNode node, std::vector<TraverseStepInfo>& result);
    };

}
}