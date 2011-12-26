#pragma once

#include <vector>
#include "Symbol.h"
#include "Terminal.h"
#include "NonTerminal.h"
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    class SymbolString : public std::vector<PSymbol> {
    public:
        SymbolString() {}

        SymbolString(PSymbol symbol) {
            this->push_back(symbol);
        }
        
        SymbolString(PNonTerminal symbol) {
            this->push_back(symbol);
        }

        SymbolString(PTerminal symbol) {
            this->push_back(symbol);
        }

        virtual ~SymbolString() {}
        bool operator == (const SymbolString& right) const;
        bool operator < (const SymbolString& right) const;
        bool ContainsSymbol(const PSymbol symbol) const;
        int FindSymbol(const PSymbol symbol) const;
    private:
        int Compare(const SymbolString& right) const;
    };

}
}
}