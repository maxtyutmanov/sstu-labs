#pragma once

#include "SymbolType.h"
#include <boost/shared_ptr.hpp>

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    class Symbol {
    public:
        virtual SymbolType::Enum GetType() const = 0;
        virtual ~Symbol() {}

        bool operator ==(const Symbol& right) const {
            return this->Compare(right) == 0;
        }

        bool operator < (const Symbol& right) const {
            return this->Compare(right) < 0;
        }

        virtual int Compare(const Symbol& right) const = 0;
    };

    typedef boost::shared_ptr<Symbol> PSymbol;
}
}
}