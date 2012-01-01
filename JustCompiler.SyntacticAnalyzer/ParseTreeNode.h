#pragma once

#include "Symbol.h"
#include <Token.h>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {

    class ParseTreeNode;
    typedef boost::shared_ptr<ParseTreeNode> PParseTreeNode;

    class ParseTreeNode {
    public:
        typedef std::vector<PParseTreeNode> ChildrenCollection;
        typedef ChildrenCollection::const_iterator ChildrenConstIterator;

        ParseTreeNode() {}

        //ctor
        ParseTreeNode(
            JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::PSymbol symbol);
        //ctor
        ParseTreeNode(
            JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::PSymbol symbol,
            boost::shared_ptr<JustCompiler::LexicalAnalyzer::Token> token);

        JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::PSymbol GetSymbol() const;
        boost::shared_ptr<JustCompiler::LexicalAnalyzer::Token> GetToken() const;

        const ChildrenCollection& Children() const {
            return children;
        }

        ChildrenConstIterator GetChildrenIterator() const;
        void AddChildNode(PParseTreeNode childNode);

        void SetToken(JustCompiler::LexicalAnalyzer::PToken token) {
            this->token = token;
        }

        std::vector<PParseTreeNode> GetChildren(bool (*pred)(const PParseTreeNode), bool fullyRecursive);
    private:
        void GetChildrenHelper(bool (*pred)(const PParseTreeNode), std::vector<PParseTreeNode>& result);

        JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::PSymbol symbol;
        boost::shared_ptr<JustCompiler::LexicalAnalyzer::Token> token;
        ChildrenCollection children;
    };
}
}