#include "LexicalError.h"

LexicalError::LexicalError() {
    //TODO: WTF?
    lineNumber = 0;
    charNumber = 0;
}

LexicalError::LexicalError(const int lineNumber, const int charNumber, const wstring& errorMessage) {
    this->lineNumber = lineNumber;
    this->charNumber = charNumber;
    this->errorMessage = errorMessage;
}

int LexicalError::GetLineNumber() const {
    return lineNumber;
}

int LexicalError::GetCharNumber() const {
    return charNumber;
}

wstring LexicalError::GetErrorMessage() const {
    return errorMessage;
}