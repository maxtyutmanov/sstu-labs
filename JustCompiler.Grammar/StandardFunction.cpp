#include "StandardFunction.h"
#include "TokenTag.h"

namespace JustCompiler {
namespace LexicalAnalyzer {
namespace Tokens {

    StandardFunction::StandardFunction(const string_type& name, const int lineNum, const int charNum)
        : Token(TokenTag::StandardFunction, lineNum, charNum) {

        this->name = name;
    }

    string_type StandardFunction::GetName() const {
        return name;
    }

    bool StandardFunction::operator== (const Token& right) const {
        if (right.GetTag() != TokenTag::StandardFunction) {
            return false;
        }

        //TODO: can be optimized

        const StandardFunction *rightFunc = dynamic_cast<const StandardFunction *>(&right);

        //TODO: check is needed. Or not?

        return this->name == rightFunc->name;
    }

}
}
}