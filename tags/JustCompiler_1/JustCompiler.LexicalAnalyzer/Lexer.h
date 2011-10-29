#pragma once

#include "Token.h"
#include "LexerSettings.h"
#include "LexerInputBuffer.h"
#include "LexicalError.h"
#include <vector>
#include <iostream>
#include <boost/tuple/tuple.hpp>
using std::vector;
using std::wistream;

typedef boost::tuple<vector<Token *>, vector<LexicalError *>> LexerOutput;

class Lexer {
public:
    Lexer(const LexerSettings& settings, wistream& input);

    LexerOutput Tokenize();
private:
    LexerSettings settings;
    LexerInputBuffer buffer;
    vector<Token *> tokens;
    vector<LexicalError *> errors;

    void SkipExtraSpaces();
    void ExtractIntConstant(const wchar_t firstDigit);
    void SkipInvalidIntConstant();
    void ExtractStringLiteral();
    //Extracts either keyword or identifier
    void ExtractWord(const wchar_t firstChar);
    void ExtractOneCharacterToken(const wchar_t ch);
    void SkipComment();
    void ExtractNewLine();

    void ReportUnrecongnizedLexeme(const wstring& errorMessage, const int lineNumber, const int charNumber);
};