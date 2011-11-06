#pragma once

#include <memory>
#include <Lexer.h>
using std::auto_ptr;

class MyGrammar {
public:
    static auto_ptr<Lexer> CreateLexer(const LexerSettings& settings, wistream& input);
    static LexerSettings SetupLexerSettings();
};