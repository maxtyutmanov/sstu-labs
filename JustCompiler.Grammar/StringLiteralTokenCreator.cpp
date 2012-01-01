#include "StringLiteralTokenCreator.h"
#include "StringLiteral.h"
#include <assert.h>

using JustCompiler::LexicalAnalyzer::Tokens::StringLiteral;

namespace JustCompiler {
namespace LexicalAnalyzer {
namespace TokenCreators {

    bool StringLiteralTokenCreator::TryCreateToken(
        const string_type& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error) {

        *token = new StringLiteral(lexeme, lineNum, charNum - lexeme.length());
        return true;
    }

}
}
}