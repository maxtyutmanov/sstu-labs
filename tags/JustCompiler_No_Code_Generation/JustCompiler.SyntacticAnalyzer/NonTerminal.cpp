#include "NonTerminal.h"

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    NonTerminal::NonTerminal(int tag) 
        :tag(tag) {}

    int NonTerminal::GetTag() const {
        return tag;
    }

    SymbolType::Enum NonTerminal::GetType() const {
        return SymbolType::NonTerminal;
    }

    int NonTerminal::Compare(const Symbol& right) const {
        if (right.GetType() == SymbolType::NonTerminal) {
            NonTerminal& rightAsNT = (NonTerminal&)right;

            return this->GetTag() - rightAsNT.GetTag();
        }
        else {
            return 1;
        }
    }
}
}
}