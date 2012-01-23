#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <memory>
#include "ui_mainwindow.h"
#include <IParser.h>
#include <Lexer.h>
#include <IntermediateCode.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();

public slots:
    void Translate();

private:
    Ui::MainWindowClass ui;
    std::auto_ptr<JustCompiler::SyntacticAnalyzer::IParser> parser;
    std::auto_ptr<JustCompiler::LexicalAnalyzer::Lexer> lexer;

    void RenderParseTree(const JustCompiler::SyntacticAnalyzer::ParseTree& parseTree);
    void RenderParseSubtree(JustCompiler::SyntacticAnalyzer::PParseTreeNode node, QTreeWidgetItem* subtreeParent);
    void ClearParseTree();

    std::wstring RenderIntermediateCode(const JustCompiler::CodeGeneration::IntermediateCode& code);
};

#endif // MAINWINDOW_H
