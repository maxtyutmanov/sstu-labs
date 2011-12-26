#pragma once

#include "NonTerminal.h"
#include "TerminalSet.h"
#include <map>
#include <set>
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    class FollowFunction {
    public:
        TerminalSet& operator()(PNonTerminal key);

        void MarkAsCalculated(PNonTerminal key);
        bool IsCalculated(PNonTerminal key) const;
        void ClearCalculated();
    private:
        std::map<int, TerminalSet> mapInternal;
        std::set<int> calculated;
    };

    typedef boost::shared_ptr<FollowFunction> PFollowFunction;
}
}
}