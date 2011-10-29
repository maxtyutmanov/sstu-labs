#include "Lexer.h"
#include "Identifier.h"
#include "IntConstant.h"
#include "StringLiteral.h"
#include "LexerOutputPresenter.h"
#include <map>
#include <fstream>
#include <iostream>
#include <boost/filesystem/detail/utf8_codecvt_facet.hpp>
#include <Windows.h>
using namespace std;

std::locale utf8_locale(std::locale(), new boost::filesystem::detail::utf8_codecvt_facet());

LexerSettings SetupLexerSettings() {
    LexemesDictionary keywords;

    keywords[L"program"] = TokenTag::Program;
    keywords[L"while"] = TokenTag::While;
    keywords[L"for"] = TokenTag::For;
    keywords[L"array"] = TokenTag::Array;
    keywords[L"begin"] = TokenTag::Begin;
    keywords[L"end"] = TokenTag::End;
    keywords[L"int"] = TokenTag::Type_Int;
    keywords[L"float"] = TokenTag::Type_Float;
    keywords[L"string"] = TokenTag::Type_String;

    LexemesDictionary standardFunctions;

    standardFunctions[L"sqrt"] = TokenTag::Sqrt;
    standardFunctions[L"log"] = TokenTag::Log;
    standardFunctions[L"ln"] = TokenTag::Ln;
    standardFunctions[L"nearby"] = TokenTag::Nearby;

    OneCharLexemesDictionary oneCharacterTokens;

    oneCharacterTokens[L'+'] = TokenTag::Plus;
    oneCharacterTokens[L'-'] = TokenTag::Minus;
    oneCharacterTokens[L'*'] = TokenTag::Asterisk;
    oneCharacterTokens[L':'] = TokenTag::Colon;
    oneCharacterTokens[L'_'] = TokenTag::Underscore;
    oneCharacterTokens[L'/'] = TokenTag::Slash;
    oneCharacterTokens[L'('] = TokenTag::OpeningRoundBracket;
    oneCharacterTokens[L')'] = TokenTag::ClosingRoundBracket;
    oneCharacterTokens[L'{'] = TokenTag::OpeningBrace;
    oneCharacterTokens[L'}'] = TokenTag::ClosingBrace;
    oneCharacterTokens[L'='] = TokenTag::Equals;
    oneCharacterTokens[L'<'] = TokenTag::LessThan;
    oneCharacterTokens[L'>'] = TokenTag::GreaterThan;
    oneCharacterTokens[L'['] = TokenTag::OpeningSquareBracket;
    oneCharacterTokens[L']'] = TokenTag::ClosingSquareBracket;
    oneCharacterTokens[L';'] = TokenTag::Semicolon;
    oneCharacterTokens[L'\''] = TokenTag::SingleQuotes;
    oneCharacterTokens[L','] = TokenTag::Comma;

    return LexerSettings(keywords, standardFunctions, oneCharacterTokens);
}

void RenderLexicalErrors(const vector<LexicalError *>& errors, wostream& output) {
    output << L"В процессе лексического разбора обнаружены ошибки: " << endl;

    for (int i = 0; i < errors.size(); ++i) {
        output << i + 1 << L": (Строка " << errors[i]->GetLineNumber() 
            << L" символ " << errors[i]->GetCharNumber() << L"): " 
            << errors[i]->GetErrorMessage() << endl;
    }

    output << endl;
}

void RenderTokenTables(TokenTablesContainer& tokenTables, const LexerSettings& lexerSettings, wostream& output) {
    output << endl << endl << L"Ключевые слова (K1):" << endl;
    tokenTables.keywords.WriteToStream(lexerSettings, output);

    output << endl << L"Стандартные функции (K2):" << endl;
    tokenTables.standardFunctions.WriteToStream(lexerSettings, output);

    output << endl << L"Разделители (K3):" << endl;
    tokenTables.separators.WriteToStream(lexerSettings, output);

    output << endl << L"Константы (K4):" << endl;
    tokenTables.constants.WriteToStream(lexerSettings, output);

    output << endl << L"Идентификаторы (K5):" << endl;
    tokenTables.identifiers.WriteToStream(lexerSettings, output);
}

void CleanUp(vector<Token *>& tokens, vector<LexicalError *>& errors) {
    vector<Token *>::iterator tokensIt;

    for (tokensIt = tokens.begin(); tokensIt != tokens.end(); ++tokensIt) {
        delete *tokensIt;
    }

    vector<LexicalError *>::iterator errorsIt;

    for (errorsIt = errors.begin(); errorsIt != errors.end(); ++errorsIt) {
        delete *errorsIt;
    }
}

int main(int argc, char** argv) {
    UINT oldcp = GetConsoleOutputCP();

    std::locale rusLocale = std::locale("rus_rus.866");
    wcout.imbue(rusLocale);

    if (argc != 3) {
        wcout << L"Должны быть указаны входной и выходной файлы" << endl;
        SetConsoleOutputCP(oldcp);
        cin.get();
        return -1;
    }

    wifstream input(argv[1]);
    input.imbue(utf8_locale);

    if (!input.good()) {
        wcout << L"Ошибка при попытке чтения из указанного входного файла" << endl;
        SetConsoleOutputCP(oldcp);
        cin.get();
        return -2;
    }

    LexerSettings lexerSettings = SetupLexerSettings();

    Lexer lexer(lexerSettings, input);
    
    LexerOutput output = lexer.Tokenize();

    vector<Token *> tokens = output.get<0>();
    vector<LexicalError *> errors = output.get<1>();

    wofstream outputFile(argv[2]);
    outputFile.imbue(utf8_locale);

    if (!outputFile.good()) {
        wcout << L"Ошибка при попытке записи в указанный выходной файл" << endl;
        CleanUp(tokens, errors);
        SetConsoleOutputCP(oldcp);
        cin.get();
        return -3;
    }

    if (errors.size() > 0) {
        RenderLexicalErrors(errors, wcout);
    }
    else {
        wcout << L"Лексический анализ завершен. Ошибок не обнаружено." << endl;
    }

    LexerOutputPresenter presenter;

    TokenTablesContainer tablesContainer = presenter.WriteDescriptorText(tokens, outputFile);

    RenderTokenTables(tablesContainer, lexerSettings, outputFile);

    CleanUp(tokens, errors);
    SetConsoleOutputCP(oldcp);
    cin.get();
    return 0;
}