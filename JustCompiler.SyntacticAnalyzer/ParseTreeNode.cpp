#include "ParseTreeNode.h"

using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;
using namespace JustCompiler::LexicalAnalyzer;
using namespace std;

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

    vector<PParseTreeNode> ParseTreeNode::GetChildren(bool (*pred)(const PParseTreeNode), bool fullyRecursive) {
        vector<PParseTreeNode> result;

        if (fullyRecursive) {
            GetChildrenHelper(pred, result);
        }
        else {
            ChildrenConstIterator childIt;

            for (childIt = children.cbegin(); childIt != children.cend(); ++childIt) {
                if (pred(*childIt)) {
                    result.push_back(*childIt);
                }
            }
        }

        return result;
    }

    void ParseTreeNode::GetChildrenHelper(bool (*pred)(const PParseTreeNode), vector<PParseTreeNode>& result) {
        ChildrenConstIterator childIt;

        for (childIt = children.cbegin(); childIt != children.cend(); ++childIt) {
            if (pred(*childIt)) {
                result.push_back(*childIt);
            }

            childIt->get()->GetChildrenHelper(pred, result);
        }
    }
}
}