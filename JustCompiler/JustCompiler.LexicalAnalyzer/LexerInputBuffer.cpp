#include "LexerInputBuffer.h"
#include <streambuf>
using std::istreambuf_iterator;

LexerInputBuffer::LexerInputBuffer(input_stream_type &input) {
    //TODO: optimize memory allocation for wstring
    this->input = string_type(
        istreambuf_iterator<char_type>(input), 
        istreambuf_iterator<char_type>());

    cursor = 0;
    lineNumber = 1;
    characterNumber = 1;
}

char_type LexerInputBuffer::Get() {
    char_type readChar = input[cursor++];

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

    if (cursor > 0 && input[cursor - 1] == LITERAL('\n')) {
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