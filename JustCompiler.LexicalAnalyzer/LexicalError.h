#pragma once

#include <string>
using std::wstring;

class LexicalError {
public:
    LexicalError();
    LexicalError(const int lineNumber, const int charNumber, const wstring& errorMessage);

    int GetLineNumber() const;
    int GetCharNumber() const;
    wstring GetErrorMessage() const;
private:
    int lineNumber;
    int charNumber;
    wstring errorMessage;
};