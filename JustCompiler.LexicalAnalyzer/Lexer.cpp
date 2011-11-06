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

Lexer::Lexer(const LexerSettings& settings, shared_ptr<FaState> initState, wistream& input)
    :settings(settings), currentState(initState), buffer(input) {
}

LexerOutput Lexer::Tokenize() {
    while (!buffer.Eof()) {
        wchar_t currentChar = buffer.Get();

        MoveFiniteAutomata(currentChar);
    }

    MoveFiniteAutomata(L'\0');

    return LexerOutput(tokens, errors);
}

void Lexer::AddTransition(const FaTransition& transition) {
    faTransitions.push_back(transition);
}

void Lexer::MoveFiniteAutomata(wchar_t currentChar) {
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
        currentLexeme = L"";
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

            currentLexeme = L"";
        }
    }

    currentState = selectedTransition->To();
}

void Lexer::ReportUnrecognizedLexeme(const int lineNumber, const int charNumber, const int errorCode) {
    errors.push_back(new LexicalError(lineNumber, charNumber, errorCode));
    tokens.push_back(new Token(TokenTag::Unrecognized, lineNumber, charNumber));
}

//void Lexer::SkipExtraSpaces() {
//    while (true) {
//
//        if (buffer.Eof()) {
//            break;
//        }
//
//        wchar_t currentChar = buffer.Get();
//
//        if (currentChar != L' ' && currentChar != L'\t') {
//            //we have read one character too many
//            buffer.Unget();
//            break;
//        }
//    }
//
//    tokens.push_back(new Token(TokenTag::Space));
//}
//
//void Lexer::ExtractIntConstant(const wchar_t firstDigit) {
//    //we subtract 1 because we've already read one digit
//    int startPosition = buffer.GetCharacterNumber() - 1;
//
//    wstring numberStr;
//    
//    wchar_t currentChar = firstDigit;
//    
//
//    //collecting all digit characters (one per iteration) into the numberStr buffer
//    while (true) {
//        numberStr.push_back(currentChar);
//
//        if (buffer.Eof()) {
//            break;
//        }
//
//        currentChar = buffer.Get();
//
//        if (!iswdigit(currentChar)) {
//            //we stop here, 'cause we've read all digits of the integer constant
//
//            if (iswalpha(currentChar)) {
//                ReportUnrecongnizedLexeme(L"Идентификатор не может начинаться с цифры", buffer.GetLineNumber(), startPosition);
//                SkipInvalidIntConstant();
//                return;
//            }
//            else {
//                buffer.Unget();
//            }
//
//            break;
//        }
//    }
//
//    if (numberStr.size() > 1 && numberStr[0] == L'0') {
//        ReportUnrecongnizedLexeme(L"Лидирующий ноль в целой константе", buffer.GetLineNumber(), startPosition);
//        SkipInvalidIntConstant();
//        return;
//    }
//
//    //if we got thus far we have a string representation of number (stored in the local variable numberStr)
//
//    int number;
//
//    try {
//        number = lexical_cast<int, wstring>(numberStr);
//    }
//    catch (const bad_lexical_cast &ex) {
//        //this could've been caused only by int overflow, 'cause we've already checked all the digits for validity
//        ReportUnrecongnizedLexeme(
//            L"Слишком большая целая константа (максимально допустимое значение: " + lexical_cast<wstring, int>(INT_MAX) + L")", 
//            buffer.GetLineNumber(), 
//            startPosition);
//        return;
//    }
//
//    //if we've got this far, integer constant is recognized without any errors
//    tokens.push_back(new IntConstant(number));
//}
//
//void Lexer::SkipInvalidIntConstant() {
//    while (true) {
//        if (buffer.Eof()) {
//            return;
//        }
//
//        wchar_t currentChar = buffer.Get();
//
//        if (!iswdigit(currentChar) && !iswalpha(currentChar)) {
//            buffer.Unget();
//            return;
//        }
//    }
//}
//
//void Lexer::ExtractStringLiteral() {
//    wstring literalText;
//
//    wchar_t currentChar;
//
//    while (true) {
//        if (buffer.Eof()) {
//            ReportUnrecongnizedLexeme(L"Незакрытый строковый литерал", buffer.GetLineNumber(), buffer.GetCharacterNumber());
//            return;
//        }
//
//        currentChar = buffer.Get();
//
//        if (currentChar == L'"') {
//            break;
//        }
//        else if (currentChar == L'\n') {
//            buffer.Unget();
//            ReportUnrecongnizedLexeme(L"Незакрытый строковый литерал", buffer.GetLineNumber(), buffer.GetCharacterNumber());
//            return;
//        }
//        else {
//            literalText.push_back(currentChar);
//        }
//    }
//    //if we got thus far then it's OK!
//    tokens.push_back(new StringLiteral(literalText));
//}
//
//void Lexer::ExtractWord(const wchar_t firstChar) {
//    int startPosition = buffer.GetCharacterNumber() - 1;
//
//    wstring word;
//    
//    wchar_t currentChar = firstChar;
//
//    //indicates whether the character set for this word is correct (only ascii characters)
//    bool valid = true;
//
//    while (true) {
//        if (!iswascii(currentChar)) {
//            valid = false;
//            //reading the word to the end anyway
//        }
//
//        word.push_back(currentChar);
//
//        if (buffer.Eof()) {
//            break;
//        }
//
//        currentChar = buffer.Get();
//
//        if (!iswalpha(currentChar) && !iswdigit(currentChar)) {
//            buffer.Unget();
//            break;
//        }
//    }
//
//    if (!valid) {
//        ReportUnrecongnizedLexeme(
//            L"Некорректный идентификатор: в идентификаторах допускаются только заглавные и строчные латинские буквы",
//            buffer.GetLineNumber(),
//            startPosition);
//        return;
//    }
//
//    if (word.length() > settings.GetMaxIdentifierLength()) {
//        ReportUnrecongnizedLexeme(
//            L"Слишком длинный идентификатор (допускается не более " + lexical_cast<wstring, int>(settings.GetMaxIdentifierLength()) + L" символов)",
//            buffer.GetLineNumber(),
//            startPosition);
//        return;
//    }
//
//    //if we got thus far, then it's OK! We have either identifier or keyword here
//
//    TokenTag::Enum tag;
//
//    if (settings.GetKeyword(word, &tag)) {
//        tokens.push_back(new Token(tag));
//    }
//    else if (settings.GetStandardFunction(word, &tag)) {
//        tokens.push_back(new Token(tag));
//    }
//    else {
//        tokens.push_back(new Identifier(word));
//    }
//}
//
//void Lexer::ExtractOneCharacterToken(const wchar_t ch) {
//    TokenTag::Enum tag;
//
//    if (settings.GetSingleCharLexeme(ch, &tag)) {
//        tokens.push_back(new Token(tag));
//    }
//    else {
//        ReportUnrecongnizedLexeme(L"Неизвестная лексема", buffer.GetLineNumber(), buffer.GetCharacterNumber());
//    }
//}
//
//void Lexer::SkipComment() {
//    bool justReadAsterisk = false;
//
//    while (true) {
//        if (buffer.Eof()) {
//            ReportUnrecongnizedLexeme(L"Незакрытый комментарий", buffer.GetLineNumber(), buffer.GetCharacterNumber());
//            return;
//        }
//
//        wchar_t currentChar = buffer.Get();
//
//        if (currentChar == L'/') {
//            if (justReadAsterisk) {
//                // */ means the end of the comment
//                return;
//            }
//        }
//        else {
//            justReadAsterisk = false;
//        }
//
//        if (currentChar == L'*') {
//            justReadAsterisk = true;
//        }
//    }
//}
//
//void Lexer::ExtractNewLine() {
//
//    while (true) {
//        if (buffer.Eof()) {
//            break;
//        }
//
//        wchar_t currentChar = buffer.Get();
//
//        if (currentChar != L'\n' && !currentChar != L'\r') {
//            buffer.Unget();
//            break;
//        }
//    }
//
//    tokens.push_back(new Token(TokenTag::Newline));
//}