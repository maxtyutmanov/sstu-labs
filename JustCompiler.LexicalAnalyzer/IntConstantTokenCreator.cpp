#include "IntConstantTokenCreator.h"
#include "IntConstant.h"
#include "ErrorCode.h"
#include <boost/lexical_cast.hpp>

bool IntConstantTokenCreator::TryCreateToken(
    const wstring& lexeme, 
    int lineNum, 
    int charNum, 
    Token** token, 
    LexicalError** error) {

    if (lexeme.size() > 1 && lexeme[0] == L'0') {
        *error = new LexicalError(lineNum, charNum, ErrorCode::IntConstantStartingWithZero);
        return false;
    }

    try {
        int value = boost::lexical_cast<int, wstring>(lexeme);
        *token = new IntConstant(value, lineNum, charNum - lexeme.length());
        return true;
    }
    catch (boost::bad_lexical_cast ex) {
        *error = new LexicalError(lineNum, charNum, ErrorCode::TooLargeIntConstant);
        return false;
    }
}