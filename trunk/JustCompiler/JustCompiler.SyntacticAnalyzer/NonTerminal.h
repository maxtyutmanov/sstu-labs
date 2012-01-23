#pragma once

#include "Symbol.h"
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    class NonTerminal;
    typedef boost::shared_ptr<NonTerminal> PNonTerminal;

    class NonTerminal : public Symbol {
    public:
        NonTerminal(int tag);

        int GetTag() const;
        virtual SymbolType::Enum GetType() const;

        /*virtual bool operator ==(const Symbol& right) const;
        bool operator == (const NonTerminal& right) const;
        bool operator < (const NonTerminal& right) const;*/

        virtual int Compare(const Symbol& right) const;
    private:
        int tag;
    };

    typedef boost::shared_ptr<NonTerminal> PNonTerminal;

}
}
}