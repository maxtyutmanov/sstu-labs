#pragma once

#include "SymbolString.h"
#include "TerminalSet.h"
#include "NonTerminal.h"
#include <boost/shared_ptr.hpp>
#include <map>
#include <set>

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    class FirstFunction {
    public:
        TerminalSet& operator()(const SymbolString& key);
        void MarkAsCalculated(const SymbolString& key);
        bool IsCalculated(const SymbolString& key) const;
        void ClearCalculated();
    private:
        std::map<SymbolString, TerminalSet> mapInternal;
        std::set<SymbolString> calculated;
    };

    typedef boost::shared_ptr<FirstFunction> PFirstFunction;
}
}
}