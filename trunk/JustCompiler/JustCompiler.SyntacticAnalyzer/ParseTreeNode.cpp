#include "ParseTreeNode.h"

using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;
using namespace JustCompiler::LexicalAnalyzer;

namespace JustCompiler {
namespace SyntacticAnalyzer {

    ParseTreeNode::ParseTreeNode(boost::shared_ptr<Symbol> symbol) 
        : symbol(symbol) {}

    ParseTreeNode::ParseTreeNode(boost::shared_ptr<Symbol> symbol, boost::shared_ptr<Token> token) 
        : symbol(symbol), token(token) {}

    boost::shared_ptr<Symbol> ParseTreeNode::GetSymbol() const {
        return symbol;
    }

    boost::shared_ptr<Token> ParseTreeNode::GetToken() const {
        return token;
    }

    ParseTreeNode::ChildrenConstIterator ParseTreeNode::GetChildrenIterator() const {
        return children.cbegin();
    }

    void ParseTreeNode::AddChildNode(boost::shared_ptr<ParseTreeNode> childNode) {
        children.push_back(childNode);
    }
}
}