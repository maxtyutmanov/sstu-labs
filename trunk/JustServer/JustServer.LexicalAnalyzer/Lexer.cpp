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

Lexer::Lexer(shared_ptr<FaState> initState)
    : currentState(initState), initState(initState) {

    assert(initState.get() != NULL);
}

LexerOutput Lexer::Tokenize() {
    assert(pBuffer.get() != NULL);

    while (!pBuffer->Eof()) {
        char_type currentChar = pBuffer->Get();

        MoveFiniteAutomata(currentChar);
    }

    MoveFiniteAutomata(LITERAL('\0'));

    return LexerOutput(tokens, errors);
}

void Lexer::SetInput(auto_ptr<IInputBuffer> pBuffer) {
    tokens.clear();
    errors.clear();
    currentState = initState;
    currentLexeme = LITERAL("");

    this->pBuffer = pBuffer;
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

    //TODO: very bad. Even to throw an exception would have been better thing to do
    assert(selectedTransition != NULL);

    switch (selectedTransition->GetReadAction()) {
    case ReadAction::KeepInBuffer_Ignore:
        //TODO: danger! Should think about infinite cycle!
        pBuffer->Unget();
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
        errors.push_back(shared_ptr<LexicalError>(new LexicalError(
            pBuffer->GetLineNumber(), 
            pBuffer->GetCharacterNumber(), 
            selectedTransition->ErrorCode())));

        tokens.push_back(shared_ptr<Token>(new Token(
            -1, 
            pBuffer->GetLineNumber(), 
            pBuffer->GetCharacterNumber())));
    }
    else {
        shared_ptr<TokenCreator> creator = selectedTransition->GetTokenCreator();

        Token* pCreatedToken;
        LexicalError* pError;

        if (creator != NULL) {
            if (creator->TryCreateToken(currentLexeme, pBuffer->GetLineNumber(), pBuffer->GetCharacterNumber(), &pCreatedToken, &pError)) {
                tokens.push_back(shared_ptr<Token>(pCreatedToken));
            }
            else {
                errors.push_back(shared_ptr<LexicalError>(pError));
                tokens.push_back(shared_ptr<Token>(new Token(-1, pBuffer->GetLineNumber(), pBuffer->GetCharacterNumber())));
            }

            currentLexeme = LITERAL("");
        }
    }

    currentState = selectedTransition->To();
}