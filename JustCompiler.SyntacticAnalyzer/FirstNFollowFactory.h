#pragma once

#include "FirstFunction.h"
#include "FollowFunction.h"
#include "Grammar.h"

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    class FirstNFollowFactory {
    public:
        static PFirstFunction GetFirst(const Grammar& grammar);
        static PFollowFunction GetFollow(const Grammar& grammar, PFirstFunction pFirst);

    private:
        static void CalculateFirstForNonTerminal(const Grammar& grammar, const PNonTerminal nonTerminal, FirstFunction& first, bool& addedSomething);
        static void CalculateFirstForSymbolString(const SymbolString& symbolStr, FirstFunction& first);
        static void CalculateFollowForNonTerminal(const Grammar& grammar, const PNonTerminal nonTerminal, FirstFunction& first, FollowFunction& follow, bool& addedSomething);
    };

}
}
}