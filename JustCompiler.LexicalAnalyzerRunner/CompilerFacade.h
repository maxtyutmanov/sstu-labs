#pragma once

#include <iostream>
#include <SyntaxError.h>
#include <LexicalError.h>
#include <SemanticError.h>
#include "ErrorsPresenter.h"
#include <vector>
using namespace JustCompiler::LexicalAnalyzer;
using namespace JustCompiler::SyntacticAnalyzer;
using namespace JustCompiler::SemanticAnalyzer;

namespace CompilerFacade {
    void RenderLexicalErrors(const std::vector<PLexicalError>& errors, ErrorsPresenter& errorsPresenter, std::wostream& output);
    void RenderSyntaxErrors(const std::vector<PSyntaxError>& errors, ErrorsPresenter& errorsPresenter, std::wostream& output);
    void RenderSemanticErrors(const std::vector<PSemanticError>& errors, ErrorsPresenter& errorsPresenter, std::wostream& output);
    void Compile(std::wistream& input, std::wostream& errorsOutput);

}