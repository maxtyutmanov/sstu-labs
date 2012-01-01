#include "SymbolString.h"
#include "NonTerminal.h"
#include "Terminal.h"

using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;

namespace JustCompiler {
namespace SyntacticAnalyzer {
namespace ContextFreeGrammar {

    bool SymbolString::operator < (const SymbolString& right) const {
        return Compare(right) < 0;
    }

    bool SymbolString::operator == (const SymbolString& right) const {
        return Compare(right) == 0;
    }

    bool SymbolString::ContainsSymbol(const PSymbol symbol) const {
        return FindSymbol(symbol) != -1;
    }

    int SymbolString::FindSymbol(const PSymbol symbol) const {
        return FindSymbol(symbol, 0);
    }

    int SymbolString::FindSymbol(const PSymbol symbol, int startIndex) const {
        for (size_t i = startIndex; i < this->size(); ++i) {
            if (*(this->at(i)) == *symbol) {
                return i;
            }
        }

        return -1;
    }

    int SymbolString::Compare(const SymbolString& right) const {
        std::vector<PSymbol>::const_iterator leftIt;
        std::vector<PSymbol>::const_iterator rightIt;

        for (leftIt = this->cbegin(), rightIt = right.cbegin(); 
            leftIt != this->cend() && rightIt != right.cend(); 
            ++leftIt, ++rightIt) {

            SymbolType::Enum leftType = leftIt->get()->GetType();
            SymbolType::Enum rightType = rightIt->get()->GetType();

            if (leftType == SymbolType::NonTerminal && rightType == SymbolType::NonTerminal) {
                NonTerminal* leftNT = (NonTerminal*)(leftIt->get());
                NonTerminal* rightNT = (NonTerminal*)(rightIt->get());

                if (leftNT->GetTag() != rightNT->GetTag()) {
                    return leftNT->GetTag() - rightNT->GetTag();
                }
            }
            else if (leftType == SymbolType::Terminal && rightType == SymbolType::Terminal) {
                Terminal* leftT = (Terminal*)(leftIt->get());
                Terminal* rightT = (Terminal*)(rightIt->get());

                if (leftT->GetTokenTag() != rightT->GetTokenTag()) {
                    return leftT->GetTokenTag() - rightT->GetTokenTag();
                }
            }
            else if (leftType == SymbolType::Terminal && rightType == SymbolType::NonTerminal) {
                return -1;
            }
            else {
                return 1;
            }
        }

        if (leftIt == this->cend() && rightIt == right.cend()) {
            return 0;
        }
        else if (leftIt == this->cend()) {
            return -1;
        }
        else {
            return 1;
        }
    }
}
}
}