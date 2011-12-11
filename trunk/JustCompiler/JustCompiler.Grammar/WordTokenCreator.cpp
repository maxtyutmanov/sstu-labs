#include "WordTokenCreator.h"
#include "ErrorCode.h"
#include "Identifier.h"
#include "TokenTag.h"

using JustCompiler::LexicalAnalyzer::Tokens::Identifier;

namespace JustCompiler {
namespace LexicalAnalyzer {
namespace TokenCreators {

    WordTokenCreator::WordTokenCreator(
        boost::shared_ptr<LexemeToTagMapping> pKeywordsMapping, 
        boost::shared_ptr<LexemeToTagMapping> pStandardFuncMapping, 
        CharValidationRule charValidationRule,
        size_t maxIdentifierLength)

        :pKeywordsMapping(pKeywordsMapping), pStandardFuncMapping(pStandardFuncMapping), 
        charValidationRule(charValidationRule), maxIdentifierLength(maxIdentifierLength) {}

    bool WordTokenCreator::TryCreateToken(
        const string_type& lexeme, 
        int lineNum, 
        int charNum, 
        Token** token, 
        LexicalError** error) {

        TokenTag::Enum tag;
    
        if (pKeywordsMapping->TryGetTokenTag(lexeme, tag)) {
            *token = new Token(tag, lineNum, charNum);
            return true;
        }
        else if (pStandardFuncMapping->TryGetTokenTag(lexeme, tag)) {
            *token = new Token(tag, lineNum, charNum);
            return true;
        }
        else {
            //it seems to be an identifier

            if (!CheckCharset(lexeme)) {
                *error = new LexicalError(lineNum, charNum - lexeme.length(), ErrorCode::IdWithWrongCharset);
                return false;
            }

            if (lexeme.length() > maxIdentifierLength) {
                *error = new LexicalError(lineNum, charNum - lexeme.length(), ErrorCode::TooLongIdentifier);
                return false;
            }
            else {
                *token = new Identifier(lexeme, lineNum, charNum);
                return true;
            }
        }
    }

    bool WordTokenCreator::CheckCharset(const string_type& lexeme) {
        for (size_t i = 0; i < lexeme.length(); ++i) {
            if (!charValidationRule(lexeme[i])) {
                return false;
            }
        }

        return true;
    }

}
}
}