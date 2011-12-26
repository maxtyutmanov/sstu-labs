#pragma once

#include "Symbol.h"
#include <vector>
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {

    class SymbolSet {
    public:
        typedef std::vector<JustCompiler::SyntacticAnalyzer::ContextFreeGrammar::PSymbol> SymbolCollection;

        SymbolSet(const SymbolCollection& symbols);

    private:
        SymbolCollection symbols;
    };

}
}