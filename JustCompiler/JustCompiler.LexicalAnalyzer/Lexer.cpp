#include "Lexer.h"
#include "IntConstant.h"
#include "StringLiteral.h"
#include "Identifier.h"
#include "TokenCreator.h"
#include <boost/tuple/tuple.hpp>
#include <assert.h>
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
using boost::bad_lexical_cast;
using boost::shared_ptr;

Lexer::Lexer(const LexerSettings& settings, shared_ptr<FaState> initState, input_stream_type& input)
    :settings(settings), currentState(initState), buffer(input) {
}

LexerOutput Lexer::Tokenize() {
    while (!buffer.Eof()) {
        char_type currentChar = buffer.Get();

        MoveFiniteAutomata(currentChar);
    }

    MoveFiniteAutomata(LITERAL('\0'));

    return LexerOutput(tokens, errors);
}

void Lexer::AddTransition(const FaTransition& transition) {
    faTransitions.push_back(transition);
}

void Lexer::MoveFiniteAutomata(char_type currentChar) {
    //search for appropriate transition for current state and input char
    FaTransition *selectedTransition = NULL;

    for (size_t i = 0; i < faTransitions.size(); ++i) {
        if (faTransitions[i].From() == currentState && faTransitions[i].IsCharValid(currentChar)) {
            selectedTransition = &faTransitions[i];
            break;
        }
    }

    //TODO: very bad
    assert(selectedTransition != NULL);

    switch (selectedTransition->GetReadAction()) {
    case ReadAction::KeepInBuffer_Ignore:
        //TODO: danger! Should think about infinite cycle!
        buffer.Unget();
        break;
    case ReadAction::RemoveFromBuffer_AddToLexeme:
        currentLexeme.push_back(currentChar);
        break;
    case ReadAction::RemoveFromBuffer_Ignore:
        //do nothing
        break;
    case ReadAction::RemoveFromBuffer_ClearLexeme:
        currentLexeme = LITERAL("");
        break;
    default:
        //TODO: !!!
        assert(false);
    }

    if (selectedTransition->ErrorCode() != 0) {
        //error while recongnition of the current lexeme. Must report it

        //TODO: maybe it's reasonable to create a LexicalErrorCreator class for the purpose of generating lexer errors
        ReportUnrecognizedLexeme(buffer.GetLineNumber(), buffer.GetCharacterNumber(), selectedTransition->ErrorCode());
    }
    else {
        shared_ptr<TokenCreator> creator = selectedTransition->GetTokenCreator();

        Token* pCreatedToken;
        LexicalError* pError;

        if (creator != NULL) {
            if (creator->TryCreateToken(currentLexeme, buffer.GetLineNumber(), buffer.GetCharacterNumber(), &pCreatedToken, &pError)) {
                tokens.push_back(pCreatedToken);
            }
            else {
                errors.push_back(pError);
                tokens.push_back(new Token(TokenTag::Unrecognized, buffer.GetLineNumber(), buffer.GetCharacterNumber()));
            }

            currentLexeme = LITERAL("");
        }
    }

    currentState = selectedTransition->To();
}

void Lexer::ReportUnrecognizedLexeme(const int lineNumber, const int charNumber, const int errorCode) {
    errors.push_back(new LexicalError(lineNumber, charNumber, errorCode));
    tokens.push_back(new Token(TokenTag::Unrecognized, lineNumber, charNumber));
}