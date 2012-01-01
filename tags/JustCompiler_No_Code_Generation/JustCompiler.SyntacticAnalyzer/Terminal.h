#pragma once

#include "Symbol.h"
#include <Token.h>
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    class Terminal;
    typedef boost::shared_ptr<Terminal> PTerminal;

    class Terminal : public Symbol {
    public:
        Terminal(int tokenTag);

        int GetTokenTag() const;
        virtual SymbolType::Enum GetType() const;
        //virtual bool operator==(const Symbol& right) const;

        virtual int Compare(const Symbol& right) const;
    private:
        int tokenTag;
    };

    
}
}
}