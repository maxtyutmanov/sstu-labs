#pragma once

#include "Global.h"
#include "Token.h"
#include "LexicalError.h"
#include <vector>
using std::vector;

class LexerOutput {
public:
    LexerOutput(const vector<Token>& tokens, const vector<LexicalError>& lexicalErrors);
private:
    vector<Token> tokens;
    vector<LexicalError> lexicalErrors;
};