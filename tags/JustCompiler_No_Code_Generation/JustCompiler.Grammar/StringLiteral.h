#pragma once

#include "Global.h"
#include "Token.h"

namespace JustCompiler {
namespace LexicalAnalyzer {
namespace Tokens {

    class StringLiteral : public Token {
    public:
        StringLiteral(const string_type& text, const int lineNum, const int charNum);

        string_type GetText() const;

        virtual bool operator== (const Token& right) const;
    private:
        string_type text;
    };

}
}
}