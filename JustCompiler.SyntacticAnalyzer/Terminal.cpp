#pragma once

#include "Terminal.h"

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    Terminal::Terminal(int tokenTag)
        : tokenTag(tokenTag) {}

    int Terminal::GetTokenTag() const {
        return tokenTag;
    }

    SymbolType::Enum Terminal::GetType() const {
        return SymbolType::Terminal;
    }

    int Terminal::Compare(const Symbol& right) const {
        if (right.GetType() == SymbolType::Terminal) {
            Terminal* rightAsT = (Terminal*)&right;

            return this->GetTokenTag() - rightAsT->GetTokenTag();
        }
        else {
            return -1;
        }
    }
}
}
}