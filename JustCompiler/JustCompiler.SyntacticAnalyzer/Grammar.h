#pragma once

#include "NonTerminal.h"
#include "Terminal.h"
#include "Production.h"
#include <map>
#include <vector>
#include <string>

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    class Grammar {
    public:
        Grammar() {}
        Grammar(PNonTerminal startSymbol);

        void AddNonTerminal(const std::string& name, PNonTerminal nonTerminal);
        void AddTerminal(const std::string& name, PTerminal terminal);
        Production& AddProduction(const Production& production);
        void SetStartSymbol(PNonTerminal startSymbol);

        const std::vector<Production>& Productions() const;
        const std::vector<PNonTerminal>& NonTerminals() const;
        const std::vector<PTerminal>& Terminals() const;
        PNonTerminal StartSymbol() const;

        PNonTerminal N(const std::string& name) const;
        PTerminal T(const std::string& name) const;
    private:
        std::vector<PNonTerminal> nonTerminals;
        std::vector<PTerminal> terminals;
        std::vector<Production> productions;

        std::map<std::string, PNonTerminal> nonTerminalsMap;
        std::map<std::string, PTerminal> terminalsMap;
        PNonTerminal startSymbol;
    };

}
}
}