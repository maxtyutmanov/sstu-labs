#pragma once

#include "ParseTreeNode.h"

using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;

namespace JustCompiler {
namespace SyntacticAnalyzer {

    class CustomNodePredicate : public NodePredicate {
    public:
        CustomNodePredicate(bool (*pred)(const ParseTreeNode*)) {
            assert(pred != NULL);
            this->pred = pred;
        }

        virtual bool operator() (const ParseTreeNode* node) const {
            return pred(node);
        }
    private:
        bool (*pred)(const ParseTreeNode*);
    };

    class NonTerminalTagPredicate : public NodePredicate {
    public:
        NonTerminalTagPredicate(int tag)
            :tag(tag) {}

        virtual bool operator() (const ParseTreeNode* node) const {
            PSymbol symbol = node->GetSymbol();
            assert(symbol.get() != NULL);

            if (symbol->GetType() == SymbolType::NonTerminal) {
                PNonTerminal nonTerminal = boost::dynamic_pointer_cast<NonTerminal, Symbol>(symbol);
                assert(nonTerminal.get() != NULL);
                
                return nonTerminal->GetTag() == tag;
            }
            else {
                return false;
            }
        }
    private:
        int tag;
    };

    class MultipleNonTerminalTagPredicate : public NodePredicate {
    public:
        void AddTag(int tag) {
            allowedTags.push_back(tag);
        }

        virtual bool operator() (const ParseTreeNode* node) const {
            PSymbol symbol = node->GetSymbol();
            assert(symbol.get() != NULL);

            if (symbol->GetType() == SymbolType::NonTerminal) {
                PNonTerminal nonTerminal = boost::dynamic_pointer_cast<NonTerminal, Symbol>(symbol);
                assert(nonTerminal.get() != NULL);

                for (size_t i = 0; i < allowedTags.size(); ++i) {
                    if (nonTerminal->GetTag() == allowedTags[i]) {
                        return true;
                    }
                }

                return false;
            }
        }
    private:
        std::vector<int> allowedTags;
    };

    class TerminalTagPredicate : public NodePredicate {
    public:
        TerminalTagPredicate(int tag)
            :tag(tag) {}

        virtual bool operator() (const ParseTreeNode* node) const {
            PSymbol symbol = node->GetSymbol();
            assert(symbol.get() != NULL);

            if (symbol->GetType() == SymbolType::Terminal) {
                PTerminal terminal = boost::dynamic_pointer_cast<Terminal, Symbol>(symbol);
                assert(terminal.get() != NULL);
                
                return terminal->GetTokenTag() == tag;
            }
            else {
                return false;
            }
        }
    private:
        int tag;
    };

    class MultipleTerminalTagPredicate : public NodePredicate {
    public:
        void AddTag(int tag) {
            allowedTags.push_back(tag);
        }

        virtual bool operator() (const ParseTreeNode* node) const {
            PSymbol symbol = node->GetSymbol();
            assert(symbol.get() != NULL);

            if (symbol->GetType() == SymbolType::Terminal) {
                PTerminal terminal = boost::dynamic_pointer_cast<Terminal, Symbol>(symbol);
                assert(terminal.get() != NULL);

                for (size_t i = 0; i < allowedTags.size(); ++i) {
                    if (terminal->GetTokenTag() == allowedTags[i]) {
                        return true;
                    }
                }

                return false;
            }
        }
    private:
        std::vector<int> allowedTags;
    };
}
}