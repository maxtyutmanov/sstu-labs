#include "Lexer.h"
#include <MyGrammar.h>
#include "ErrorsPresenter.h"
#include <fstream>
#include <iostream>
#include <boost/filesystem/detail/utf8_codecvt_facet.hpp>
#include <Windows.h>
#include <SyntaxDirectedParser.h>
#include <SyntaxError.h>
#include <SemanticChecker.h>
#include <SemanticError.h>
#include <TokenStream.h>
#include <MyGrammarFactory.h>
#include <FirstNFollowFactory.h>
#include <LexerInputBuffer.h>
using namespace std;
using namespace JustCompiler::LexicalAnalyzer;
using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;
using namespace JustCompiler::SyntacticAnalyzer;
using namespace JustCompiler::ParserGrammar;
using namespace JustCompiler::SemanticAnalyzer;

std::locale utf8_locale(std::locale(), new boost::filesystem::detail::utf8_codecvt_facet());

void RenderLexicalErrors(const vector<PLexicalError>& errors, ErrorsPresenter& errorsPresenter, wostream& output) {
    output << L"В процессе лексического разбора обнаружены ошибки: " << endl;

    for (int i = 0; i < errors.size(); ++i) {
        output << i + 1 << ". " << errorsPresenter.GetErrorMessage(errors[i]) << endl;
    }
}

void RenderSyntaxErrors(const vector<PSyntaxError>& errors, ErrorsPresenter& errorsPresenter, wostream& output) {
    output << L"В процессе синтаксического разбора обнаружены ошибки: " << endl;

    for (int i = 0; i < errors.size(); ++i) {
        output << i + 1 << ". " << errorsPresenter.GetErrorMessage(errors[i]) << endl;
    }
}

void RenderSemanticErrors(const vector<PSemanticError>& errors, ErrorsPresenter& errorsPresenter, wostream& output) {
    output << L"В процессе семантического анализа обнаружены ошибки: " << endl;

    for (int i = 0; i < errors.size(); ++i) {
        output << i + 1 << ". " << errorsPresenter.GetErrorMessage(errors[i]) << endl;
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

    ErrorsPresenter errorsPresenter;

    auto_ptr<Lexer> pLexer = MyGrammar::CreateLexer();
    auto_ptr<IInputBuffer> pLexerInputBuffer(new LexerInputBuffer(input));
    pLexer->SetInput(pLexerInputBuffer);
    LexerOutput output = pLexer->Tokenize();
    vector<PToken> tokens = output.get<0>();
    vector<PLexicalError> errors = output.get<1>();

    wofstream outputFile(argv[2]);
    outputFile.imbue(utf8_locale);

    if (!outputFile.good()) {
        wcout << L"Ошибка при попытке записи в указанный выходной файл" << endl;
        cin.get();
        return -3;
    }

    if (errors.size() == 0) {
        Grammar grammar = MyGrammarFactory::CreateGrammar();
        PFirstFunction first = FirstNFollowFactory::GetFirst(grammar);
        PFollowFunction follow = FirstNFollowFactory::GetFollow(grammar, first);
        ParserTable parserTable(grammar, *first, *follow);
        
        auto_ptr<IParser> parser(new SyntaxDirectedParser(grammar, parserTable));

        PTokenStream tokenStream(new TokenStream(tokens));

        auto_ptr<ParserOutput> parserOutput = parser->Parse(tokenStream);

        if (parserOutput->errors.size() == 0) {
            SemanticChecker semanticChecker;
            SemanticCheckerOutput semanticCheckerOutput = semanticChecker.Check(parserOutput->parseTree);

            if (semanticCheckerOutput.errors.size() == 0) {
                wcout << L"Трансляция завершена. Ошибок не обнаружено." << endl;
            }
            else {
                RenderSemanticErrors(semanticCheckerOutput.errors, errorsPresenter, wcout);
            }
        }
        else {
            RenderSyntaxErrors(parserOutput->errors, errorsPresenter, wcout);
        }
    }
    else {
        RenderLexicalErrors(errors, errorsPresenter, wcout);
    }

    cin.get();
    return 0;
}