#include "WordTokenCreator.h"
#include "ErrorCode.h"
#include "Identifier.h"

WordTokenCreator::WordTokenCreator(const LexerSettings& lexerSettings) 
    : settings(lexerSettings) {
}

bool WordTokenCreator::TryCreateToken(
    const wstring& lexeme, 
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

bool WordTokenCreator::CheckCharset(const wstring& lexeme) {
    for (size_t i = 0; i < lexeme.length(); ++i) {
        if (!iswascii(lexeme[i])) {
            return false;
        }
    }

    return true;
}