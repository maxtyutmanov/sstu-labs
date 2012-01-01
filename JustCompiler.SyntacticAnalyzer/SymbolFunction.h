#pragma once

#include <map>
#include "SymbolType.h"
#include "SymbolSet.h"

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    struct SymbolFunctionArg {
        SymbolFunctionArg(SymbolType::Enum symbolType, int tag)
            :symbolType(symbolType), tag(tag) {}

        bool operator < (const SymbolFunctionArg& right) {
            if (this->symbolType != right.symbolType) {
                return this->symbolType < right.symbolType;
            }
            else {
                return this->tag < right.tag;
            }
        }

        SymbolType::Enum symbolType;
        int tag;
    };

    class SymbolFunction {
    public:
        void AddValue(const SymbolFunctionArg& arg, const SymbolSet& symbolSet);
    private:
        std::map<SymbolFunctionArg, SymbolSet> mapInternal;
    };

}
}
}