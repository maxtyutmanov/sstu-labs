#include "Grammar.h"

using namespace std;

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    Grammar::Grammar(PNonTerminal startSymbol)
        : startSymbol(startSymbol) { }

    void Grammar::AddNonTerminal(const string& name, PNonTerminal nonTerminal) {
        nonTerminalsMap[name] = nonTerminal;
        nonTerminals.push_back(nonTerminal);
    }

    void Grammar::AddTerminal(const string& name, PTerminal terminal) {
        terminalsMap[name] = terminal;
        terminals.push_back(terminal);
    }

    Production& Grammar::AddProduction(const Production& production) {
        productions.push_back(production);

        return productions.back();
    }

    void Grammar::SetStartSymbol(PNonTerminal startSymbol) {
        this->startSymbol = startSymbol;
    }

    const vector<PNonTerminal>& Grammar::NonTerminals() const {
        return nonTerminals;
    }

    const vector<PTerminal>& Grammar::Terminals() const {
        return terminals;
    }

    const vector<Production>& Grammar::Productions() const {
        return productions;
    }

    PNonTerminal Grammar::StartSymbol() const {
        return startSymbol;
    }

    PNonTerminal Grammar::N(const string& name) const {
        map<string, PNonTerminal>::const_iterator found = nonTerminalsMap.find(name);

        assert(found != nonTerminalsMap.cend());

        return found->second;
    }

    PTerminal Grammar::T(const string& name) const {
        map<string, PTerminal>::const_iterator found = terminalsMap.find(name);

        assert(found != terminalsMap.cend());

        return found->second;
    }
}
}
}