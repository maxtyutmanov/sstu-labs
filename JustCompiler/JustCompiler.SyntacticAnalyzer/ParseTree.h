#pragma once

#include "ParseTreeNode.h"

namespace JustCompiler {
namespace SyntacticAnalyzer {

    class ParseTree {
    public:
        ParseTree(PParseTreeNode root);

        PParseTreeNode GetRoot() const;
    private:
        PParseTreeNode root;
    };

}
}