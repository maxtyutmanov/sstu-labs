#include "LexerInputBuffer.h"
#include <streambuf>
using std::istreambuf_iterator;

LexerInputBuffer::LexerInputBuffer(wistream &input) {
    //TODO: optimize memory allocation for wstring
    this->input = wstring(
        istreambuf_iterator<wchar_t>(input), 
        istreambuf_iterator<wchar_t>());

    cursor = 0;
    lineNumber = 1;
    characterNumber = 1;
}

wchar_t LexerInputBuffer::Get() {
    wchar_t readChar = input[cursor++];

    if (readChar == L'\n') {
        GoToNewLine();
    }
    else {
        ++characterNumber;
    }
    
    return readChar;
}

void LexerInputBuffer::Unget() {
    //input[cursor - 1] is the latest read character

    if (cursor > 0 && input[cursor - 1] == L'\n') {
        GoToPreviousLine();
    }
    else {
        --characterNumber;
    }

    cursor--;
}

bool LexerInputBuffer::Eof() const {
    return cursor == input.length();
}

int LexerInputBuffer::GetLineNumber() const {
    return lineNumber;
}

int LexerInputBuffer::GetCharacterNumber() const {
    return characterNumber;
}

void LexerInputBuffer::GoToNewLine() {
    characterCounts[lineNumber] = characterNumber;
    ++lineNumber;
    characterNumber = 1;
}

void LexerInputBuffer::GoToPreviousLine() {
    --lineNumber;
    characterNumber = characterCounts[lineNumber];
}