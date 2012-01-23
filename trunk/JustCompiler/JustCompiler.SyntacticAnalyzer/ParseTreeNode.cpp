#include "ParseTreeNode.h"
#include <SpecialTokenTag.h>

using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;
using namespace JustCompiler::LexicalAnalyzer;
using namespace std;

namespace JustCompiler {
namespace SyntacticAnalyzer {

    ParseTreeNode::ParseTreeNode(PParseTreeNode parent, PSymbol symbol) 
        : parent(parent), symbol(symbol) {}

    ParseTreeNode::ParseTreeNode(PSymbol symbol) 
        : symbol(symbol) {}

    boost::shared_ptr<Symbol> ParseTreeNode::GetSymbol() const {
        return symbol;
    }

    boost::shared_ptr<Token> ParseTreeNode::GetToken() const {
        return token;
    }

    void ParseTreeNode::SetToken(PToken token) {
        this->token = token;
    }

    void ParseTreeNode::SetProduction(const Production* pProduction) {
        this->pProduction = pProduction;
    }

    const ParseTreeNode::ChildrenCollection& ParseTreeNode::Children() const {
        return children;
    }

    PParseTreeNode ParseTreeNode::Parent() const {
        return this->parent;
    }

    PParseTreeNode ParseTreeNode::FirstParent(const NodePredicate& predicate) const {
        if (this->Parent().get() != NULL) {
            if (predicate(this->Parent().get())) {
                return this->Parent();
            }
            else {
                return this->Parent()->FirstParent(predicate);
            }
        }
        else {
            return PParseTreeNode();
        }
    }

    PParseTreeNode ParseTreeNode::FirstChild(const NodePredicate& predicate) const {
        vector<PParseTreeNode> filteredChildren = GetChildren(predicate, false);

        if (filteredChildren.size() != 0) {
            return filteredChildren[0];
        }
        else {
            return PParseTreeNode();
        }
    }

    bool ParseTreeNode::Is(const NodePredicate& predicate) const {
        return predicate(this);
    }

    void ParseTreeNode::AddChildNode(PParseTreeNode childNode) {
        children.push_back(childNode);
    }

    PParseTreeNode ParseTreeNode::operator[](int childIndex) const {
        return children[childIndex];
    }

    void ParseTreeNode::SetAttribute(const std::string& key, PSymbolAttribute value) {
        attributes[key] = value;
    }

    bool ParseTreeNode::HasAttribute(const std::string& key) const {
        map<string, PSymbolAttribute>::const_iterator foundIt = attributes.find(key);

        return foundIt != attributes.cend();
    }

    PSymbolAttribute ParseTreeNode::GetAttribute(const std::string& key) const {
        map<string, PSymbolAttribute>::const_iterator foundIt = attributes.find(key);

        assert(foundIt != attributes.cend());

        return foundIt->second;
    }

    bool ParseTreeNode::IsEmpty() const {
        if (children.size() == 1) {
            PParseTreeNode childNode = children[0];
            PSymbol childSymbol = childNode->GetSymbol();
            assert(childSymbol.get() != NULL);

            if (childSymbol->GetType() == SymbolType::Terminal) {
                PTerminal childTerminal = boost::dynamic_pointer_cast<Terminal, Symbol>(childSymbol);
                assert(childTerminal.get() != NULL);

                return childTerminal->GetTokenTag() == SpecialTokenTag::Empty;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    vector<PParseTreeNode> ParseTreeNode::GetChildren(const NodePredicate& pred, bool fullyRecursive) const {
        vector<PParseTreeNode> result;

        if (fullyRecursive) {
            GetChildrenHelper(pred, result);
        }
        else {
            ChildrenConstIterator childIt;

            for (childIt = children.cbegin(); childIt != children.cend(); ++childIt) {
                if (pred(childIt->get())) {
                    result.push_back(*childIt);
                }
            }
        }

        return result;
    }

    void ParseTreeNode::GetChildrenHelper(const NodePredicate& pred, vector<PParseTreeNode>& result) const {
        ChildrenConstIterator childIt;

        for (childIt = children.cbegin(); childIt != children.cend(); ++childIt) {
            if (pred(childIt->get())) {
                result.push_back(*childIt);
            }

            childIt->get()->GetChildrenHelper(pred, result);
        }
    }
}
}