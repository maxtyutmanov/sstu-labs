#include "UnrecognizedTokenCreator.h"
#include "TokenTag.h"

namespace JustCompiler {
namespace LexicalAnalyzer {
namespace TokenCreators {

    bool UnrecognizedTokenCreator::TryCreateToken(
        const string_type& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error) {

        *token = new Token(TokenTag::Unrecognized, lineNum, charNum);
        return true;
    }

}
}
}