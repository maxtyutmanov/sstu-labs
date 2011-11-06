#pragma once

#include "Global.h"
#include "Token.h"
#include "LexerSettings.h"
#include "LexerInputBuffer.h"
#include "LexicalError.h"
#include "FaState.h"
#include "FaTransition.h"
#include <vector>
#include <iostream>
#include <boost/tuple/tuple.hpp>
#include <boost/shared_ptr.hpp>
using std::vector;
using std::wistream;
using boost::shared_ptr;

typedef boost::tuple<vector<Token *>, vector<LexicalError *>> LexerOutput;

class Lexer {
public:
    Lexer(const LexerSettings& settings, shared_ptr<FaState> initState, input_stream_type& input);
    void AddTransition(const FaTransition& transition);

    LexerOutput Tokenize();
private:
    LexerSettings settings;
    LexerInputBuffer buffer;
    string_type currentLexeme;
    vector<FaTransition> faTransitions;
    shared_ptr<FaState> currentState;

    vector<Token *> tokens;
    vector<LexicalError *> errors;

    //private methods
    
    void MoveFiniteAutomata(char_type inputChar);

    void ReportUnrecognizedLexeme(const int charNumber, const int lineNumber, const int errorCode);
};