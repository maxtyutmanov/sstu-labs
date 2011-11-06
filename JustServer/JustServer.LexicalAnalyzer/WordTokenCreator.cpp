#include "WordTokenCreator.h"
#include "ErrorCode.h"
#include "Identifier.h"

WordTokenCreator::WordTokenCreator(const LexerSettings& lexerSettings, CharValidationRule charValidationRule) 
    : settings(lexerSettings), charValidationRule(charValidationRule) {
}

bool WordTokenCreator::TryCreateToken(
    const string_type& lexeme, 
    int lineNum, 
    int charNum, 
    Token** token, 
    LexicalError** error) {

    TokenTag::Enum tag;
    
    if (settings.GetKeyword(lexeme, &tag)) {
        *token = new Token(tag, lineNum, charNum);
        return true;
    }
    else if (settings.GetStandardFunction(lexeme, &tag)) {
        *token = new Token(tag, lineNum, charNum);
        return true;
    }
    else {
        //it seems to be an identifier

        if (!CheckCharset(lexeme)) {
            *error = new LexicalError(lineNum, charNum - lexeme.length(), ErrorCode::IdWithWrongCharset);
            return false;
        }

        if (lexeme.length() > settings.GetMaxIdentifierLength()) {
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