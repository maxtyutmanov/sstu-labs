#include "FirstFunction.h"

using namespace std;

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    TerminalSet& FirstFunction::operator()(const SymbolString& key) {
        map<SymbolString, TerminalSet>::iterator foundIt = mapInternal.find(key);

        if (foundIt == mapInternal.end()) {
            mapInternal[key] = TerminalSet();
            foundIt = mapInternal.find(key);
        }

        return foundIt->second;
    }

    void FirstFunction::MarkAsCalculated(const SymbolString& key) {
        if (calculated.find(key) == calculated.end()) {
            calculated.insert(key);
        }
    }

    bool FirstFunction::IsCalculated(const SymbolString& key) const {
        set<SymbolString>::const_iterator found = calculated.find(key);

        if (found != calculated.cend()) {
            return true;
        }
        else {
            return false;
        }
    }

    void FirstFunction::ClearCalculated() {
        calculated.clear();
    }
}
}
}