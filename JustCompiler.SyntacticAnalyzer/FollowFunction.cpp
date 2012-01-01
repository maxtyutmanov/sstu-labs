#include "FollowFunction.h"

using namespace std;

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    TerminalSet& FollowFunction::operator()(PNonTerminal key) {
        map<int, TerminalSet>::iterator foundIt = mapInternal.find(key->GetTag());

        if (foundIt == mapInternal.end()) {
            mapInternal[key->GetTag()] = TerminalSet();
            foundIt = mapInternal.find(key->GetTag());
        }

        return foundIt->second;
    }

    void FollowFunction::MarkAsCalculated(PNonTerminal key) {
        if (!IsCalculated(key)) {
            calculated.insert(key->GetTag());
        }
    }

    bool FollowFunction::IsCalculated(PNonTerminal key) const {
        return calculated.find(key->GetTag()) != calculated.end();
    }

    void FollowFunction::ClearCalculated() {
        calculated.clear();
    }
}
}
}