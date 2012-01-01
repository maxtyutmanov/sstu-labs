#pragma once

#include "Terminal.h"
#include "NonTerminal.h"
#include "Production.h"
#include "ParserTableKey.h"
#include "ParserTableEntry.h"
#include "FirstFunction.h"
#include "FollowFunction.h"
#include "Grammar.h"
#include <boost/shared_ptr.hpp>
#include <vector>
#include <map>

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    class ParserTable {
    public:
        ParserTable(const Grammar& grammar, FirstFunction& first, FollowFunction& follow);

        ParserTableEntry GetEntry(int nonTerminalTag, int terminalTag) const;

        std::vector<int> GetExpectedTerminals(int nonTerminalTag) const;
    private:
        void AddEntry(
            int nonTerminalTag,
            int terminalTag,
            const Production& production);

        void AddEntry(
            int nonTerminalTag,
            int terminalTag,
            int errorCode);

        std::map<ParserTableKey, ParserTableEntry> tableInternal;
    };

}
}
}