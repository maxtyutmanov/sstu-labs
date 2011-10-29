#pragma once

#include <string>
#include <iostream>
#include <map>
using std::wstring;
using std::wistream;
using std::map;

class LexerInputBuffer {
public:
    explicit LexerInputBuffer(wistream &input);

    wchar_t Get();
    void Unget();
    bool Eof() const;
    int GetLineNumber() const;
    int GetCharacterNumber() const;
private:
    wstring input;
    int cursor;
    int lineNumber;
    int characterNumber;
    //correspondence between line numbers and characters counts in this lines
    map<int, int> characterCounts;

    void GoToNewLine();
    void GoToPreviousLine();
};