#include "SingleCharTokenCreator.h"
#include "ErrorCode.h"
#include <assert.h>
#include "TokenTag.h"

namespace JustCompiler {
namespace LexicalAnalyzer {
namespace TokenCreators {

    SingleCharTokenCreator::SingleCharTokenCreator(boost::shared_ptr<LexemeToTagMapping> pSingleCharLexemesMapping)
        :pSingleCharLexemesMapping(pSingleCharLexemesMapping) {
    }

    bool SingleCharTokenCreator::TryCreateToken(
        const string_type& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error) {

        assert(lexeme.length() == 1);

        char_type singleChar = lexeme[0];

        TokenTag::Enum tag;

        if (pSingleCharLexemesMapping->TryGetTokenTag(lexeme, tag)) {
            *token = new Token(tag, lineNum, charNum - 1);
            return true;
        }
        else {
            *error = new LexicalError(lineNum, charNum - 1, ErrorCode::UnknownLexeme);
            return false;
        }
    }

}
}
}