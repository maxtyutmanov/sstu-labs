#include "ParseTreeDirectIterator.h"

using namespace JustCompiler::SyntacticAnalyzer;
using namespace std;

namespace JustCompiler {
namespace CodeGeneration {

    vector<TraverseStepInfo> ParseTreeDirectIterator::Iterate(const ParseTree parseTree) {
        vector<TraverseStepInfo> result;

        IterateHelper(parseTree.GetRoot(), result);

        return result;
    }

    void ParseTreeDirectIterator::IterateHelper(const JustCompiler::SyntacticAnalyzer::PParseTreeNode node, std::vector<TraverseStepInfo>& result) {
        TraverseStepInfo tun;
        tun.node = node;
        tun.stepType = TraverseStepType::Tunneling;
        result.push_back(tun);

        for (size_t i = 0; i < node->Children().size(); ++i) {
            IterateHelper(node->Children()[i], result);
        }

        TraverseStepInfo bubl;
        bubl.node = node;
        bubl.stepType = TraverseStepType::Bubbling;
        result.push_back(bubl);
    }
}
}