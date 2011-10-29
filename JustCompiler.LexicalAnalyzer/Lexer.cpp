#include "Lexer.h"
#include "IntConstant.h"
#include "StringLiteral.h"
#include "Identifier.h"
#include <boost/tuple/tuple.hpp>
#include <assert.h>
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
using boost::bad_lexical_cast;

Lexer::Lexer(const LexerSettings& settings, wistream& input)
    :settings(settings), buffer(input) {
}

LexerOutput Lexer::Tokenize() {
    while (!buffer.Eof()) {
        wchar_t currentChar = buffer.Get();

        if (currentChar == L' ' || currentChar == '\t') {
            SkipExtraSpaces();
        }
        else if (iswdigit(currentChar)) {
            ExtractIntConstant(currentChar);
        }
        else if (currentChar == L'"') {
            ExtractStringLiteral();
        }
        else if (iswalpha(currentChar)) {
            //keyword, standard function or identifier
            ExtractWord(currentChar);
        }
        else if (currentChar == L'\n') {
            ExtractNewLine();
        }
        else if (currentChar == L'\r') {
            //TODO: we're ignoring carriage return. This is bad!
        }
        else if (currentChar == L'/' && !buffer.Eof()) {
            //it can be a comment (if asterisk follows)

            if (buffer.Get() == L'*') {
                //...yes, it's a comment
                SkipComment();
            }
            else {
                //...no, it's not
                buffer.Unget();
                ExtractOneCharacterToken(currentChar);
            }

            //skipping comments
        }
        else {
            //if we got thus far, we treat the last read character as a one character token
            ExtractOneCharacterToken(currentChar);
        }
    }

    return LexerOutput(tokens, errors);
}

void Lexer::SkipExtraSpaces() {
    while (true) {

        if (buffer.Eof()) {
            break;
        }

        wchar_t currentChar = buffer.Get();

        if (currentChar != L' ' && currentChar != L'\t') {
            //we have read one character too many
            buffer.Unget();
            break;
        }
    }

    tokens.push_back(new Token(TokenTag::Space));
}

void Lexer::ExtractIntConstant(const wchar_t firstDigit) {
    //we subtract 1 because we've already read one digit
    int startPosition = buffer.GetCharacterNumber() - 1;

    wstring numberStr;
    
    wchar_t currentChar = firstDigit;

    

    //collecting all digit characters (one per iteration) into the numberStr buffer
    while (true) {
        numberStr.push_back(currentChar);

        if (buffer.Eof()) {
            break;
        }

        currentChar = buffer.Get();

        if (!iswdigit(currentChar)) {
            //we stop here, 'cause we've read all digits of the integer constant

            if (iswalpha(currentChar)) {
                ReportUnrecongnizedLexeme(L"Идентификатор не может начинаться с цифры", buffer.GetLineNumber(), startPosition);
                SkipInvalidIntConstant();
                return;
            }
            else {
                buffer.Unget();
            }

            break;
        }
    }

    if (numberStr.size() > 1 && numberStr[0] == L'0') {
        ReportUnrecongnizedLexeme(L"Лидирующий ноль в целой константе", buffer.GetLineNumber(), startPosition);
        SkipInvalidIntConstant();
        return;
    }

    //if we got thus far we have a string representation of number (stored in the local variable numberStr)

    int number;

    try {
        number = lexical_cast<int, wstring>(numberStr);
    }
    catch (const bad_lexical_cast &ex) {
        //this could've been caused only by int overflow, 'cause we've already checked all the digits for validity
        ReportUnrecongnizedLexeme(
            L"Слишком большая целая константа (максимально допустимое значение: " + lexical_cast<wstring, int>(INT_MAX) + L")", 
            buffer.GetLineNumber(), 
            startPosition);
        return;
    }

    //if we've got this far, integer constant is recognized without any errors
    tokens.push_back(new IntConstant(number));
}

void Lexer::SkipInvalidIntConstant() {
    while (true) {
        if (buffer.Eof()) {
            return;
        }

        wchar_t currentChar = buffer.Get();

        if (!iswdigit(currentChar) && !iswalpha(currentChar)) {
            buffer.Unget();
            return;
        }
    }
}

void Lexer::ExtractStringLiteral() {
    wstring literalText;

    wchar_t currentChar;

    while (true) {
        if (buffer.Eof()) {
            ReportUnrecongnizedLexeme(L"Незакрытый строковый литерал", buffer.GetLineNumber(), buffer.GetCharacterNumber());
            return;
        }

        currentChar = buffer.Get();

        if (currentChar == L'"') {
            break;
        }
        else if (currentChar == L'\n') {
            buffer.Unget();
            ReportUnrecongnizedLexeme(L"Незакрытый строковый литерал", buffer.GetLineNumber(), buffer.GetCharacterNumber());
            return;
        }
        else {
            literalText.push_back(currentChar);
        }
    }
    //if we got thus far then it's OK!
    tokens.push_back(new StringLiteral(literalText));
}

void Lexer::ExtractWord(const wchar_t firstChar) {
    int startPosition = buffer.GetCharacterNumber() - 1;

    wstring word;
    
    wchar_t currentChar = firstChar;

    //indicates whether the character set for this word is correct (only ascii characters)
    bool valid = true;

    while (true) {
        if (!iswascii(currentChar)) {
            valid = false;
            //reading the word to the end anyway
        }

        word.push_back(currentChar);

        if (buffer.Eof()) {
            break;
        }

        currentChar = buffer.Get();

        if (!iswalpha(currentChar) && !iswdigit(currentChar)) {
            buffer.Unget();
            break;
        }
    }

    if (!valid) {
        ReportUnrecongnizedLexeme(
            L"Некорректный идентификатор: в идентификаторах допускаются только заглавные и строчные латинские буквы",
            buffer.GetLineNumber(),
            startPosition);
        return;
    }

    if (word.length() > settings.GetMaxIdentifierLength()) {
        ReportUnrecongnizedLexeme(
            L"Слишком длинный идентификатор (допускается не более " + lexical_cast<wstring, int>(settings.GetMaxIdentifierLength()) + L" символов)",
            buffer.GetLineNumber(),
            startPosition);
        return;
    }

    //if we got thus far, then it's OK! We have either identifier or keyword here

    TokenTag::Enum tag;

    if (settings.GetKeyword(word, &tag)) {
        tokens.push_back(new Token(tag));
    }
    else if (settings.GetStandardFunction(word, &tag)) {
        tokens.push_back(new Token(tag));
    }
    else {
        tokens.push_back(new Identifier(word));
    }
}

void Lexer::ExtractOneCharacterToken(const wchar_t ch) {
    TokenTag::Enum tag;

    if (settings.GetSingleCharLexeme(ch, &tag)) {
        tokens.push_back(new Token(tag));
    }
    else {
        ReportUnrecongnizedLexeme(L"Неизвестная лексема", buffer.GetLineNumber(), buffer.GetCharacterNumber());
    }
}

void Lexer::SkipComment() {
    bool justReadAsterisk = false;

    while (true) {
        if (buffer.Eof()) {
            ReportUnrecongnizedLexeme(L"Незакрытый комментарий", buffer.GetLineNumber(), buffer.GetCharacterNumber());
            return;
        }

        wchar_t currentChar = buffer.Get();

        if (currentChar == L'/') {
            if (justReadAsterisk) {
                // */ means the end of the comment
                return;
            }
        }
        else {
            justReadAsterisk = false;
        }

        if (currentChar == L'*') {
            justReadAsterisk = true;
        }
    }
}

void Lexer::ExtractNewLine() {

    while (true) {
        if (buffer.Eof()) {
            break;
        }

        wchar_t currentChar = buffer.Get();

        if (currentChar != L'\n' && !currentChar != L'\r') {
            buffer.Unget();
            break;
        }
    }

    tokens.push_back(new Token(TokenTag::Newline));
}

void Lexer::ReportUnrecongnizedLexeme(const wstring& errorMessage, const int lineNumber, const int charNumber) {
    errors.push_back(new LexicalError(lineNumber, charNumber, errorMessage));
    tokens.push_back(new Token(TokenTag::Unrecognized));
}