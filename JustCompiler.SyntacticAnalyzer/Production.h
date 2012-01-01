#pragma once

#include "NonTerminal.h"
#include "SymbolString.h"
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    class Production {
    public:
        Production(boost::shared_ptr<NonTerminal> left, const SymbolString& right);

        boost::shared_ptr<NonTerminal> Left() const;
        SymbolString Right() const;

        bool ToEmpty() const;
    private:
        boost::shared_ptr<NonTerminal> left;
        SymbolString right;
    };
}
}
}