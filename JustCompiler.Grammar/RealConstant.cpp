#include "RealConstant.h"

#include "TokenTag.h"

namespace JustCompiler {
namespace LexicalAnalyzer {
namespace Tokens {

    RealConstant::RealConstant(const double value, const int lineNum, const int charNum) 
        :Token(TokenTag::RealConstant, lineNum, charNum) {

        this->value = value;
    }

    double RealConstant::GetValue() const {
        return value;
    }

    bool RealConstant::operator== (const Token& right) const {
        if (right.GetTag() != TokenTag::RealConstant) {
            return false;
        }

        const RealConstant* rightIntConstant = dynamic_cast<const RealConstant*>(&right);

        return this->value == rightIntConstant->value;
    }

}
}
}