#include "mainwindow.h"
#include <SyntaxDirectedParser.h>
#include <MyGrammarFactory.h>
#include <LexerInputBuffer.h>
#include <MyGrammar.h>
#include <FirstNFollowFactory.h>
#include <sstream>
#include <TokenStream.h>
#include <SemanticChecker.h>
#include <NonTerminalWithDesc.h>
#include <TerminalWithDesc.h>
#include <CodeGenerator.h>
#include <sstream>
#include "ErrorsPresenter.h"

using namespace std;
using namespace JustCompiler::LexicalAnalyzer;
using namespace JustCompiler::SyntacticAnalyzer;
using namespace JustCompiler::SyntacticAnalyzer::ContextFreeGrammar;
using namespace JustCompiler::ParserGrammar;
using namespace JustCompiler::SemanticAnalyzer;
using namespace JustCompiler::CodeGeneration;

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    connect(ui.translateAction, SIGNAL(triggered()), this, SLOT(Translate()));

    lexer = MyGrammar::CreateLexer();
    Grammar parserGrammar = MyGrammarFactory::CreateGrammar();
    PFirstFunction pFirst = FirstNFollowFactory::GetFirst(parserGrammar);
    PFollowFunction pFollow = FirstNFollowFactory::GetFollow(parserGrammar, pFirst);
    ParserTable controlTable(parserGrammar, *pFirst, *pFollow);
    parser.reset(new SyntaxDirectedParser(parserGrammar, controlTable));

    ui.parseTreeView->setHeaderLabel(QString::fromUtf16((const ushort *)L"Дерево разбора"));
    ui.parseTreeView->hide();
}

MainWindow::~MainWindow()
{

}

void MainWindow::Translate() {
    ClearParseTree();
    wstring outputTxt;

    QString source = ui.sourceTxt->toPlainText();
    const wchar_t* sourceWstring = (const wchar_t *)source.utf16();

    wistringstream iss(sourceWstring);

    ErrorsPresenter errorsPresenter;

    auto_ptr<IInputBuffer> lexerInput(new LexerInputBuffer(iss));

    lexer->SetInput(lexerInput);
    LexerOutput lexerOutput = lexer->Tokenize();

    size_t i = 0;
    vector<PLexicalError> lexicalErrors = lexerOutput.get<1>();

    if (lexicalErrors.size() == 0) {
        vector<PToken> tokens = lexerOutput.get<0>();
        boost::shared_ptr<ITokenStream> tokenStream(new TokenStream(tokens));
        auto_ptr<ParserOutput> parserOutput = parser->Parse(tokenStream);

        if (parserOutput->errors.size() == 0) {
            SemanticChecker semanticChecker;
            SemanticCheckerOutput semanticCheckerOutput = semanticChecker.Check(parserOutput->parseTree);

            if (semanticCheckerOutput.errors.size() == 0) {
                CodeGenerator generator;
                IntermediateCode code = generator.GenerateCode(parserOutput->parseTree);

                outputTxt = L"Трансляция завершена. Ошибок не обнаружено\n\n" + RenderIntermediateCode(code);

                RenderParseTree(parserOutput->parseTree);
            }
            else {
                //outputTxt = L"Семантические ошибки";
                for (i = 0; i < semanticCheckerOutput.errors.size(); ++i) {
                    outputTxt.append(errorsPresenter.GetErrorMessage(semanticCheckerOutput.errors[i]) + L"\n");
                }
            }
        }
        else {
            //outputTxt = L"Синтаксические ошибки";
            for (i = 0; i < parserOutput->errors.size(); ++i) {
                outputTxt.append(errorsPresenter.GetErrorMessage(parserOutput->errors[i]) + L"\n");
            }
        }
    }
    else {
        //outputTxt = L"Лексические ошибки";

        for (i = 0; i < lexicalErrors.size(); ++i) {
            outputTxt.append(errorsPresenter.GetErrorMessage(lexicalErrors[i]) + L"\n");
        }
    }
    ui.outputTxt->setText(QString::fromUtf16((const ushort *)outputTxt.c_str(), outputTxt.size()));
}

void MainWindow::RenderParseTree(const ParseTree& parseTree) {
    ui.parseTreeView->clear();
    
    QTreeWidgetItem* root = new QTreeWidgetItem(ui.parseTreeView);
    //root->setText(0, QString::fromUtf16((const ushort*)L"Дерево разбора"));

    RenderParseSubtree(parseTree.GetRoot(), root);

    ui.parseTreeView->expandAll();
}

void MainWindow::RenderParseSubtree(PParseTreeNode node, QTreeWidgetItem* subtreeRoot) {
    wstring nodeText;
    PSymbol symbol = node->GetSymbol();

    if (symbol->GetType() == SymbolType::NonTerminal) {
        PNonTerminalWithDesc nonTerminal = boost::dynamic_pointer_cast<NonTerminalWithDesc, Symbol>(symbol);
        assert(nonTerminal.get() != NULL);
        nodeText = nonTerminal->GetDesc();
    }
    else {
        PTerminalWithDesc terminal = boost::dynamic_pointer_cast<TerminalWithDesc, Symbol>(symbol);
        assert(terminal.get() != NULL);
        nodeText = terminal->GetDesc();
    }

    subtreeRoot->setText(0, QString::fromUtf16((const ushort*)nodeText.c_str()));

    for (size_t i = 0; i < node->Children().size(); ++i) {
        QTreeWidgetItem* childItem = new QTreeWidgetItem(subtreeRoot);
        RenderParseSubtree(node->Children()[i], childItem);
    }
}

void MainWindow::ClearParseTree() {
    ui.parseTreeView->clear();
}

wstring MainWindow::RenderIntermediateCode(const IntermediateCode& code) {
    wostringstream oss;

    vector<Command> commands = code.GetCommands();

    vector<Command>::iterator it;

    for (it = commands.begin(); it != commands.end(); ++it) {
        oss << it->ToString() << endl;
    }

    return oss.str();
}