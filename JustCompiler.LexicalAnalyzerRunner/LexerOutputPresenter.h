#pragma once

#include "Token.h"
#include "LexicalError.h"
#include "StringLiteral.h"
#include "IntConstant.h"
#include "TokenTable.h"

#include <vector>
#include <map>
#include <string>
#include <iostream>
using std::vector;
using std::wstring;
using std::wostream;
using std::map;


struct TokenTablesContainer {
    TokenTable keywords;
    TokenTable standardFunctions;
    TokenTable separators;
    TokenTable constants;
    TokenTable identifiers;
};

class LexerOutputPresenter {
public:
    TokenTablesContainer WriteDescriptorText(vector<Token*> tokens, wostream& output);
    void WriteLexicalErrors(wostream& output);
};