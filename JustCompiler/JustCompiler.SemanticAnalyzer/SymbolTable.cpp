#include "SymbolTable.h"

using namespace JustCompiler::LexicalAnalyzer::Tokens;
using namespace std;

namespace JustCompiler {
namespace SemanticAnalyzer {

    void SymbolTable::AddEntry(PIdentifier id) {
        tableInternal[id->GetName()] = id;
    }

    bool SymbolTable::HasEntry(const std::string& name) const {
        return tableInternal.find(name) != tableInternal.cend();
    }

    PIdentifier SymbolTable::GetEntry(const std::string& name) const {
        map<string, PIdentifier>::const_iterator foundIt = tableInternal.find(name);

        if (foundIt != tableInternal.cend()) {
            return foundIt->second;
        }
    }
}
}