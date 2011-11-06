#pragma once

#include "Global.h"
#include <map>
using std::map;

class LexerInputBuffer {
public:
    explicit LexerInputBuffer(input_stream_type &input);

    char_type Get();
    void Unget();
    bool Eof() const;
    int GetLineNumber() const;
    int GetCharacterNumber() const;
private:
    string_type input;
    int cursor;
    int lineNumber;
    int characterNumber;
    //correspondence between line numbers and characters counts in this lines
    map<int, int> characterCounts;

    void GoToNewLine();
    void GoToPreviousLine();
};