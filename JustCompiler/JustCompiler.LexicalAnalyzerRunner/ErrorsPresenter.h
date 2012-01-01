#pragma once

#include <LexicalError.h>
#include <SyntaxError.h>
#include <SemanticError.h>
#include <vector>
#include <string>

using std::vector;
using std::wstring;

class ErrorsPresenter {
public:
    wstring GetErrorMessage(const JustCompiler::LexicalAnalyzer::PLexicalError error);
    wstring GetErrorMessage(const JustCompiler::SyntacticAnalyzer::PSyntaxError error);
    wstring GetErrorMessage(const JustCompiler::SemanticAnalyzer::PSemanticError error);
private:
    wstring GetMessageAboutExpectedToken(const JustCompiler::SyntacticAnalyzer::PSyntaxError error);
    wstring GetTokenName(const int tokenTag);
};