#include "ParseTree.h"

namespace JustCompiler {
namespace SyntacticAnalyzer {

    ParseTree::ParseTree(boost::shared_ptr<ParseTreeNode> root) 
        : root(root) { }

    boost::shared_ptr<ParseTreeNode> ParseTree::GetRoot() const {
        return root;
    }
}
}