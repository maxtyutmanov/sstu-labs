#pragma once

#include <LexerSettings.h>
#include <LexicalError.h>
#include <vector>
#include <string>

using std::vector;
using std::wstring;

class ErrorsPresenter {
public:
    explicit ErrorsPresenter(const LexerSettings& settings);
    
    wstring GetErrorMessage(const LexicalError& error);
private:
    LexerSettings settings;
};