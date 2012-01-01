#include "FirstNFollowFactory.h"
#include <SpecialTokenTag.h>

using namespace std;
using JustCompiler::LexicalAnalyzer::SpecialTokenTag;

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    PFirstFunction FirstNFollowFactory::GetFirst(const Grammar& grammar) {
        PFirstFunction pFirst(new FirstFunction());
        PTerminal empty(new Terminal(SpecialTokenTag::Empty));

        FirstFunction& first = *pFirst;

        vector<PTerminal>::const_iterator termIt;

        //for every terminal first(T) = {T}
        for (termIt = grammar.Terminals().cbegin(); termIt != grammar.Terminals().cend(); ++termIt) {
            first(*termIt).Merge(*termIt, true);
            first.MarkAsCalculated(*termIt);
        }

        //A -> empty => add {empty} to first(A)
        vector<Production>::const_iterator prodIt;
        const vector<Production>& allProductions = grammar.Productions();

        for (prodIt = allProductions.cbegin(); prodIt != allProductions.cend(); ++prodIt) {
            if (prodIt->ToEmpty()) {
                first(prodIt->Left()).Merge(empty, true);
            }
        }

        //for every non terminal: X -> Y1Y2Y3...YK
        vector<PNonTerminal>::const_iterator nonTermIt;

        bool addedSomething;

        do {
            addedSomething = false;

            for (nonTermIt = grammar.NonTerminals().cbegin(); nonTermIt != grammar.NonTerminals().cend(); ++nonTermIt) {
                CalculateFirstForNonTerminal(grammar, *nonTermIt, first, addedSomething);
            }
        } while (addedSomething);

        //for the right part of every production
        for (prodIt = grammar.Productions().cbegin(); prodIt != grammar.Productions().cend(); ++prodIt) {
            if (!first.IsCalculated(prodIt->Right())) {
                CalculateFirstForSymbolString(prodIt->Right(), first);
            }
        }

        return pFirst;
    }

    void FirstNFollowFactory::CalculateFirstForNonTerminal(const Grammar& grammar, const PNonTerminal nonTerminal, FirstFunction& first, bool& addedSomething) {
        vector<Production>::const_iterator prodIt;

        for (prodIt = grammar.Productions().cbegin(); prodIt != grammar.Productions().cend(); ++prodIt) {
            //for every production that has this non terminal on the left side
            if (prodIt->Left()->GetTag() == nonTerminal->GetTag()) {
                SymbolString rightStr = prodIt->Right();

                SymbolString::const_iterator rightIt;

                //calculate first sets for all the symbols on the right side of the production
                for (rightIt = rightStr.cbegin(); rightIt != rightStr.end(); ++rightIt) {

                    //copy the whole first set from the symbol on the right side of the production
                    TerminalSet& firstSetToCopy = first(*rightIt);

                    bool hasEmptySymbol = false;

                    for (int i = 0; i < firstSetToCopy.size(); ++i) {
                        if (first(nonTerminal).Merge(firstSetToCopy[i], true)) {
                            addedSomething = true;
                        }

                        if (firstSetToCopy[i].get()->GetTokenTag() == SpecialTokenTag::Empty) {
                            hasEmptySymbol = true;
                        }
                    }

                    if (!hasEmptySymbol) {
                        break;
                    }
                }
            }
        }

        first.MarkAsCalculated(nonTerminal);
    }

    void FirstNFollowFactory::CalculateFirstForSymbolString(const SymbolString& symbolStr, FirstFunction& first) {
        SymbolString::const_iterator it;

        for (it = symbolStr.cbegin(); it != symbolStr.cend(); ++it) {
            assert(first.IsCalculated(*it));
            first(symbolStr).Merge(first(*it), false);

            if (!first(*it).Contains(SpecialTokenTag::Empty)) {
                break;
            }
        }

        first.MarkAsCalculated(symbolStr);
    }

    PFollowFunction FirstNFollowFactory::GetFollow(const Grammar& grammar, PFirstFunction pFirst) {
        PFollowFunction pFollow(new FollowFunction());
        FollowFunction& follow = *pFollow;
        FirstFunction& first = *pFirst;
        
        vector<PNonTerminal>::const_iterator nonTermIt;

        //follow(S).add($)
        follow(grammar.StartSymbol()).Merge(PTerminal(new Terminal(SpecialTokenTag::Eof)), false);

        bool addedSomething;

        do {
            addedSomething = false;

            for (nonTermIt = grammar.NonTerminals().cbegin(); nonTermIt != grammar.NonTerminals().cend(); ++nonTermIt) {
                NonTerminal* ptr = nonTermIt->get();

                CalculateFollowForNonTerminal(grammar, *nonTermIt, first, follow, addedSomething);
            }
        } while (addedSomething);

        return pFollow;
    }

    void FirstNFollowFactory::CalculateFollowForNonTerminal(const Grammar& grammar, const PNonTerminal nonTerminal,
        FirstFunction& first, FollowFunction& follow, bool& addedSomething) {

        vector<Production>::const_iterator prodIt;

        //A->aBb
        for (prodIt = grammar.Productions().cbegin(); prodIt != grammar.Productions().cend(); ++prodIt) {
            SymbolString right = prodIt->Right();

            //find the index of B
            int nonTermIndex = -1;

            while ((nonTermIndex = right.FindSymbol(nonTerminal, nonTermIndex + 1)) != -1) {
                //build b
                SymbolString followStr;

                for (size_t i = nonTermIndex + 1; i < right.size(); ++i) {
                    followStr.push_back(right[i]);
                }

                //calculate the first function, if needed
                if (!first.IsCalculated(followStr)) {
                    CalculateFirstForSymbolString(followStr, first);
                }

                if (follow(nonTerminal).Merge(first(followStr), false)) {
                    addedSomething = true;
                }

                //A->aB
                if ((nonTermIndex == (right.size() - 1) || first(followStr).Contains(SpecialTokenTag::Empty)) && prodIt->Left() != nonTerminal) {
                    //CalculateFollowForNonTerminal(grammar, prodIt->Left(), first, follow, addedSomething);

                    if (follow(nonTerminal).Merge(follow(prodIt->Left()), false)) {
                        addedSomething = true;
                    }
                }
            }
        }

        follow.MarkAsCalculated(nonTerminal);
    }
}
}
}