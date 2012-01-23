#pragma once

#include "Symbol.h"
#include "Production.h"
#include "SymbolAttribute.h"
#include <Token.h>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {

    class ParseTreeNode;
    typedef boost::shared_ptr<ParseTreeNode> PParseTreeNode;

    class NodePredicate {
    public:
        virtual bool operator() (const ParseTreeNode* node) const = 0;
    };

    class ParseTreeNode {
    public:
        typedef std::vector<PParseTreeNode> ChildrenCollection;
        typedef ChildrenCollection::const_iterator ChildrenConstIterator;

        //ctor
        ParseTreeNode(
            PParseTreeNode parent,
            JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::PSymbol symbol);

        ParseTreeNode(
            JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::PSymbol symbol);
        
        //getters/setters
        JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::PSymbol GetSymbol() const;
        JustCompiler::LexicalAnalyzer::PToken GetToken() const;
        void SetToken(JustCompiler::LexicalAnalyzer::PToken token);
        //gets the pointer to the production that generated children of this node
        JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Production* GetProduction() const;
        //sets the pointer to production that generated children of this node
        void SetProduction(const JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Production* pProduction);
        const ChildrenCollection& Children() const;
        PParseTreeNode Parent() const;
        PParseTreeNode FirstParent(const NodePredicate& predicate) const;
        PParseTreeNode FirstChild(const NodePredicate& predicate) const;
        bool Is(const NodePredicate& predicate) const;

        std::vector<PParseTreeNode> GetChildren(const NodePredicate& pred, bool fullyRecursive) const;
        void AddChildNode(PParseTreeNode childNode);

        PParseTreeNode operator[](int childIndex) const;

        void SetAttribute(const std::string& key, PSymbolAttribute value);
        bool HasAttribute(const std::string& key) const;
        PSymbolAttribute GetAttribute(const std::string& key) const;

        bool IsEmpty() const;
        
        template<typename T>
        boost::shared_ptr<T> GetTypedAttribute(const std::string& key) const {
            PSymbolAttribute attr = GetAttribute(key);

            boost::shared_ptr<T> typedAttr = boost::dynamic_pointer_cast<T, SymbolAttribute>(attr);

            assert(typedAttr.get() != NULL);

            return typedAttr;
        }
    private:
        void GetChildrenHelper(const NodePredicate& pred, std::vector<PParseTreeNode>& result) const;

        JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::PSymbol symbol;
        JustCompiler::LexicalAnalyzer::PToken token;
        const JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::Production* pProduction;
        std::map<std::string, PSymbolAttribute> attributes;
        ChildrenCollection children;
        PParseTreeNode parent;
        
    };
}
}