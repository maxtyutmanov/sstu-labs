#include "UnrecognizedTokenCreator.h"

bool UnrecognizedTokenCreator::TryCreateToken(
    const wstring& lexeme, 
    int lineNum, 
    int charNum, 
    Token** token, 
    LexicalError** error) {

    *token = new Token(TokenTag::Unrecognized, lineNum, charNum);
    return true;
}