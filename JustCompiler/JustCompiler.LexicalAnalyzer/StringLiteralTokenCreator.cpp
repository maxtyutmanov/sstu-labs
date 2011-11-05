#include "StringLiteralTokenCreator.h"
#include "StringLiteral.h"
#include <assert.h>

bool StringLiteralTokenCreator::TryCreateToken(
    const wstring& lexeme, 
    int lineNum, 
    int charNum, 
    Token** token, 
    LexicalError** error) {

    *token = new StringLiteral(lexeme, lineNum, charNum - lexeme.length());
    return true;
}