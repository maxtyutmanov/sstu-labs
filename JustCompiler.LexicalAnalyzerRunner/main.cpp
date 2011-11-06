#include "Lexer.h"
#include "Identifier.h"
#include "IntConstant.h"
#include "StringLiteral.h"
#include "LexerOutputPresenter.h"
#include "CharacterValidators.h"
#include <MyGrammar.h>
#include "ErrorsPresenter.h"
#include <map>
#include <fstream>
#include <iostream>
#include <boost/filesystem/detail/utf8_codecvt_facet.hpp>
#include <Windows.h>
using namespace std;

std::locale utf8_locale(std::locale(), new boost::filesystem::detail::utf8_codecvt_facet());

void RenderLexicalErrors(const vector<LexicalError *>& errors, ErrorsPresenter& errorsPresenter, wostream& output) {
    output << L"В процессе лексического разбора обнаружены ошибки: " << endl;

    for (int i = 0; i < errors.size(); ++i) {
        output << i + 1 << errorsPresenter.GetErrorMessage(*errors[i]) << endl;
    }
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
    std::locale rusLocale = std::locale("rus_rus.866");
    wcout.imbue(rusLocale);

    if (argc != 3) {
        wcout << L"Должны быть указаны входной и выходной файлы" << endl;
        cin.get();
        return -1;
    }

    wifstream input(argv[1]);
    input.imbue(utf8_locale);

    if (!input.good()) {
        wcout << L"Ошибка при попытке чтения из указанного входного файла" << endl;
        cin.get();
        return -2;
    }

    LexerSettings lexerSettings = MyGrammar::SetupLexerSettings();

    auto_ptr<Lexer> pLexer = MyGrammar::CreateLexer(lexerSettings, input);
    
    LexerOutput output = pLexer->Tokenize();

    vector<Token *> tokens = output.get<0>();
    vector<LexicalError *> errors = output.get<1>();

    wofstream outputFile(argv[2]);
    outputFile.imbue(utf8_locale);

    if (!outputFile.good()) {
        wcout << L"Ошибка при попытке записи в указанный выходной файл" << endl;
        CleanUp(tokens, errors);
        cin.get();
        return -3;
    }

    if (errors.size() > 0) {
        ErrorsPresenter errorsPresenter(lexerSettings);

        RenderLexicalErrors(errors, errorsPresenter, wcout);
    }
    else {
        wcout << L"Лексический анализ завершен. Ошибок не обнаружено." << endl;
    }

    LexerOutputPresenter presenter;

    TokenTablesContainer tablesContainer = presenter.WriteDescriptorText(tokens, outputFile);

    RenderTokenTables(tablesContainer, lexerSettings, outputFile);

    CleanUp(tokens, errors);
    cin.get();
    return 0;
}