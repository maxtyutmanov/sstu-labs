#pragma once

#include "Token.h"

namespace JustCompiler {
namespace LexicalAnalyzer {
namespace Tokens {

    class RealConstant : public Token {
    public:
        RealConstant(const double value, const int lineNum, const int charNum);

        double GetValue() const;

        virtual bool operator== (const Token& right) const;
    private:
        double value;
    };

}
}
}