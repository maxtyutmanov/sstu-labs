#pragma once

#include "Global.h"
#include "Token.h"
#include "IInputBuffer.h"
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

//TODO: this is bad
typedef boost::tuple<vector<shared_ptr<JustCompiler::LexicalAnalyzer::Token>>, vector<shared_ptr<JustCompiler::LexicalAnalyzer::LexicalError>>> LexerOutput;

namespace JustCompiler {
namespace LexicalAnalyzer {

    class Lexer {
    public:
        Lexer(shared_ptr<FaState> initState);
        void AddTransition(const FaTransition& transition);
        void SetInput(auto_ptr<IInputBuffer> pBuffer);

        LexerOutput Tokenize();
    private:
        auto_ptr<IInputBuffer> pBuffer;
        string_type currentLexeme;
        vector<FaTransition> faTransitions;
        shared_ptr<FaState> initState;
        shared_ptr<FaState> currentState;

        vector<shared_ptr<Token>> tokens;
        vector<shared_ptr<LexicalError>> errors;

        //private methods
    
        void MoveFiniteAutomata(char_type inputChar);
    };

}
}