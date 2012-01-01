#pragma once

#include "Global.h"
#include <Token.h>

namespace JustCompiler {
namespace LexicalAnalyzer {
namespace Tokens {

    class StandardFunction : public Token {
    public:
        StandardFunction(const string_type& name, const int lineNum, const int charNum);

        string_type GetName() const;

        virtual bool operator== (const Token& right) const;
    private:
        string_type name;
    };

}
}
}