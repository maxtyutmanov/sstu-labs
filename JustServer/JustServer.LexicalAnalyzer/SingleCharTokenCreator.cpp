#include "SingleCharTokenCreator.h"
#include "ErrorCode.h"
#include <assert.h>

SingleCharTokenCreator::SingleCharTokenCreator(const LexerSettings& lexerSettings)
    :settings(lexerSettings) {
}

bool SingleCharTokenCreator::TryCreateToken(
    const string_type& lexeme, 
    int lineNum, 
    int charNum, 
    Token** token, 
    LexicalError** error) {

    //TODO: very bad
    assert(lexeme.length() == 1);

    char_type singleChar = lexeme[0];

    TokenTag::Enum tag;

    if (settings.GetSingleCharLexeme(singleChar, &tag)) {
        *token = new Token(tag, lineNum, charNum - 1);
        return true;
    }
    else {
        *error = new LexicalError(lineNum, charNum, ErrorCode::UnknownLexeme);
        return false;
    }
}