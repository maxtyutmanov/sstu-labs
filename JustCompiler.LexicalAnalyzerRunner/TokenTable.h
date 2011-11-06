#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "Token.h"
#include "LexerSettings.h"
using namespace std;

class TokenTable {
public:
    //searches for specified token in table (and inserts it in the table, if necessary) and gets its ID
    int Search(Token *t);

    void WriteToStream(const LexerSettings& lexerSettings, wostream& output);
private:
    vector<Token *> tokens;
};