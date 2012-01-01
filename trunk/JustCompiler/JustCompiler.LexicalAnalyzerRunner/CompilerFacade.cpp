#include "Lexer.h"
#include <MyGrammar.h>
#include "ErrorsPresenter.h"
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <SyntaxDirectedParser.h>
#include <SyntaxError.h>
#include <SemanticChecker.h>
#include <SemanticError.h>
#include <TokenStream.h>
#include <MyGrammarFactory.h>
#include <FirstNFollowFactory.h>
#include <LexerInputBuffer.h>
#include "CompilerFacade.h"
#include <TerminalWithDesc.h>
#include <NonTerminalWithDesc.h>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;
using namespace JustCompiler::ParserGrammar;

namespace CompilerFacade {

    void RenderLexicalErrors(const vector<PLexicalError>& errors, ErrorsPresenter& errorsPresenter, wostream& output) {
        for (int i = 0; i < errors.size(); ++i) {
            output << i + 1 << ". " << errorsPresenter.GetErrorMessage(errors[i]) << endl;
        }
    }

    void RenderSyntaxErrors(const vector<PSyntaxError>& errors, ErrorsPresenter& errorsPresenter, wostream& output) {
        for (int i = 0; i < errors.size(); ++i) {
            output << i + 1 << ". " << errorsPresenter.GetErrorMessage(errors[i]) << endl;
        }
    }

    void RenderSemanticErrors(const vector<PSemanticError>& errors, ErrorsPresenter& errorsPresenter, wostream& output) {
        for (int i = 0; i < errors.size(); ++i) {
            output << i + 1 << ". " << errorsPresenter.GetErrorMessage(errors[i]) << endl;
        }
    }

    void RenderSelection(Grammar& grammar, FirstFunction& first, FollowFunction& follow, wostream& output) {
        vector<Production>::const_iterator prodIt;

        for (prodIt = grammar.Productions().cbegin(); prodIt != grammar.Productions().cend(); ++prodIt) {
            PNonTerminal left = prodIt->Left();
            SymbolString right = prodIt->Right();

            TerminalSet selection = first(right);

            if (first(right).Contains(SpecialTokenTag::Empty)) {
                selection.Merge(follow(left), false);
            }

            PNonTerminalWithDesc leftD = boost::dynamic_pointer_cast<NonTerminalWithDesc, NonTerminal>(left);
            output << L"Выбор ( " << leftD->GetDesc() << L" := ";

            for (size_t i = 0; i < right.size(); ++i) {
                PNonTerminalWithDesc n = boost::dynamic_pointer_cast<NonTerminalWithDesc, Symbol>(right[i]);
                PTerminalWithDesc t = boost::dynamic_pointer_cast<TerminalWithDesc, Symbol>(right[i]);

                if (n.get() != NULL) {
                    output << n->GetDesc() << L" ";
                }
                else {
                    output << t->GetDesc() << L" ";
                }
            }

            output << L") = { ";

            for (size_t i = 0; i < selection.size(); ++i) {
                PTerminalWithDesc t = boost::dynamic_pointer_cast<TerminalWithDesc, Terminal>(selection[i]);
                output << t->GetDesc() << L" ";
            }

            output << L"}" << endl;
        }
    }

    void Compile(wistream& input, wostream& errorsOutput) {
        std::locale rusLocale = std::locale("rus_rus.866");
        input.imbue(rusLocale);

        ErrorsPresenter errorsPresenter;

        auto_ptr<Lexer> pLexer = MyGrammar::CreateLexer();
        auto_ptr<IInputBuffer> pLexerInputBuffer(new LexerInputBuffer(input));
        pLexer->SetInput(pLexerInputBuffer);
        LexerOutput output = pLexer->Tokenize();
        vector<PToken> tokens = output.get<0>();
        vector<PLexicalError> errors = output.get<1>();

        if (errors.size() == 0) {
            Grammar grammar = MyGrammarFactory::CreateGrammar();

            PFirstFunction first = FirstNFollowFactory::GetFirst(grammar);
            PFollowFunction follow = FirstNFollowFactory::GetFollow(grammar, first);
            //RenderSelection(grammar, *first, *follow, errorsOutput);
            ParserTable parserTable(grammar, *first, *follow);
        
            auto_ptr<IParser> parser(new SyntaxDirectedParser(grammar, parserTable));

            PTokenStream tokenStream(new TokenStream(tokens));

            auto_ptr<ParserOutput> parserOutput = parser->Parse(tokenStream);

            if (parserOutput->errors.size() == 0) {
                SemanticChecker semanticChecker;
                SemanticCheckerOutput semanticCheckerOutput = semanticChecker.Check(parserOutput->parseTree);

                if (semanticCheckerOutput.errors.size() == 0) {
                    errorsOutput << L"Трансляция завершена. Ошибок не обнаружено." << endl;
                }
                else {
                    RenderSemanticErrors(semanticCheckerOutput.errors, errorsPresenter, errorsOutput);
                }
            }
            else {
                RenderSyntaxErrors(parserOutput->errors, errorsPresenter, errorsOutput);
            }
        }
        else {
            RenderLexicalErrors(errors, errorsPresenter, errorsOutput);
        }
    }
}